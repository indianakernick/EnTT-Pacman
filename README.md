# EnTT Pacman

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](./LICENSE)

An example of how to use the ECS part of the [EnTT Framework](https://github.com/skypjack/entt)

![Screenshot](https://i.imgur.com/J5RDcIz.png)

## What is this?

This is a tutorial on how to use the EnTT framework to make a game. This project
is for people who are just starting out with EnTT and not too sure how use it.

The code isn't perfect. It could certainly be improved in some areas. Any kind
of feedback is welcome. Be sure to ask me questions if something is unclear.
[The EnTT Gitter channel](https://gitter.im/skypjack/entt) is a great place for
discussion.

## Installing SDL2

This uses the [SDL2 Library](https://www.libsdl.org/) for input and rendering.
CMake will find it if it's on your system. For details on how to install SDL2,
see the [installation page](https://wiki.libsdl.org/Installation).

If you're on MacOS,

```
brew install sdl2
```

If you're on a Debian based system,

```
sudo apt-get install libsdl2-dev
```

If you're on Windows,

```
vcpkg install sdl2
```

## Building

[EnTT](https://github.com/skypjack/entt) is bundled with the project to make
building this as easy as possible.

```
git clone https://github.com/indianakernick/EnTT-Pacman.git
cd EnTT-Pacman/build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
./pacman
```

## It's not exactly the same as the real thing

I read [The Pacman Dossier](http://tralvex.com/download/forum/The%20Pac-Man%20Dossier.pdf)
many times during development. If you notice a difference between this game and
the real thing, that wasn't an oversight. Perfectly recreating the real thing
would have made this project quite a bit more complicated. I think it's
complicated enough as it is!
