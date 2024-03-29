/*
 * This file is part of WebEngine Greeter
 * Copyright (C) 2019-2021 Matija Skala <mskala@gmx.com>
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class QWebChannel;
class QWebEngineView;
class Greeter;
class ThemeUtils;
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString theme);
    void keyPressEvent ( QKeyEvent * event ) override;

private:
    QWebEngineView* m_view;
    QWebChannel* m_channel;
    Greeter* m_greeter;
    ThemeUtils* m_themeUtils;
};

#endif // MAINWINDOW_H
