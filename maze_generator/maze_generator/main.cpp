#include <cstdint>
#include <cstddef>
#include <limits>
#include <utility>
#include <string>
#include <fstream>
#include "PCG_generator.h"
#include "Array2D.h"
#include "Stack.h"
#include "Cell.h"
#include "Maze_generator.h"


















int main()
{
	constexpr const std::size_t num_cols = 5;
	constexpr const std::size_t num_rows = 5;
	constexpr auto maze = Maze_generator::make_maze<num_cols, num_rows>();
	constexpr auto rendered_maze = Maze_generator::solve(Maze_generator::render_maze(maze));

	for (std::size_t row = 0; row < num_rows * 2 + 1; ++row)
	{
		for (std::size_t col = 0; col < num_cols * 2 + 1; ++col)
		{
			const auto square = [&]() {
				switch (rendered_maze(col, row)) {
				case Maze_generator::WallType::Empty:      return " ";
				case Maze_generator::WallType::UpperLeft:  return "┌";
				case Maze_generator::WallType::Vertical:   return "│";//
				case Maze_generator::WallType::Horizontal: return "─";//
				case Maze_generator::WallType::UpperRight: return "┐";
				case Maze_generator::WallType::LowerLeft:  return "└";
				case Maze_generator::WallType::LowerRight: return "┘";
				case Maze_generator::WallType::RightTee:   return "├";//
				case Maze_generator::WallType::LeftTee:    return "┤";//
				case Maze_generator::WallType::UpTee:      return "┴";//
				case Maze_generator::WallType::DownTee:    return "┬";//
				case Maze_generator::WallType::FourWay:    return "┼";//
				case Maze_generator::WallType::Up:         return "╵";//
				case Maze_generator::WallType::Down:       return "╷";//
				case Maze_generator::WallType::Left:       return "╴";//
				case Maze_generator::WallType::Right:      return "╶";//
				case Maze_generator::WallType::Visited:    return "·";
				case Maze_generator::WallType::Used:       return "*";
				default: throw 0;
				}

				
			}();
			std::ofstream outfile;
			outfile.open("labirynt.txt", std::ios_base::app); // append instead of overwrite
			outfile << square;
			std::cout << square;
		}
		std::cout << '\n';
	}
}