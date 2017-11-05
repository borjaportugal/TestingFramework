
#pragma once

#include <exception>	// std::exception

namespace testing
{
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
}

