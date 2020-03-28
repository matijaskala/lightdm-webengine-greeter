#include <QApplication>
#include <QSettings>

#include "mainwindow.h"

QString theme() {
    QSettings settings("/etc/lightdm/lightdm-webengine-greeter.conf", QSettings::IniFormat);
    settings.beginGroup("greeter");
    auto theme = settings.value("webkit_theme");
    if (theme.isNull())
        theme = settings.value("webkit-theme", "default");
    settings.endGroup();
    return theme.toString();
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    new MainWindow(theme());
    app.exec();
}
