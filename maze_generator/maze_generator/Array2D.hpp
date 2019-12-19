#pragma once
#include <array>
namespace std { typedef unsigned int	size_t; }


template<typename Data, std::size_t Cols, std::size_t Rows>
struct Array2D
{
	constexpr Array2D() {}
	constexpr static auto rows();
	constexpr static auto cols();

	constexpr Data& operator()(const std::size_t col, const std::size_t row);
	constexpr const Data& operator()(const std::size_t col, const std::size_t row) const;

	std::array<Data, Cols * Rows> m_data{};
};
