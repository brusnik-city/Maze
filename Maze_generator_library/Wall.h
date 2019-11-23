#pragma once

enum class Wall
{
	None,
	Vertical_wall,
	Horizontal_wall,
	Upper_half,
	Lover_half,
	Left_half,
	Right_half,
	Upper_left_corner,
	Upper_right_corner,
	Lover_left_corner,
	Lover_right_corner,
	Tripple_left_connection,
	Tripple_right_connection,
	Tripple_upper_connection,
	Tripple_lover_connection,
	Cross_connection,
	Visited,
	Part_of_way
};