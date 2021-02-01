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

			virtual ~Observable() = default;
		
			virtual void AddObserver(Observer* observer) override final;
			virtual void RemoveObserver(Observer* observer) override final;
			virtual void NotifyObservers(const Event& e) override final;
	
		private:
			std::list<Observer*> m_Observers;
	};
	
}
