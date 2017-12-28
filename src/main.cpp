/*!
\author Borja Portugal Martin
GitHub: https://github.com/borjaportugal

This file is subject to the license terms in the LICENSE file
found in the top-level directory of this distribution.
*/

#include <iostream>

#include "testing\testing.h"


TEST_F(test_that_passes)
{
	TEST_ASSERT(1 != 2);
}

TEST_F(test_that_fails)
{
	TEST_ASSERT(1 == 2);
}

TEST_F(test_that_passes_2)
{
	TEST_ASSERT(1 != 2);
}

struct ExampleCategory : public ::testing::TestCategory
{
	int i = 0;
};

TEST(ExampleCategory, test_that_passes)
{
	TEST_ASSERT(i++ == 0);
}

TEST(ExampleCategory, test_that_passes_2)
{
	TEST_ASSERT(i == 0);
}

TEST(ExampleCategory, test_that_fails)
{
	TEST_ASSERT(++i == 0);
}


struct TestOnExitExample : public ::testing::TestCategory
{
	static int i;
};
int TestOnExitExample::i = 0;

TEST(TestOnExitExample, test_1)
{
	TEST_ASSERT(i++ == 0);
}
TEST(TestOnExitExample, test_2)
{
	TEST_ON_EXIT()
	{
		// this will be executed when the test finishes,
		// either succeeds or fails
		i = 0;
	};

	// this is true
	TEST_ASSERT(i == 1);
}

TEST(TestOnExitExample, test_3)
{
	TEST_ON_EXIT()
	{
		// this will be executed when the test finishes,
		// either succeeds or fails
		i = 33;
	};

	// this is false
	TEST_ASSERT(i != 0);
}

TEST(TestOnExitExample, test_4)
{
	// this is true
	TEST_ASSERT(i == 33);
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

