﻿#pragma once

#include <memory>

#include "Event.h"

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

			virtual void AddObserver(Observer* observer) = 0;
			virtual void RemoveObserver(Observer* observer) = 0;
			virtual void NotifyObservers(Event& e) = 0;
	};
	
}
