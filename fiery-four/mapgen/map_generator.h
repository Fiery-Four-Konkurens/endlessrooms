//
// Created by Bendi on 11/24/2026.
//
#ifndef KONKURENS_GAME_MAP_GENERATOR_H
#define KONKURENS_GAME_MAP_GENERATOR_H

#include "../common/Coords.h"
#include "../common/Room.h"
#include "../common/Random.h"
#include "../sfw.h"

class MapGenerator
{
public:
	explicit MapGenerator(unsigned int seed);

	void generateNeighbours(
		HashMap<Coords, Room, Coords>& map,
		Coords coords
	);

private:
	struct GenerationTask
	{
		Coords coords;
		Room result;

		unsigned int seed;

		unsigned char fixed_mask;
		unsigned char door_mask;

		bool required;
	};

	static void generateRoom(void* arg);

	Random random;
};

#endif