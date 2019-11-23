#pragma once
namespace cx_alg
{
	template <class Forward_itr, class T>
	constexpr void fill(Forward_itr first, Forward_itr last, const T& value)
	{
		for (; first != last; first++)
			*first = value;
	}

	template <class Output_itr, class Size, class T>
	constexpr void fill_n(Output_itr first, Size count, const T& value)
	{
		for (Size i = 0; i < count; i++)
			*first++ = value
	}
}