/*
 * This file is part of WebEngine Greeter
 * Copyright (C) 2019  Matija Skala <mskala@gmx.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QFile>
#include <QScreen>
#include <QWebChannel>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>
#include <QWebEngineView>

#include "greeter.h"
#include "mainwindow.h"
#include "themeutils.h"

static void addWebEngineScript(QString path, QString name, QWebEngineView* view)
{
    QWebEngineScript script;
    QFile scriptFile{path};
    if (scriptFile.open(QFile::ReadOnly))
    {
        auto scriptString = scriptFile.readAll();
        script.setInjectionPoint(QWebEngineScript::DocumentCreation);
        script.setName(name);
        script.setWorldId(QWebEngineScript::MainWorld);
        script.setSourceCode(QString::fromUtf8(scriptString));
    }
    view->page()->scripts().insert(script);
}

MainWindow::MainWindow(QString theme)
: m_view{new QWebEngineView{this}}
, m_channel{new QWebChannel{m_view->page()}}
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle("WebEngine greeter for LightDM");
    setWindowState(Qt::WindowMaximized);
    m_view->setContextMenuPolicy(Qt::PreventContextMenu);
    m_view->show();
    setCentralWidget(m_view);
    show();
    m_greeter = new Greeter;
    m_themeUtils = new ThemeUtils;
    QHash<QString, QObject*> objs;
    objs["LightDMGreeter"] = m_greeter;
    objs["ThemeUtils"] = m_themeUtils;
    m_channel->registerObject("LightDMGreeter", m_greeter);
    m_channel->registerObject("ThemeUtils", m_themeUtils);
    m_view->page()->setWebChannel(m_channel);
    QString webchUrl = ":/qtwebchannel/qwebchannel.js";
    addWebEngineScript(webchUrl, "QWebChannel API", m_view);
    addWebEngineScript(":/_greeter/web-greeter/moment-with-locales.min.js", "res1", m_view);
    addWebEngineScript(":/_greeter/web-greeter/ThemeUtils.js", "res2", m_view);
    addWebEngineScript(":/_greeter/web-greeter/bootstrap.js", "res3", m_view);
    m_view->page()->load(QUrl{"file:///" + m_greeter->themes_directory() + "/" + theme + "/index.html"});
    setGeometry(QApplication::primaryScreen()->geometry());
}
