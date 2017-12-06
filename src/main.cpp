/*!
\author Borja Portugal Martin
GitHub: https://github.com/borjaportugal

This file is subject to the license terms in the LICENSE file
found in the top-level directory of this distribution.
*/

#include <iostream>

#include "testing\testing.h"


TEST_F(a_test)
{
	TEST_ASSERT(1 != 2);
}

TEST_F(an_other_test)
{
	TEST_ASSERT(1 == 2);
}

TEST_F(third_test)
{
	TEST_ASSERT(1 != 2);
}

struct ExampleCategory : public ::testing::TestCategory
{
	int i = 0;

	void tear_up() override
	{
		std::cout << "Pre test execution\n";
	}

	void tear_down() override
	{
		std::cout << "Post test execution\n";
	}
};

TEST(ExampleCategory, a_test)
{
	TEST_ASSERT(i++ == 0);
}

TEST(ExampleCategory, an_other_test)
{
	TEST_ASSERT(i == 0);
}

TEST(ExampleCategory, third_test)
{
	TEST_ASSERT(++i == 0);
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

