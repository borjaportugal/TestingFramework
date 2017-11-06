/*!
\author Borja Portugal Martin
*/

#include <iostream>

#include "testing\testing.h"

TEST(a_test)
{
	TEST_ASSERT(1 != 2);
}

TEST(an_other_test)
{
	TEST_ASSERT(1 == 2);
}

TEST(third_test)
{
	TEST_ASSERT(1 != 2);
}

int main()
{
	testing::TestingConfig config;
	config.m_abort_on_failure = false;
	config.m_verbose = true;

	if (testing::run_all_tests(config) == false)
	{
		std::cin.get();
	}

	return 0;
}

