#include "Maze_generator.hpp"
#include "Stack.h"
#include "PCG_generator.h"

template<typename T, typename Gen>
static inline constexpr auto Maze_generator::distribution(Gen& g, T min, T max)
{
	const auto range = max - min + 1;
	const auto bias_remainder = std::numeric_limits<T>::max() % range;
	const auto unbiased_max = std::numeric_limits<T>::max() - bias_remainder - 1;

	auto r = g();
	for (; r > unbiased_max; r = g());

	return (r % range) + min;
}

template<std::size_t num_cols, std::size_t num_rows>
static inline constexpr Array2D<Cell, num_cols, num_rows> Maze_generator::make_maze()
{

	PCG_generator pcg;

	Array2D<Cell, num_cols, num_rows> M;

	//// Set starting row and column
	std::size_t c = 0;
	std::size_t r = 0;
	Stack<Loc, num_cols * num_rows> history;
	history.emplace_back(c, r); // The history is the stack of visited locations

								//// Trace a path though the cells of the maze and open walls along the path.
								//// We do this with a while loop, repeating the loop until there is no history, 
								//// which would mean we backtracked to the initial start.
	while (!history.empty())
	{
		M(c, r).visited = true;

		Stack<char, 4> check{};

		// check if the adjacent cells are valid for moving to
		if (c > 0 && M(c - 1, r).visited == false) {
			check.emplace_back('L');
		}
		if (r > 0 && M(c, r - 1).visited == false) {
			check.emplace_back('U');
		}
		if (c < num_cols - 1 && M(c + 1, r).visited == false) {
			check.emplace_back('R');
		}
		if (r < num_rows - 1 && M(c, r + 1).visited == false) {
			check.emplace_back('D');
		}

		if (!check.empty()) { // If there is a valid cell to move to.
							  // Mark the walls between cells as open if we move

			history.emplace_back(c, r);

			for (auto num_pops = distribution(pcg, std::size_t(0), check.size() - 1); num_pops > 0; --num_pops)
			{
				check.pop_back();
			}

			switch (check.pop_back()) {
			case 'L':
				M(c, r).left_open = true;
				--c;
				M(c, r).right_open = true;
				break;

			case 'U':
				M(c, r).up_open = true;
				--r;
				M(c, r).down_open = true;
				break;

			case 'R':
				M(c, r).right_open = true;
				++c;
				M(c, r).left_open = true;
				break;

			case 'D':
				M(c, r).down_open = true;
				++r;
				M(c, r).up_open = true;
				break;
			}
		}
		else {
			// If there are no valid cells to move to.
			// retrace one step back in history if no move is possible
			const auto last = history.pop_back();
			c = last.col;
			r = last.row;
		}
	}

	// Open the walls at the start and finish
	M(0, 0).left_open = true;
	M(num_cols - 1, num_rows - 1).right_open = true;

	return M;
}

template<std::size_t num_cols, std::size_t num_rows>
static inline constexpr Array2D<Maze_generator::WallType, num_cols * 2 + 1, num_rows * 2 + 1> Maze_generator::render_maze(const Array2D<Cell, num_cols, num_rows>& maze_data)
{
	Array2D<WallType, num_cols * 2 + 1, num_rows * 2 + 1> result{};


	for (std::size_t col = 0; col < num_cols; ++col)
	{
		for (std::size_t row = 0; row < num_rows; ++row)
		{
			const auto render_col = col * 2 + 1;
			const auto render_row = row * 2 + 1;

			const auto& cell = maze_data(col, row);

			// upper
			if (!cell.up_open) { result(render_col, render_row - 1) = WallType::Horizontal; }

			// left
			if (!cell.left_open) { result(render_col - 1, render_row) = WallType::Vertical; }

			// right
			if (!cell.right_open) { result(render_col + 1, render_row) = WallType::Vertical; }

			// lower
			if (!cell.down_open) { result(render_col, render_row + 1) = WallType::Horizontal; }
		}
	}

	for (std::size_t col = 0; col < result.cols(); col += 2)
	{
		for (std::size_t row = 0; row < result.rows(); row += 2)
		{
			const auto up = (row == 0) ? false : result(col, row - 1) != WallType::Empty;
			const auto left = (col == 0) ? false : result(col - 1, row) != WallType::Empty;
			const auto right = (col == num_cols * 2) ? false : result(col + 1, row) != WallType::Empty;
			const auto down = (row == num_rows * 2) ? false : result(col, row + 1) != WallType::Empty;

			if (up && right && down && left) {
				result(col, row) = WallType::FourWay;
			}
			if (up && right && down && !left) {
				result(col, row) = WallType::RightTee;
			}
			if (up && right && !down && left) {
				result(col, row) = WallType::UpTee;
			}
			if (up && !right && down && left) {
				result(col, row) = WallType::LeftTee;
			}
			if (!up && right && down && left) {
				result(col, row) = WallType::DownTee;
			}

			if (up && right && !down && !left) {
				result(col, row) = WallType::LowerLeft;
			}
			if (up && !right && !down && left) {
				result(col, row) = WallType::LowerRight;
			}
			if (!up && !right && down && left) {
				result(col, row) = WallType::UpperRight;
			}
			if (!up && right && down && !left) {
				result(col, row) = WallType::UpperLeft;
			}
			if (!up && right && !down && left) {
				result(col, row) = WallType::Horizontal;
			}
			if (up && !right && down && !left) {
				result(col, row) = WallType::Vertical;
			}


			if (up && !right && !down && !left) {
				result(col, row) = WallType::Up;
			}
			if (!up && right && !down && !left) {
				result(col, row) = WallType::Right;
			}
			if (!up && !right && down && !left) {
				result(col, row) = WallType::Down;
			}
			if (!up && !right && !down && left) {
				result(col, row) = WallType::Left;
			}
		}
	}


	return result;
}

template<typename T>
static inline constexpr auto Maze_generator::solve(T maze)
{
	constexpr auto num_cols = maze.cols();
	constexpr auto num_rows = maze.rows();

	size_t row = 1;
	size_t col = 0;

	Stack<Loc, num_cols * num_rows> history;

	history.emplace_back(col, row);
	while (row != maze.rows() - 2 || col != maze.cols() - 2)
	{
		maze(col, row) = WallType::Visited;

		// check if the adjacent cells are valid for moving to
		if (col < num_cols - 1 && maze(col + 1, row) == WallType::Empty) {
			++col;
			history.emplace_back(col, row);
		}
		else if (row < num_rows - 1 && maze(col, row + 1) == WallType::Empty) {
			++row;
			history.emplace_back(col, row);
		}
		else if (col > 0 && maze(col - 1, row) == WallType::Empty) {
			--col;
			history.emplace_back(col, row);
		}
		else if (row > 0 && maze(col, row - 1) == WallType::Empty) {
			--row;
			history.emplace_back(col, row);
		}
		else {
			// If there are no valid cells to move to.
			// retrace one step back in history if no move is possible
			const auto last = history.pop_back();
			col = last.col;
			row = last.row;
		}
	}

	while (!history.empty())
	{
		const auto last = history.pop_back();
		maze(last.col, last.row) = WallType::Used;
	}

	return maze;
}
