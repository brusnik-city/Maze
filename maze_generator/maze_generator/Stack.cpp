#include "Stack.hpp"

template< typename T, std::size_t Size >
template<typename ... Arg>
void constexpr Stack<T,Size>::emplace_back(Arg&&... arg)
{
	m_data[pos] = T{ std::forward<Arg>(arg)... };
	++pos;
}

template< typename T, std::size_t Size >
constexpr T Stack<T,Size>::pop_back()
{
	--pos;
	return m_data[pos];
}

template< typename T, std::size_t Size >
constexpr bool Stack<T,Size>::empty() const
{
	return pos == 0;
}

template< typename T, std::size_t Size >
constexpr std::size_t Stack<T,Size>::size() const
{
	return pos;
}