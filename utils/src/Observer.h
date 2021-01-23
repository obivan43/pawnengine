#pragma once
#include <iostream>

namespace pawn {
	
	class Observer {
		public:
			Observer()
			{
				std::cout << "created" << std::endl;
			}
			Observer(const Observer& other) = default;
			Observer(Observer && other) noexcept = default;
			Observer& operator=(const Observer & other) = default;
			Observer& operator=(Observer && other) noexcept = default;

			virtual ~Observer() = default;
		
			virtual void handleEvent() {};

	};
	
}
