
#include "Test.h"
#include "TestFailedException.h"

namespace testing
{
	TestResult Test::run() const
	{
		TestResult result{ get_name() };

		try
		{
			run_test();
		}
		catch (const TestFailedException & ex)
		{
			result.m_succeded = false;
			result.m_fail_reason = ex.get_failed_condition();
			result.m_line = ex.get_line();
		}
		catch (const std::exception & ex)
		{
			result.m_succeded = false;
			result.m_fail_reason = ex.what();
		}
		catch (...)
		{
			result.m_succeded = false;
			result.m_fail_reason = "Unknown reason.";
		}

		return result;
	}


	void Test::run_test() const
	{
		m_test_fn();
	}
}
