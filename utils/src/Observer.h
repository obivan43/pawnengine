#pragma once
#include <iostream>

namespace pawn {
	
	class Observer {
		public:
			Observer() = default;
			Observer(const Observer& other) = default;
			Observer(Observer && other) noexcept = default;
			Observer& operator=(const Observer & other) = default;
			Observer& operator=(Observer && other) noexcept = default;

			virtual ~Observer() = default;
		
			virtual void handleEvent();

	};
	
}
