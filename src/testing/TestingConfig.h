
#pragma once

#include <ostream>

namespace testing
{
	struct TestingConfig
	{
		std::ostream * m_ostream{ nullptr };
		bool m_verbose{ true };
		bool m_abort_on_failure{ false };
	};
}

