#!/bin/sh
set -e

echo "Compiling for Linux..."

cp -u ../tools/merger/out/full/sfw.h sfw.h
cp -u ../tools/merger/out/full/sfw.cpp sfw.cpp
cp -u ../tools/merger/out/full/sfw_3rd.m sfw_3rd.m

mkdir -p build

ccache g++ -Wall -g -c sfw.cpp -o ./build/sfw.o
ccache g++ -Wall -g -c ./scene/scenes/main_menu_scene.cpp -o ./build/main_menu_scene.o
ccache g++ -Wall -g -c ./scene/scenes/game_scene.cpp -o ./build/game_scene.o
ccache g++ -Wall -g -c ./scene/scenes/pause_menu_scene.cpp -o ./build/pause_menu_scene.o
ccache g++ -Wall -g -c ./scene/scenes/game_over_scene.cpp -o ./build/game_over_scene.o
ccache g++ -Wall -g -c ./mapgen/map_generator.cpp -o ./build/map_generator.o
ccache g++ -Wall -g -c main.cpp -o ./build/main.o

ccache g++ -Wall -static-libgcc -static-libstdc++ -g \
    ./build/sfw.o \
    ./build/main_menu_scene.o \
    ./build/game_scene.o \
    ./build/pause_menu_scene.o \
    ./build/game_over_scene.o \
    ./build/map_generator.o \
    ./build/main.o \
    -lX11 -o game