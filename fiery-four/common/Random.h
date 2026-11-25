//
// Created by Bendi on 11/25/2026.
//

#ifndef KONKURENS_GAME_RANDOM_H
#define KONKURENS_GAME_RANDOM_H
class Random {
private:
	unsigned int state;

public:
	explicit Random(unsigned int seed)
		: state(seed == 0 ? 1u : seed) {
	}

	unsigned int next() {
		state ^= state << 13;
		state ^= state >> 17;
		state ^= state << 5;

		return state;
	}

	unsigned int range(unsigned int min, unsigned int max)
	{
		return min + next() % (max - min + 1);
	}

	bool chance(unsigned int percentage)
	{
		return next() % 100u < percentage;
	}

	// GCC és Clang alatt: __builtin_ia32_rdtsc()
	// MSVC alatt: __rdtsc()

	static unsigned int generateWorldSeed() {
		#if defined(_MSC_VER)
				unsigned long long ticks = __rdtsc();
		#else
				unsigned long long ticks = __builtin_ia32_rdtsc();
		#endif
				return static_cast<unsigned int>(ticks ^ (ticks >> 32));
	}

};
#endif //KONKURENS_GAME_RANDOM_H
