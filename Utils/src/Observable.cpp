#include "pch.h"
#include "Observable.h"
#include "Observer.h"

namespace pawn {
	
	void Observable::AddObserver(const std::shared_ptr<pawn::Observer>& observer) {
		m_Observers.push_front(observer);
	}

	void Observable::RemoveObserver(const std::shared_ptr<pawn::Observer>& observer) {
		m_Observers.remove(observer);
	}

	void Observable::NotifyObservers() {
		for (auto& observer : m_Observers) {
			observer->HandleEvent();
		}
	}
	
}
