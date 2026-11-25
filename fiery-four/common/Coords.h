//
// Created by Bendi on 11/24/2026.
//

#ifndef COORDS_H
#define COORDS_H

struct Coords
{
	short x;
	short y;

	constexpr bool operator==(const Coords& other) const noexcept
	{
		return x == other.x && y == other.y;
	}

	constexpr Coords operator+(const Coords& other) const noexcept
	{
		return {
			static_cast<short>(x + other.x),
			static_cast<short>(y + other.y)
		};
	}


	static constexpr unsigned int hash(const Coords& coords) noexcept
	{
		unsigned int h = static_cast<unsigned short>(coords.x);

		h ^= static_cast<unsigned short>(coords.y)
			 + 0x9e3779b9u + (h << 6) + (h >> 2); // Ez valami aranymetszet hókusz pókusz

		return h;
	}
};

#endif