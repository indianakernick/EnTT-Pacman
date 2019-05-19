# EnTT Pacman

[![Build Status](https://travis-ci.org/Kerndog73/EnTT-Pacman.svg?branch=master)](https://travis-ci.org/Kerndog73/EnTT-Pacman)
[![Build Status](https://ci.appveyor.com/api/projects/status/5ndjklgbe42b0q9b?svg=true)](https://ci.appveyor.com/project/Kerndog73/entt-example)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](./LICENSE)

An example of how to use the ECS part of the [EnTT Framework](https://github.com/skypjack/entt)

![Screenshot](https://i.imgur.com/J5RDcIz.png)

## What is this?

This is a tutorial on how to use the EnTT framework to make a game. This project is for people who are just starting out with EnTT and not too sure how use it.

The code isn't perfect. It could certainly be improved in some areas. Any kind of feedback is welcome. Be sure to ask me questions if something is unclear. [The EnTT Gitter channel](https://gitter.im/skypjack/entt) is a great place for discussion.

## Dependencies

* [Simpleton](https://github.com/Kerndog73/Simpleton-Engine)
* [SDL2 Library](https://www.libsdl.org/) for input and rendering
* [GLM](https://github.com/g-truc/glm)
* [EnTT](https://github.com/skypjack/entt)

EnTT Pacman uses [conan](https://conan.io/) to import all project dependencies.
You only require python `pip` to be installed in your system.

First, install conan:

```bash
pip install conan
```

Then add bincrafters remote:
```bash
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```

## Building

Conan will take care of downloading all dependent packages.

```bash
git clone https://github.com/Kerndog73/EnTT-Pacman.git
mkdir -p EnTT-Pacman/build && cd EnTT-Pacman/build
conan install --build=missing ..
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
./example
```

## It's not exactly the same as the real thing

I read [The Pacman Dossier](http://tralvex.com/download/forum/The%20Pac-Man%20Dossier.pdf) many times during development. If you notice a difference between this game and the real thing, that wasn't an oversight. Perfectly recreating the real thing would have made this project quite a bit more complicated. I think it's complicated enough as it is!
