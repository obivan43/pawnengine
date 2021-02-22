#pragma once

#include <list>

#include "IObservable.h"

namespace pawn {
	
	class Observable : public IObservable {
		
		public:
			Observable() = default;
			Observable(const Observable& other) = default;
			Observable(Observable&& other) noexcept = default;
		
			Observable& operator=(const Observable& other) = default;
			Observable& operator=(Observable&& other) noexcept = default;
		
			void AddObserver(Observer* observer) override final;
			void RemoveObserver(Observer* observer) override final;
			void NotifyObservers(Event& e) override final;
	
		private:
			std::list<Observer*> m_Observers;
	};
	
}
