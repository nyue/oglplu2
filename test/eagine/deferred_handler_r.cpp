/*
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EAGINE_deferred_handler
#include <boost/test/unit_test.hpp>

#include <eagine/deferred_handler.hpp>

void test_increment(int*& pi)
{
	++(*pi);
}

eagine::deferred_handler<int*> get_handler(int* pi)
{
	return {test_increment, pi};
}

BOOST_AUTO_TEST_SUITE(deferred_handler)

BOOST_AUTO_TEST_CASE(deferred_handler_1)
{
	using namespace eagine;

	deferred_handler<int*> dh;

	BOOST_CHECK_EQUAL(!dh, true);
	BOOST_CHECK_EQUAL(bool(dh), false);
}

BOOST_AUTO_TEST_CASE(deferred_handler_2)
{
	using namespace eagine;
	int i = 0;

	BOOST_CHECK_EQUAL(i, 0);
	{
		deferred_handler<int*> dh(test_increment, &i);

		BOOST_CHECK_EQUAL(!dh, false);
		BOOST_CHECK_EQUAL(bool(dh), true);
		BOOST_CHECK_EQUAL(i, 0);
	}
	BOOST_CHECK_EQUAL(i, 1);
}

BOOST_AUTO_TEST_CASE(deferred_handler_3)
{
	using namespace eagine;
	int i = 0;

	BOOST_CHECK_EQUAL(i, 0);
	{
		deferred_handler<int*> dh = get_handler(&i);

		BOOST_CHECK_EQUAL(!dh, false);
		BOOST_CHECK_EQUAL(bool(dh), true);
		BOOST_CHECK_EQUAL(i, 0);
	}
	BOOST_CHECK_EQUAL(i, 1);
	{
		deferred_handler<int*> dh = get_handler(&i);

		BOOST_CHECK_EQUAL(!dh, false);
		BOOST_CHECK_EQUAL(bool(dh), true);
		BOOST_CHECK_EQUAL(i, 1);
	}
	BOOST_CHECK_EQUAL(i, 2);
}

BOOST_AUTO_TEST_CASE(deferred_handler_cancel)
{
	using namespace eagine;
	int i = 0;

	BOOST_CHECK_EQUAL(i, 0);
	{
		deferred_handler<int*> dh = get_handler(&i);

		BOOST_CHECK_EQUAL(!dh, false);
		BOOST_CHECK_EQUAL(bool(dh), true);
		BOOST_CHECK_EQUAL(i, 0);

		dh.cancel();

		BOOST_CHECK_EQUAL(!dh, true);
		BOOST_CHECK_EQUAL(bool(dh), false);
		BOOST_CHECK_EQUAL(i, 0);
	}
	BOOST_CHECK_EQUAL(i, 0);
}

BOOST_AUTO_TEST_CASE(deferred_handler_trigger)
{
	using namespace eagine;
	int i = 0;

	BOOST_CHECK_EQUAL(i, 0);
	{
		deferred_handler<int*> dh = get_handler(&i);

		BOOST_CHECK_EQUAL(!dh, false);
		BOOST_CHECK_EQUAL(bool(dh), true);
		BOOST_CHECK_EQUAL(i, 0);

		dh.trigger();

		BOOST_CHECK_EQUAL(!dh, true);
		BOOST_CHECK_EQUAL(bool(dh), false);
		BOOST_CHECK_EQUAL(i, 1);
	}
	BOOST_CHECK_EQUAL(i, 1);
}

BOOST_AUTO_TEST_SUITE_END()