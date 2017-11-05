
#pragma once

namespace testing
{
	class Test;
	struct TestResult;

	namespace impl
	{
		void register_test(const Test &);
	}
}

