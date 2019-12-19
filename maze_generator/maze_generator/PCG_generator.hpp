#pragma once
#include <iostream>


struct PCG_generator
{
	using  result_type = std::uint32_t;
	struct pcg32_random_t
	{
		constexpr std::uint64_t seed();
		std::uint64_t state = 0;
		std::uint64_t inc = seed();

	};
	pcg32_random_t rng;

	static result_type constexpr min();
	static result_type constexpr max();
	constexpr result_type operator()();

private:

	constexpr result_type pcg32_random_r();

};