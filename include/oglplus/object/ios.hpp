/**
 *  @file oglplus/object/ios.hpp
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#ifndef OGLPLUS_OBJECT_IOS_1509260923_HPP
#define OGLPLUS_OBJECT_IOS_1509260923_HPP

#include "gl_name.hpp"
#include "../enum_types.hpp"
#include "../enum_value_names.hpp"
#include <iostream>

namespace oglplus {

static inline
std::ostream&
operator << (std::ostream& out, const any_object_name& aon)
{
	return out
		<< enum_value_name(object_type(aon._type))
		<< '(' <<aon._name << ')';
}

} // namespace oglplus

#endif // include guard