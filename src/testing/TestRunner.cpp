
#include "TestRunner.h"
#include "Test.h"

#include <iostream>

namespace testing
{
	void TestingStats::dump(std::ostream & os) const
	{
		os << "Tests run: " << m_run_tests << '\n'
			<< "  Succeded: " << m_succeded_tests << '\n'
			<< "  Failed: " << m_failed_tests;
	}

	bool TestRunner::run_all_tests(const TestingConfig & config)
	{
		set_config(config);		// config we will be using this run
		m_stats = TestingStats{};	// reset to track new stats

		auto & os = get_ostream();

		bool all_succeded = true;
		for (const auto & test : m_tests)
		{
			if (verbose())
				os << "Running: " << test.get_name() << std::endl;

			const auto test_result = test.run();
			all_succeded &= test_result.m_succeded;

			track_test_result(test, test_result);

			if (!test_result.m_succeded && abort_on_failure())
			{
				os << "Aborting test execution.\n";
				break;
			}
		}

		m_stats.m_run_tests = m_stats.m_succeded_tests + m_stats.m_failed_tests;

		os << '\n';
		os << "Final stats:\n";
		m_stats.dump(os);
		os << '\n';
		return all_succeded;
	}

	std::ostream & TestRunner::get_ostream() const
	{
		return *m_config.m_ostream;
	}
	void TestRunner::set_config(const TestingConfig & config)
	{
		m_config = config;

		// Default ostream is std::cout
		if (!m_config.m_ostream)
			m_config.m_ostream = &std::cout;
	}

	void TestRunner::track_test_result(const Test & test, const TestResult & test_result)
	{
		if (test_result.m_succeded)
			track_succeded_test(test, test_result);
		else
			track_failed_test(test, test_result);
	}
	void TestRunner::track_succeded_test(const Test & test,
		const TestResult & test_result)
	{
		m_stats.m_succeded_tests++;
	}
	void TestRunner::track_failed_test(const Test & test,
		const TestResult & test_result)
	{
		m_stats.m_failed_tests++;
		report_failure(test, test_result);
	}
	void TestRunner::report_failure(const Test & test,
		const TestResult & test_result) const
	{
		get_ostream() << "Test " << test.get_name() << " failed: "
			<< test_result.m_fail_reason
			<< '\n';
	}

	void TestRunner::register_test(const Test & test)
	{
		m_tests.emplace_back(test);
	}
}
