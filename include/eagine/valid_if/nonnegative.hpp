/**
 *  @file eagine/valid_if/nonnegative.hpp
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef EAGINE_VALID_IF_NONNEGATIVE_1509260923_HPP
#define EAGINE_VALID_IF_NONNEGATIVE_1509260923_HPP

#include "decl.hpp"

namespace eagine {

// nonnegative
template <typename T>
struct valid_if_nonneg_policy {
    constexpr bool operator()(T value) const noexcept {
	return value >= T(0);
    }

    struct do_log {
	template <typename X>
	constexpr inline do_log(X&&) noexcept {
	}

	template <typename Log>
	void operator()(Log& log, const T& v) const {
	    log << "Value " << v << ", "
		<< "less then zero "
		<< "is invalid";
	}
    };
};

template <typename T>
using valid_if_nonnegative = valid_if<T, valid_if_nonneg_policy<T>>;

} // namespace eagine

#endif // include guard
