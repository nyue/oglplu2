/**
 *  @file eagine/valid_if/lt_size.hpp
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef EAGINE_VALID_IF_LT_SIZE_1509260923_HPP
#define EAGINE_VALID_IF_LT_SIZE_1509260923_HPP

#include "in_class.hpp"

namespace eagine {

// valid if less than container.size()
template <typename T, typename C>
struct valid_if_lt_size_policy
{
	bool operator()(T x, const C& c) const
	{
		return x < c.size();
	}

	struct do_log
	{
		inline
		do_log(const valid_if_lt_size_policy<T, C>&)
		noexcept
		{ }

		template <typename Log>
		void operator ()(Log& log, const T& v, const C& c) const
		{
			log	<< "Value " << v << ", "
				<< "not less than c.size() = "
				<< c.size() << " is invalid";
		}
	};

	struct abort
	{
		[[noreturn]]
		void operator ()(void) const
		noexcept
		{
			EAGINE_ABORT(
			"Value not less than c.size() is invalid"
			);
		}
	};
};

template <typename C, typename T>
using valid_if_lt_size =
	in_class_valid_if<T, C, valid_if_lt_size_policy<T, C>>;

} // namespace eagine

#endif // include guard