#pragma once

#include <memory>

namespace pawn {

	class Observer;
	
	class IObservable {	
		public:
			IObservable() = default;
			IObservable(const IObservable& other) = default;
			IObservable(IObservable&& other) noexcept = default;

			IObservable& operator=(const IObservable& other) = default;
			IObservable& operator=(IObservable&& other) noexcept = default;

			virtual ~IObservable() = default;

			virtual void AddObserver(const std::shared_ptr<pawn::Observer>& observer) = 0;
			virtual void RemoveObserver(const std::shared_ptr<pawn::Observer>& observer) = 0;
			virtual void NotifyObservers() = 0;
	};
	
}
