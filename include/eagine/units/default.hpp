/**
 *  @file eagine/unit/default.hpp
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef EAGINE_UNITS_DEFAULT_1512222148_HPP
#define EAGINE_UNITS_DEFAULT_1512222148_HPP

#include "fwd.hpp"
#include "../identity.hpp"

namespace eagine {
namespace units {

template <typename U>
struct add_result<U, U>
 : identity<U>
{ };

template <typename U>
struct sub_result<U, U>
 : identity<U>
{ };

template <typename U>
struct is_convertible<U, U>
 : std::true_type
{ };

template <typename U>
struct value_conv<U, U>
{
	template <typename T>
	constexpr inline
	T operator ()(T v) const
	{
		return v;
	}
};

} // namespace units
} // namespace eagine

#endif //include guard

