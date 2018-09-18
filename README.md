# EnTT-Example

[![Build Status](https://travis-ci.org/Kerndog73/EnTT-Example.svg?branch=master)](https://travis-ci.org/Kerndog73/EnTT-Example)
[![Build Status](https://ci.appveyor.com/api/projects/status/5ndjklgbe42b0q9b?svg=true)](https://ci.appveyor.com/project/Kerndog73/entt-example)

An example of how to use the ECS part of the [EnTT Framework](https://github.com/skypjack/entt)

If you're on MacOS or Linux, we'll use ncurses which is probably already installed on your system. If you're on windows, we'll build pdcurses from sources. All other dependencies are bundled in the repo.

```bash
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
./example
```