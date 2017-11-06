
#pragma once

#include <exception>
#include <string>
#include <vector>
#include <ostream>

namespace testing
{
	struct TestingConfig
	{
		std::ostream * m_ostream{ nullptr };
		bool m_verbose{ true };
		bool m_abort_on_failure{ false };
	};

	struct TestResult
	{
		operator bool() const { return m_succeded; }

		bool m_succeded{ true };
		unsigned m_line{ 0 };
		std::string m_fail_reason;
	};

	/// \brief	Thrown when a test fails, contains information about failure.
	class TestFailedException : public std::exception
	{
	public:
		TestFailedException(const char * failed_condition, unsigned line)
			: m_failed_cond{ failed_condition }
			, m_line{ line }
		{}

		const char * what() const override { return get_failed_condition(); }

		const char * get_failed_condition() const { return m_failed_cond; }
		unsigned get_line() const { return m_line; }

	private:
		const char * m_failed_cond{ nullptr };
		unsigned m_line{ 0 };

	};

	/// \brief	Stores and runs a unit test.
	class Test
	{
		using test_fn = void(*)();

	public:
		explicit Test(test_fn test, const char * name)
			: m_test_fn{ test }
			, m_test_name{ name }
		{}

		TestResult run() const;

		const char * get_name() const { return m_test_name; }

	private:
		void run_test() const;

		test_fn m_test_fn{ nullptr };
		const char * m_test_name{ "" };
	};

	///	\brief Stores statistics of the last run tests.
	struct TestingStats
	{
		void dump(std::ostream & os) const;

		unsigned m_succeded_tests{ 0 };
		unsigned m_failed_tests{ 0 };
		unsigned m_run_tests{ 0 };
	};

	namespace impl
	{
		/// \brief	Helper for not including TestRunner here.
		void register_test(const Test & test);
	}

	/// \brief	Main class in charge of running all tests and getting statistics.
	class TestRunner
	{
	public:
		static TestRunner & get_instance();

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

namespace testing
{
	/// \brief	Runs all the tests that have been compiled.
	bool run_all_tests(const TestingConfig & config = TestingConfig{});
}

/// \brief	Declares a variable name that won't be duplicated.
///			The user needs to specify some value to have some context in case the compiler complains.
#define TESTING_UNNAMED_VARIABLE(x)	TESTING_UNNAMED_VARIABLE_INNER(x)
#define TESTING_UNNAMED_VARIABLE_INNER(x)	x ## _unnamed_var_ ## __LINE__ ## _ ## __COUNTER__

/// \brief	Register the test before main is called.
#define _TESTING_REGISTER_TEST(func)											\
namespace { namespace testing_impl {											\
	static const bool TESTING_UNNAMED_VARIABLE(test_register ## func) = []()	\
	{																			\
		::testing::impl::register_test(::testing::Test{ func, #func });			\
		return true;															\
	}();																		\
} }


///	\brief	If the condition is not satisfied the test fails.
#define TEST_ASSERT(cond) do { if (!(cond))	throw std::exception{ "Condition ( " #cond " ) not satisfied." , __LINE__ }; } while (0)

///	\brief	Test fails inmediately.
#define TEST_FAILED() TEST_ASSERT(false)

///	\brief	Placeholder macro to mark paths that the execution should follow in order to make the test pass,
///	lets the test continue executing.
#define TEST_SUCCEDED()		

/// \brief	Declares a test 
#define TEST(func) void func(); _TESTING_REGISTER_TEST(func);	void func()



