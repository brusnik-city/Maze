#pragma once
struct Cell
{
	constexpr Cell()		= default;
	bool upper_wall_exist	= false;
	bool bottom_wall_exist	= false;
	bool left_wall_exist	= false;
	bool right_wall_exist	= false;
	bool is_visited			= false;
};