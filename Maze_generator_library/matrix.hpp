#pragma once
#include<array>
namespace maze_gen
{

	template <typename maze_particle_type, auto size_x, auto size_y, auto size_z>
	class matrix
	{
	public:
		constexpr matrix();
		constexpr static auto rows();
		constexpr static auto columns();
		constexpr static auto deep();
		constexpr maze_particle_type &operator()(const size_t x, const size_t y, const size_t z);
		constexpr const maze_particle_type &operator()(const size_t x, const size_t y, const size_t z) const;

	private:
		size_t m_x;
		size_t m_y;
		size_t m_z;
		std::array<maze_particle_type, m_x*m_y*m_z> matrix_3d;
	};

}