
#pragma once

#include "Singleton.h"
#include "Forwards.h"
#include "TestingConfig.h"

#include <ostream>	// std::ostream
#include <vector>	// std::vector

namespace testing
{
	///	\brief Stores statistics of the last run tests.
	struct TestingStats
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
		bool run_all_tests(const TestingConfig & config);

		/// \brief	Returns the statistics of the last call to run tests.
		TestingStats get_stats() const { return m_stats; }
		
	private:
		// test registration
		void register_test(const Test & test);
		friend void ::testing::impl::register_test(const Test &);

	private:
		void set_config(const TestingConfig & config);
		void track_test_result(const Test & test, const TestResult & test_result);
		void track_succeded_test(const Test & test, const TestResult & test_result);
		void track_failed_test(const Test & test, const TestResult & test_result);
		void report_failure(const Test & test, const TestResult & test_result) const;

		// configuration related
		bool abort_on_failure() const { return m_config.m_abort_on_failure; }
		bool verbose() const { return m_config.m_verbose; }
		std::ostream & get_ostream() const;

		TestingConfig m_config;

		/// \brief	Stats about the last execution of tests.
		TestingStats m_stats;

		/// \brief	Stores all the tests that have been compiled in the program.
		std::vector<Test> m_tests;
	};

}

inline std::ostream & operator<<(std::ostream & os, const ::testing::TestingStats & stats)
{
	stats.dump(os);
	return os;
}


