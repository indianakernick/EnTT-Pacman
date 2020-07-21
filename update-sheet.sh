#!/bin/sh

alias Animera=/Users/indikernick/Library/Developer/Xcode/DerivedData/Animera-gzeagjhsrxxguqcoscwzymctmade/Build/Products/Debug/Animera.app/Contents/MacOS/Animera

Animera export << EOF
{
  "output name": "sprites",
  "output directory": "src/util",
  "generator": "cpp",
  "animations": [
    {
      "file": "animations/dot.animera",
      "name": ""
    },
    "animations/pacman.animera",
    "animations/scared.animera",
    {
      "file": "animations/maze.animera",
      "name": ""
    },
    {
      "file": "animations/ghost.animera",
      "name": "",
      "composite": false
    }
  ]
}
EOF
