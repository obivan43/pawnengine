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
		
			virtual void AddObserver(const std::shared_ptr<pawn::Observer>& observer) override final;
			virtual void RemoveObserver(const std::shared_ptr<pawn::Observer>& observer) override final;
			virtual void NotifyObservers() override final;
	
		private:
			std::list<std::shared_ptr<Observer>> m_Observers;
	};
	
}
