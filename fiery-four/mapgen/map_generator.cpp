//
// Created by Bendi on 11/24/2026.
//

#include "map_generator.h"

namespace
{
	constexpr unsigned int DOOR_CHANCE = 55;
	constexpr unsigned int MIN_ENEMIES = 1; // FIT IN 3 BITS!
	constexpr unsigned int MAX_ENEMIES = 7;
	constexpr unsigned int DIRECTION_COUNT = 4;

    constexpr Coords offsets[DIRECTION_COUNT] =
    {
        { 1,  0}, // RIGHT
        {-1,  0}, // LEFT
        { 0,  1}, // UP
        { 0, -1}  // DOWN
    };

    constexpr Direction opposite(Direction dir)
    {
        return static_cast<Direction>(dir ^ 1);
    }
}

MapGenerator::MapGenerator(unsigned int seed)
    : random(seed)
{
}

void MapGenerator::generateRoom(void* arg)
{
    GenerationTask& task =
        *static_cast<GenerationTask*>(arg);

    if (!task.required)
        return;

    Room room{};

	Random random(task.seed);

    // Generate doors.
    for (unsigned int i = 0; i < DIRECTION_COUNT; ++i)
    {
        Direction dir = static_cast<Direction>(i);
        unsigned int bit = 1u << i;

        if (task.fixed_mask & bit)
        {
            room.setDoor(dir, (task.door_mask & bit) != 0);
        }
        else
        {
        	room.setDoor(dir, random.chance(DOOR_CHANCE));
        }
    }

    // Generate 1-7 enemies.
    room.enemy_count = random.range(MIN_ENEMIES, MAX_ENEMIES);
    room.visited = 0;

    task.result = room;
}

void MapGenerator::generateNeighbours(
    HashMap<Coords, Room, Coords>& map,
    Coords coords)
{
    const Room* current = map.getptr(coords);

    if (!current)
        return;

    GenerationTask tasks[DIRECTION_COUNT]{};
    Thread threads[DIRECTION_COUNT];

    // PHASE 1: Prepare tasks.

    for (unsigned int i = 0; i < DIRECTION_COUNT; ++i)
    {
        Direction dir = static_cast<Direction>(i);
        GenerationTask& task = tasks[i];

        task.coords = coords + offsets[i];

        // Skip directions without a door.
        if (!current->hasDoor(dir))
            continue;

        // Do not overwrite existing rooms.
        if (map.has(task.coords))
            continue;

        task.required = true;

        task.seed = Coords::hash(task.coords) ^ random.next();

        // Check all existing neighbours of the new room.
        for (unsigned int j = 0; j < DIRECTION_COUNT; ++j)
        {
            Coords adjacent = task.coords + offsets[j];

            const Room* neighbour = map.getptr(adjacent);

            if (!neighbour)
                continue;

            Direction neighbour_dir =
                static_cast<Direction>(j);

            unsigned int bit = 1u << j;

            task.fixed_mask |= bit;

            if (neighbour->hasDoor(opposite(neighbour_dir)))
                task.door_mask |= bit;
        }
    }

    // PHASE 2: Start worker threads.

    for (unsigned int i = 0; i < DIRECTION_COUNT; ++i)
    {
        if (tasks[i].required)
            threads[i].start(generateRoom, &tasks[i]);
    }

    // PHASE 3: Synchronize.

    for (unsigned int i = 0; i < DIRECTION_COUNT; ++i)
    {
        if (tasks[i].required)
            threads[i].wait_to_finish();
    }

    // PHASE 4: Insert generated rooms.

    for (unsigned int i = 0; i < DIRECTION_COUNT; ++i)
    {
        if (tasks[i].required)
            map.insert(tasks[i].coords, tasks[i].result);
    }

}