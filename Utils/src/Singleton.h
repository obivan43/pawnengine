#pragma once

#include <mutex>
#include <functional>

using std::call_once;
using std::once_flag;

namespace pawn {
	
	template<typename Type> class Singleton {

		public:
			Singleton(const Singleton&) = delete;
			const Singleton& operator=(const Singleton&) = delete;
			virtual ~Singleton() = default;

			template<typename... Args>
			static Type& Instance(Args&&... args);

		protected:
			Singleton() = default;

		private:
			static once_flag& GetOnceFlag() {
				static once_flag once;
				return once;
			}
	
		private:
			static std::unique_ptr<Type> m_Instance;
	};

	template<class Type> std::unique_ptr<Type> Singleton<Type>::m_Instance = nullptr;

	template <typename Type>
	template <typename ... Args>
	Type& Singleton<Type>::Instance(Args&&... args) {
        call_once(
			GetOnceFlag(),
            [](Args&&... args) {
				m_Instance.reset(new Type(std::forward<Args>(args)...));
            }, std::forward<Args>(args)...
		);

        return *m_Instance.get();
	}
	
}
