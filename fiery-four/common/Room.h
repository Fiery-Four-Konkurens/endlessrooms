//
// Created by Bendi on 11/24/2026.
//

#ifndef ROOM_H
#define ROOM_H

enum Direction : unsigned char
{
	RIGHT = 0, //00
	LEFT  = 1, //01
	UP    = 2, //10
	DOWN  = 3  //11
};

struct Room
{
	unsigned char right       : 1;
	unsigned char left        : 1;
	unsigned char up          : 1;
	unsigned char down        : 1;
	unsigned char visited     : 1;
	unsigned char enemy_count : 3; //000 - 111 = 0 - 7


	constexpr bool hasDoor(Direction dir) const noexcept
	{
		switch (dir)
		{
			case RIGHT: return right;
			case LEFT:  return left;
			case UP:    return up;
			case DOWN:  return down;
		}

		return false;
	}

	constexpr void setDoor(Direction dir, bool value) noexcept
	{
		switch (dir)
		{
			case RIGHT: right = value; break;
			case LEFT:  left  = value; break;
			case UP:    up    = value; break;
			case DOWN:  down  = value; break;
		}
	}
};

static_assert(sizeof(Room) == 1, "Invalid Room size");

#endif