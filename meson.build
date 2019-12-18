project('lightdm-webengine-greeter', 'Cpp')
qt5 = import('qt5')
qt5_files = qt5.preprocess(
    moc_headers: ['mainwindow.h', 'greeter.h', 'themeutils.h'],
    qresources: 'bundle.qrc')
qt5_dep = dependency('qt5', modules: ['Core', 'Gui', 'Widgets', 'WebEngineWidgets'])
glib_dep = dependency('glib-2.0')
lightdm_gobject_dep = dependency('liblightdm-gobject-1')
lightdm_qt5_dep = dependency('liblightdm-qt5-3')
executable('lightdm-webengine-greeter',
    'main.cpp', 'mainwindow.cpp', 'greeter.cpp', 'themeutils.cpp', qt5_files,
    install: true,
    dependencies: [qt5_dep, glib_dep, lightdm_gobject_dep, lightdm_qt5_dep])
install_data('lightdm-webengine-greeter.desktop', install_dir: 'share/xgreeters')
install_subdir('web-greeter/_vendor', install_dir: 'share/webengine-greeter')
install_subdir('web-greeter/themes', install_dir: 'share/webengine-greeter')
