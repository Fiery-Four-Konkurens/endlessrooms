#!/bin/sh

echo "Compiling & starting game for Linux..."

cp -u ../tools/merger/out/full/sfw.h sfw.h
cp -u ../tools/merger/out/full/sfw.cpp sfw.cpp
cp -u ../tools/merger/out/full/sfw_3rd.m sfw_3rd.m

ccache g++ -Wall -g -c sfw.cpp -o sfw.o
ccache g++ -Wall -g -c main_menu_scene.cpp -o main_menu_scene.o
ccache g++ -Wall -g -c game_scene.cpp -o game_scene.o
ccache g++ -Wall -g -c pause_menu_scene.cpp -o pause_menu_scene.o
ccache g++ -Wall -g -c game_over_scene.cpp -o game_over_scene.o
ccache g++ -Wall -g -c main.cpp -o main.o

ccache g++ -Wall -static-libgcc -static-libstdc++ -g sfw.o main_menu_scene.o game_scene.o pause_menu_scene.o game_over_scene.o main.o -lX11 -o game

./game
