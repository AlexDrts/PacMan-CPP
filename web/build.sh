#!/usr/bin/env bash
# Builds the browser version of the game into ./site
# Needs Zig (https://ziglang.org) or: pip install ziglang && ZIG="python3 -m ziglang" web/build.sh
set -euo pipefail
cd "$(dirname "$0")/.."
mkdir -p site
${ZIG:-zig} c++ -target wasm32-wasi -mexec-model=reactor -O2 -fno-exceptions -s -I. \
  web/main_web.cpp web/console_shim.cpp project_02.10.2025.cpp Entities.cpp \
  -o site/pacman.wasm
cp web/index.html site/
cp Pac-Man-intro-music.wav PacMan-Death-Sound-Effect-HD.wav site/
echo "Built: site/"
