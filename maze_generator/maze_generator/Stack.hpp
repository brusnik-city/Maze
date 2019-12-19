#pragma once
namespace std {typedef unsigned int	size_t;}

template<typename T, std::size_t Size>
struct Stack
{
	T m_data[Size]{};
	std::size_t pos = 0;

	template<typename ... Arg>
	void constexpr emplace_back(Arg&&... arg);
	constexpr T pop_back();
	constexpr bool empty() const;
	constexpr std::size_t size() const;
};