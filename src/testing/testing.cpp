
#include "testing.h"

#include "TestRunner.h"

namespace testing
{
	namespace impl
	{
		void register_test(const Test & test)
		{
			TestRunner::get_instance().register_test(test);
		}
	}

	bool run_all_tests(const TestingConfig & config)
	{
		return TestRunner::get_instance().run_all_tests(config);
	}
}

