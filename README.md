# EnTT-Example

[![Build Status](https://travis-ci.org/Kerndog73/EnTT-Example.svg?branch=master)](https://travis-ci.org/Kerndog73/EnTT-Example)
[![Build Status](https://ci.appveyor.com/api/projects/status/5ndjklgbe42b0q9b?svg=true)](https://ci.appveyor.com/project/Kerndog73/entt-example)

An example of how to use the ECS part of the [EnTT Framework](https://github.com/skypjack/entt)

## What is this?

When I first found EnTT, I wondered "How do I make a game with this?". An example would have been really helpful at that time. I couldn't find one. I learnt how to make games with EnTT by making games with EnTT. This took quite a long time. This project is for people who are just starting out with EnTT and not too sure how use it.

As of writing this, the project is incomplete. The game is sort of playable at the moment so you can still clone the source and build it. I like to think the code is clean and easy to follow. After the game is functionally complete, I plan to spend a lot of time refactoring, adding comments and simplifying the code. I will also write a tour and put it in this `README.md` that outlines how the parts come together to make a game.

This is a tutorial on how to use an ECS framework (EnTT in particular) to make a game.

## Installing SDL2

This uses the [SDL2 Library](https://www.libsdl.org/) for input and rendering. CMake will find it if it's on your system. For details on how to install SDL2, see the [installation page](https://wiki.libsdl.org/Installation).

If you're on MacOS,

```
brew install sdl2
```

If you're on a Debian based system,

```
sudo apt-get install libsdl2-dev
```

If you're on a Red Hat based system,

```
sudo yum install SDL2-devel
```

If you're on some other Linux system that doesn't have an SDL2 package, you'll have to build the source.

```
hg clone https://hg.libsdl.org/SDL SDL
cd SDL
mkdir build
cd build
../configure
make
sudo make install
```

If you're on Windows,

```
vcpkg install sdl2
```

## Building

The other dependencies ([GLM](https://github.com/g-truc/glm), [EnTT](https://github.com/skypjack/entt), [Simpleton](https://github.com/Kerndog73/Simpleton-Engine)) are bundled with the project so you don't have to worry about them. On Windows, you'll need to specify the vcpkg toolchain file.

```
git clone https://github.com/Kerndog73/EnTT-Example.git
cd EnTT-Example/build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
./example
```