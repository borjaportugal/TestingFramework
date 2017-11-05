
#pragma once

#include <string>	// std::string

namespace testing
{
	struct TestResult
	{
		operator bool() const { return m_succeded; }

		bool m_succeded{ true };
		unsigned m_line{ 0 };
		std::string m_fail_reason;
	};

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
}

