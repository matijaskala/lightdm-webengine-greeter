project('lightdm-webengine-greeter', 'cpp', default_options: ['cpp_std=c++17'])
qt5 = import('qt5')
qt5_files = qt5.preprocess(
    moc_headers: ['mainwindow.h', 'greeter.h', 'themeutils.h'],
    qresources: 'bundle.qrc')
qt5_dep = dependency('qt5', modules: ['Core', 'Gui', 'Widgets', 'WebEngineWidgets'])
glib_dep = dependency('glib-2.0')
lightdm_gobject_dep = dependency('liblightdm-gobject-1')
lightdm_qt5_dep = dependency('liblightdm-qt5-3')
prefix = get_option('prefix')
datadir = get_option('datadir')
executable('lightdm-webengine-greeter',
    'main.cpp', 'mainwindow.cpp', 'greeter.cpp', 'themeutils.cpp', qt5_files,
    cpp_args: '-DDATADIR="' + join_paths(prefix, datadir) + '"',
    install: true,
    dependencies: [qt5_dep, glib_dep, lightdm_gobject_dep, lightdm_qt5_dep])
install_data('lightdm-webengine-greeter.conf', install_dir: '/etc/lightdm')
install_data('lightdm-webengine-greeter.desktop', install_dir: join_paths(datadir, 'xgreeters'))
install_subdir('web-greeter/_vendor', install_dir: join_paths(datadir, 'lightdm-webengine-greeter'))
install_subdir('web-greeter/themes', install_dir: join_paths(datadir, 'lightdm-webengine-greeter'))
install_subdir('themes', install_dir: join_paths(datadir, 'lightdm-webengine-greeter'))
