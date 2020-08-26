# Retro-menu
Retro menu launcher for [Retro](https://github.com/dev-0x7C6/retro-build-environment) distribution. Written in Qt / QML.  Look and feel is inspired by Nintendo Switch system menu.

![alt text](https://devwork.space/wp-content/uploads/2020/08/retro_menu.png "retro-menu 2020-08-26")

# Current state
Project is under early development state, it's working but upcomming changes may change behavior and functionality.

# Build 

```console
user@workspace # cd retro-menu
user@workspace # cmake . -DCMAKE_INSTALL_PREFIX=/usr
user@workspace # make -j$(nproc)
root@workspace # make install
```
