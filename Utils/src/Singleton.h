#pragma once

#include <memory>

template<typename Type> class Singleton {
	public:
		Singleton(const Singleton& other) = delete;
		Singleton(Singleton&& other) = delete;
	
		Singleton& operator=(const Singleton& other) = delete;
		Singleton& operator=(Singleton&& other) = delete;
		Singleton& operator=(const Singleton) = delete;
	
	    virtual ~Singleton() = default;

		static Type& instance();

	protected:
		Singleton() = default;
};

template<typename Type> Type& Singleton<Type>::instance() {
    static const std::unique_ptr<Type> instance{ new Type() };
    return *instance;
}
