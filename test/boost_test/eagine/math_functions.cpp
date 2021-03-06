/**
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#include <eagine/math/functions.hpp>
#define BOOST_TEST_MODULE EAGINE_math_functions
#include "../unit_test_begin.inl"

BOOST_AUTO_TEST_SUITE(math_function_tests)

static eagine::test_random_generator rg;

template <typename T>
T
rndval(void) {
    return rg.get<T>(-1000, 1000);
}

template <typename T, typename... P>
void
test_math_function_min_max_Tv(P... v) {
    T a[sizeof...(P)] = {v...};

    using namespace eagine;

    T minv = math::minimum(v...);
    T maxv = math::maximum(v...);

    for(T x : a) {
	BOOST_CHECK(x >= minv);
	BOOST_CHECK(x <= maxv);
    }
}

template <typename T>
void
test_math_function_minimum_T(void) {
    test_math_function_min_max_Tv<T>(rndval<T>(), rndval<T>());
    test_math_function_min_max_Tv<T>(rndval<T>(), rndval<T>(), rndval<T>());
    test_math_function_min_max_Tv<T>(
      rndval<T>(), rndval<T>(), rndval<T>(), rndval<T>());
    test_math_function_min_max_Tv<T>(
      rndval<T>(), rndval<T>(), rndval<T>(), rndval<T>(), rndval<T>());
    test_math_function_min_max_Tv<T>(rndval<T>(),
      rndval<T>(),
      rndval<T>(),
      rndval<T>(),
      rndval<T>(),
      rndval<T>(),
      rndval<T>(),
      rndval<T>(),
      rndval<T>(),
      rndval<T>(),
      rndval<T>(),
      rndval<T>());
}

BOOST_AUTO_TEST_CASE(math_functions_min_max) {
    test_math_function_minimum_T<short>();
    test_math_function_minimum_T<int>();
    test_math_function_minimum_T<float>();
    test_math_function_minimum_T<double>();
}

BOOST_AUTO_TEST_CASE(math_functions_factorial) {
    using namespace eagine::math;

    BOOST_CHECK_EQUAL(factorial(-2), 1);
    BOOST_CHECK_EQUAL(factorial(-1), 1);

    BOOST_CHECK_EQUAL(factorial(0), 1);
    BOOST_CHECK_EQUAL(factorial(1), 1);
    BOOST_CHECK_EQUAL(factorial(2), 2);
    BOOST_CHECK_EQUAL(factorial(3), 6);
    BOOST_CHECK_EQUAL(factorial(4), 24);
    BOOST_CHECK_EQUAL(factorial(5), 120);
    BOOST_CHECK_EQUAL(factorial(6), 720);
    BOOST_CHECK_EQUAL(factorial(7), 5040);

    BOOST_CHECK_EQUAL(factorial(12), 479001600);
}

BOOST_AUTO_TEST_CASE(math_functions_binomial) {
    using namespace eagine::math;

    BOOST_CHECK_EQUAL(binomial(-1, 0), 0);

    BOOST_CHECK_EQUAL(binomial(0, 0), 1);

    for(int n = 1; n < 12; ++n) {
	BOOST_CHECK_EQUAL(binomial(n, -1), 0);
	BOOST_CHECK_EQUAL(binomial(n, 0), 1);

	for(int k = 1; k < n; ++k) {
	    BOOST_CHECK_EQUAL(
	      binomial(n, k), binomial(n - 1, k - 1) + binomial(n - 1, k));
	}

	BOOST_CHECK_EQUAL(binomial(n, n), 1);
	BOOST_CHECK_EQUAL(binomial(n, n + 1), 0);
    }
}

template <typename T>
void
test_math_functions_bezier_1(int l) {
    using eagine::math::bezier;

    for(int i = 0; i < l; ++i) {
	T t = rg.get<T>(0, 1);
	T x = rg.get<T>(-1000, 1000);

	BOOST_CHECK_EQUAL(bezier(t, x), x);
    }
}

template <typename T>
void
test_math_functions_bezier_2(int l) {
    using eagine::math::bezier;

    for(int i = 0; i < l; ++i) {
	T t = rg.get<T>(0, 1);
	T x = rg.get<T>(-1000, 1000);
	T y = rg.get<T>(-1000, 1000);

	BOOST_CHECK_EQUAL(bezier(t, x, y), (1 - t) * x + t * y);
    }
}

template <typename T>
void
test_math_functions_bezier_3(int l) {
    using eagine::math::bezier;

    for(int i = 0; i < l; ++i) {
	T t = rg.get<T>(0, 1);
	T x = rg.get<T>(-1000, 1000);
	T y = rg.get<T>(-1000, 1000);
	T z = rg.get<T>(-1000, 1000);

	BOOST_CHECK_CLOSE(bezier(t, x, y, z),
	  (1 - t) * (1 - t) * x + 2 * (1 - t) * t * y + t * t * z,
	  0.06);
    }
}

template <typename T>
void
test_math_functions_bezier_4(int l) {
    using eagine::math::bezier;

    for(int i = 0; i < l; ++i) {
	T t = rg.get<T>(0, 1);
	T v0 = rg.get<T>(-1000, 1000);
	T v1 = rg.get<T>(-1000, 1000);
	T v2 = rg.get<T>(-1000, 1000);
	T v3 = rg.get<T>(-1000, 1000);

	BOOST_CHECK_CLOSE(bezier(t, v0, v1, v2, v3),
	  (1 - t) * (1 - t) * (1 - t) * v0 + 3 * (1 - t) * (1 - t) * t * v1
	    + 3 * (1 - t) * t * t * v2 + t * t * t * v3,
	  0.6);
    }
}

template <typename T>
void
test_math_functions_bezier_5(int l) {
    using eagine::math::bezier;

    for(int i = 0; i < l; ++i) {
	T t = rg.get<T>(0, 1);
	T v0 = rg.get<T>(-1000, 1000);
	T v1 = rg.get<T>(-1000, 1000);
	T v2 = rg.get<T>(-1000, 1000);
	T v3 = rg.get<T>(-1000, 1000);
	T v4 = rg.get<T>(-1000, 1000);

	BOOST_CHECK_CLOSE(bezier(t, v0, v1, v2, v3, v4),
	  (1 - t) * (1 - t) * (1 - t) * (1 - t) * v0
	    + 4 * (1 - t) * (1 - t) * (1 - t) * t * v1
	    + 6 * (1 - t) * (1 - t) * t * t * v2 + 4 * (1 - t) * t * t * t * v3
	    + t * t * t * t * v4,
	  0.6);
    }
}

template <typename T>
void
test_math_functions_bezier(int l) {
    test_math_functions_bezier_1<T>(l);
    test_math_functions_bezier_2<T>(l);
    test_math_functions_bezier_3<T>(l);
    test_math_functions_bezier_4<T>(l);
    test_math_functions_bezier_5<T>(l);
}

BOOST_AUTO_TEST_CASE(math_functions_bezier) {
    test_math_functions_bezier<float>(100);
    test_math_functions_bezier<double>(100);
}

// TODO

BOOST_AUTO_TEST_SUITE_END()

#include "../unit_test_end.inl"
