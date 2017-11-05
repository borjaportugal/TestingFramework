
#pragma once

#include "Test.h"
#include "TestFailedException.h"

#include <string>
#include <vector>

namespace testing
{
	namespace impl
	{
		void register_test(const Test & test);
	}

	bool run_all_tests();
}


#define _TESTING_REGISTER_TEST(test)	\
static const bool test_registered ## test = []() { \
		::testing::impl::register_test(test); \
		return true;	\
	}()

#define TEST_ASSERT(cond)	if (!(cond))	throw std::exception{ #cond, __LINE__ }
#define TEST_FAILED()		TEST_ASSERT(false)
#define TEST_SUCCEDED()		

#define TEST(func)	\
void func();		\
static const ::testing::Test test_ ## func{ func, #func };	\
_TESTING_REGISTER_TEST(test_ ## func); \
void func()



