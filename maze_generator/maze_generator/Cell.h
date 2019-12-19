#pragma once
struct Cell
{
	constexpr Cell() = default;
	bool left_open = false;
	bool right_open = false;
	bool up_open = false;
	bool down_open = false;
	bool visited = false;
};