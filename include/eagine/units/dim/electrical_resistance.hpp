/**
 *  @file eagine/unit/dim/electrical_resistance.hpp
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef EAGINE_UNITS_DIM_ELECTRICAL_RESISTANCE_1512222148_HPP
#define EAGINE_UNITS_DIM_ELECTRICAL_RESISTANCE_1512222148_HPP

#include "electric_tension.hpp"

namespace eagine {
namespace units {

typedef decltype(electric_tension() / electric_current()) electrical_resistance;

template <>
struct dim_name<electrical_resistance> {
    static constexpr const char mp_str[] = "electrical resistance";
};

} // namespace units
} // namespace eagine

#endif // include guard
