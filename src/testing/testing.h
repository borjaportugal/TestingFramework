
#pragma once

#include "Test.h"
#include "TestFailedException.h"
#include "TestingConfig.h"

#include <string>
#include <vector>

namespace testing
{
	namespace impl
	{
		/// \brief	Helper for not including TestRunner here.
		void register_test(const Test & test);
	}

	/// \brief	Runs all the tests that have been compiled.
	bool run_all_tests(const TestingConfig & config = TestingConfig{});
}

/// \brief	Declares a variable name that won't be duplicated.
///			The user needs to specify some value to have some context in case the compiler complains.
#define TESTING_UNNAMED_VARIABLE(x)	TESTING_UNNAMED_VARIABLE_INNER(x)
#define TESTING_UNNAMED_VARIABLE_INNER(x)	x ## _unnamed_var_ ## __LINE__ ## _ ## __COUNTER__

/// \brief	Register the test before main is called.
#define _TESTING_REGISTER_TEST(func)	\
namespace { namespace testing_impl { \
static const bool TESTING_UNNAMED_VARIABLE(test_register ## func) = []() { \
		::testing::impl::register_test(::testing::Test{ func, #func }); \
		return true;	\
	}(); } }

#define TEST_ASSERT(cond)	\
	if (!(cond))	\
		throw std::exception{ "Condition ( " #cond " ) not satisfied." , __LINE__ }
#define TEST_FAILED()		TEST_ASSERT(false)
#define TEST_SUCCEDED()		

#define TEST(func)	\
void func();		\
_TESTING_REGISTER_TEST(func); \
void func()



