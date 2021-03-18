#pragma once

#include "IObservable.h"

#include <list>

namespace pawn {
	
	class Observable : public IObservable {
		
		public:
			Observable();
			Observable(const Observable& other) = default;
			Observable(Observable&& other) noexcept = default;
		
			Observable& operator=(const Observable& other) = default;
			Observable& operator=(Observable&& other) noexcept = default;

			~Observable();
		
			void AddObserver(Observer* observer) override final;
			void RemoveObserver(Observer* observer) override final;
			void NotifyObservers(Event& e) override final;
	
		private:
			std::list<Observer*>* m_Observers;
	};
	
}
