/**
 *  @file eagine/units/unit/si/energy.hpp
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef EAGINE_UNITS_UNIT_SI_ENERGY_1512222148_HPP
#define EAGINE_UNITS_UNIT_SI_ENERGY_1512222148_HPP

#include "../../dim/energy.hpp"
#include "common.hpp"
#include "length.hpp"
#include "mass.hpp"
#include "time.hpp"

namespace eagine {
namespace units {

// joule
typedef unit<energy, si> joule;

template <>
struct unit_name<joule> {
    static constexpr const char mp_str[] = "joule";
};

template <>
struct unit_symbol<joule> {
    static constexpr const char mp_str[] = "J";
};

// derived
typedef make_scaled_unit_t<scales::kilo, joule> kilojoule;
typedef make_scaled_unit_t<scales::mega, joule> megajoule;
// TODO

} // namespace units
} // namespace eagine

#endif // include guard
