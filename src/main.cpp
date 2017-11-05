/*!
\author Borja Portugal Martin
*/

#include <iostream>

#include "testing\testing.h"
#include "testing\TestRunner.h"

TEST(a_test)
{
	TEST_ASSERT(1 != 2);
}

TEST(an_other_test)
{
	TEST_ASSERT(1 == 2);
}

int main()
{
	if (testing::run_all_tests() == false)
	{
		std::cout << testing::TestRunner::get_instance().get_stats() << std::endl;
		std::cin.get();
	}

	return 0;
}

