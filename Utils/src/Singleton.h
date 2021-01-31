#pragma once

#include <memory>

namespace pawn {
	
	template<typename Type> class Singleton {

	public:
		virtual ~Singleton() = default;

		template<typename... Args>
		static Type& Instance(Args&&... args);

	protected:
		Singleton() = default;

	private:
		Singleton(const Singleton&) = delete;
		const Singleton& operator=(const Singleton&) = delete;
	};

	template <typename Type>
	template <typename ... Args>
	Type& Singleton<Type>::Instance(Args&&... args) {
		static const std::unique_ptr<Type> instance(new Type(std::forward<Args>(args)...));
		return *instance;
	}
	
}
