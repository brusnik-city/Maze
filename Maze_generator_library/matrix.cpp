#include "matrix.hpp"
namespace maze_gen
{
	template<typename maze_particle_type, auto size_x, auto size_y, auto size_z>
	inline constexpr matrix<maze_particle_type, size_x, size_y, size_z>::matrix()
	{
		cx_alg::fill(matrix_3d.begin(), matrix_3d.end(), 0);
	}
	template<typename maze_particle_type, auto size_x, auto size_y, auto size_z>
	inline constexpr auto matrix<maze_particle_type, size_x, size_y, size_z>::rows()
	{
	}
	template<typename maze_particle_type, auto size_x, auto size_y, auto size_z>
	inline constexpr auto matrix<maze_particle_type, size_x, size_y, size_z>::columns()
	{
	}
	template<typename maze_particle_type, auto size_x, auto size_y, auto size_z>
	inline constexpr auto matrix<maze_particle_type, size_x, size_y, size_z>::deep()
	{
	}
	template<typename maze_particle_type, auto size_x, auto size_y, auto size_z>
	inline constexpr maze_particle_type & matrix<maze_particle_type, size_x, size_y, size_z>::operator()(const size_t x, const size_t y, const size_t z)
	{
		// TODO: insert return statement here
	}
	template<typename maze_particle_type, auto size_x, auto size_y, auto size_z>
	inline constexpr const maze_particle_type & matrix<maze_particle_type, size_x, size_y, size_z>::operator()(const size_t x, const size_t y, const size_t z) const
	{
		// TODO: insert return statement here
	}
}
