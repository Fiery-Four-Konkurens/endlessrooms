//
// Created by Bendi on 11/25/2026.
//

#ifndef KONKURENS_GAME_RANDOM_H
#define KONKURENS_GAME_RANDOM_H
class Random {
	public:

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
