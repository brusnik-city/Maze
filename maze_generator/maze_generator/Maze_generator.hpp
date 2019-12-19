#pragma once
#include "Array2D.h"
#include "Cell.h"
#include "Loc.h"

class Maze_generator
{
public:
	enum class WallType
	{
		Empty,
		UpperLeft,
		Vertical,
		Horizontal,
		UpperRight,
		LowerLeft,
		LowerRight,
		RightTee,
		LeftTee,
		UpTee,
		DownTee,
		FourWay,
		Up,
		Down,
		Left,
		Right,
		Visited,
		Used
	};

	template<typename T, typename Gen>
	static constexpr auto distribution(Gen& g, T min, T max);

	template<std::size_t num_cols, std::size_t num_rows>
	static constexpr Array2D<Cell, num_cols, num_rows> make_maze();


	template<std::size_t num_cols, std::size_t num_rows>
	static constexpr Array2D<WallType, num_cols * 2 + 1, num_rows * 2 + 1> render_maze(const Array2D<Cell, num_cols, num_rows>& maze_data);

	template<typename T>
	static constexpr auto solve(T maze);


};
