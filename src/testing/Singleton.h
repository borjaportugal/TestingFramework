
#pragma once

namespace testing
{
	namespace impl
	{
		template <class T>
		class Singleton
		{
		public:
			static T & get_instance()
			{
				if (!s_inst)	s_inst = new T{};
				return *s_inst;
			}

		protected:
			Singleton() = default;
			~Singleton() = default;

		private:
			static T * s_inst;

			// in case T has private ctor/dtor
			friend T;
		};
		template <typename T>
		T * Singleton<T>::s_inst = nullptr;

	}
}

