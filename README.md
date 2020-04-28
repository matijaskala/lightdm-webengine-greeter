# LightDM WebEngine Greeter
QtWebEngine-based greeter for LightDM

![](themes/sunlight/screenshot.png)

### Build:
```sh
git clone https://github.com/matijaskala/lightdm-webengine-greeter.git
mkdir lightdm-webengine-greeter/build
cd lightdm-webengine-greeter/build
meson --buildtype release ..
ninja
```

### Install:
```sh
sudo ninja install
```

If the greeter refuses to start, try disabling sandbox:

Create a file named _/etc/lightdm/Xgreeter_:
```sh
#!/bin/sh

export QTWEBENGINE_DISABLE_SANDBOX=1
exec "$@"
```
Then run:
```sh
sudo chmod +x /etc/lightdm/Xgreeter
sudo sed -i 's:#greeter-wrapper=.*:greeter-wrapper=/etc/lightdm/Xgreeter:' /etc/lightdm/lightdm.conf
```
