#include "PCG_generator.hpp"

inline constexpr std::uint64_t PCG_generator::pcg32_random_t::seed()
{
	std::uint64_t shifted = 0;

	for (const auto c : __TIME__)
	{
		shifted <<= 8;
		shifted |= c;
	}

	return shifted;
}

inline constexpr PCG_generator::result_type PCG_generator::min()
{
	return std::numeric_limits<result_type>::min();
}

inline constexpr PCG_generator::result_type PCG_generator::max()
{
	return std::numeric_limits<result_type>::min();
}

inline constexpr PCG_generator::result_type PCG_generator::operator()()
{
	return pcg32_random_r();
}

inline constexpr PCG_generator::result_type PCG_generator::pcg32_random_r()
{
	std::uint64_t oldstate = rng.state;
	// Advance internal state
	rng.state = oldstate * 6364136223846793005ULL + (rng.inc | 1);
	// Calculate output function (XSH RR), uses old state for max ILP
	std::uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
	std::uint32_t rot = oldstate >> 59u;
	return (xorshifted >> rot) | (xorshifted << ((rot) & 31));
}

