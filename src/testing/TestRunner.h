
#pragma once

#include "Singleton.h"

#include <ostream>	// std::ostream
#include <vector>	// std::vector

namespace testing
{
	class Test;
	struct TestResult;

	struct TestStats
	{
		void dump(std::ostream & os) const;

		unsigned m_succeded_tests{ 0 };
		unsigned m_failed_tests{ 0 };
		unsigned m_run_tests{ 0 };
	};

	class TestRunner : public impl::Singleton<TestRunner>
	{
	public:
		bool run_all_tests();

		TestStats get_stats() const { return m_stats; }

		void register_test(const Test & test);

	private:
		void track_succeded_test(const TestResult & test_result);
		void track_failed_test(const TestResult & test_result);
		void report_failure(const TestResult & test_result) const;

		TestStats m_stats;

		std::vector<const Test *> m_tests;
	};

}

inline std::ostream & operator<<(std::ostream & os, const ::testing::TestStats & stats)
{
	stats.dump(os);
	return os;
}


