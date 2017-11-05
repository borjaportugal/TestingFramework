
#include "TestRunner.h"
#include "Test.h"

#include <iostream>

namespace testing
{
	void TestStats::dump(std::ostream & os) const
	{
		os << "Tests run: " << m_run_tests << '\n'
			<< "  Succeded: " << m_succeded_tests << '\n'
			<< "  Failed: " << m_failed_tests;
	}

	bool TestRunner::run_all_tests()
	{
		m_stats = TestStats{};

		bool all_succeded = true;
		for (const auto * test : m_tests)
		{
			const auto test_result = test->run();
			all_succeded &= test_result.m_succeded;

			if (test_result.m_succeded)
				track_succeded_test(test_result);
			else
				track_failed_test(test_result);
		}

		m_stats.m_run_tests = m_stats.m_succeded_tests + m_stats.m_failed_tests;
		return all_succeded;
	}

	void TestRunner::track_succeded_test(const TestResult & test_result)
	{
		m_stats.m_succeded_tests++;
	}
	void TestRunner::track_failed_test(const TestResult & test_result)
	{
		m_stats.m_failed_tests++;
		report_failure(test_result);
	}
	void TestRunner::report_failure(const TestResult & test_result) const
	{
		std::cout << test_result.m_fail_reason << std::endl;
	}

	void TestRunner::register_test(const Test & test)
	{
		m_tests.emplace_back(&test);
	}
}
