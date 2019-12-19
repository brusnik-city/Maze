#pragma once
namespace std { typedef unsigned int	size_t; }

struct Loc
{
	std::size_t col = 0;
	std::size_t row = 0;

	constexpr Loc(const std::size_t t_col, const std::size_t t_row)
		: col(t_col), row(t_row)
	{
	}

	constexpr Loc() = default;
};