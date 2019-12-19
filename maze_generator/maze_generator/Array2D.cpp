#include "Array2D.hpp"

template<typename Data, std::size_t Cols, std::size_t Rows>
inline constexpr auto Array2D<Data, Cols, Rows>::rows() { return Rows; }

template<typename Data, std::size_t Cols, std::size_t Rows>
inline constexpr auto Array2D<Data, Cols, Rows>::cols() { return Cols; }

template<typename Data, std::size_t Cols, std::size_t Rows>
inline constexpr Data& Array2D<Data, Cols, Rows>::operator()(const std::size_t col, const std::size_t row)
{
	return m_data[col + (row * Cols)];
}

template<typename Data, std::size_t Cols, std::size_t Rows>
constexpr const Data& Array2D<Data, Cols, Rows>::operator()(const std::size_t col, const std::size_t row) const
{
	return m_data[col + (row * Cols)];
}