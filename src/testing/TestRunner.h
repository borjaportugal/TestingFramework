
#pragma once

#include "Singleton.h"
#include "Forwards.h"

#include <ostream>	// std::ostream
#include <vector>	// std::vector

namespace testing
{
	///	\brief Stores statistics of the last run tests.
	struct TestStats
	{
		void dump(std::ostream & os) const;

		unsigned m_succeded_tests{ 0 };
		unsigned m_failed_tests{ 0 };
		unsigned m_run_tests{ 0 };
	};

	/// \brief	Main class in charge of running all tests and getting statistics.
	class TestRunner : public impl::Singleton<TestRunner>
	{
	public:
		bool run_all_tests();

		/// \brief	Returns the statistics of the last call to run tests.
		TestStats get_stats() const { return m_stats; }

	private:
		// test registration
		void register_test(const Test & test);
		friend void ::testing::impl::register_test(const Test &);

	private:
		void track_succeded_test(const Test & test, const TestResult & test_result);
		void track_failed_test(const Test & test, const TestResult & test_result);
		void report_failure(const Test & test, const TestResult & test_result) const;

		/// \brief	Stats about the last execution of tests.
		TestStats m_stats;

		/// \brief	Stores all the tests that have been compiled in the program.
		std::vector<Test> m_tests;
	};

}

inline std::ostream & operator<<(std::ostream & os, const ::testing::TestStats & stats)
{
	stats.dump(os);
	return os;
}


