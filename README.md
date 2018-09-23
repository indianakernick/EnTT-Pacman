# EnTT-Example

[![Build Status](https://travis-ci.org/Kerndog73/EnTT-Example.svg?branch=master)](https://travis-ci.org/Kerndog73/EnTT-Example)
[![Build Status](https://ci.appveyor.com/api/projects/status/5ndjklgbe42b0q9b?svg=true)](https://ci.appveyor.com/project/Kerndog73/entt-example)

An example of how to use the ECS part of the [EnTT Framework](https://github.com/skypjack/entt)

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

The other dependencies are bundled with the project so you don't have to worry about them. The project can be built with CMake.

```
git clone https://github.com/Kerndog73/EnTT-Example.git
cd EnTT-Example/build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
./example
```