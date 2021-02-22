#include "pch.h"
#include "Observable.h"
#include "Observer.h"

namespace pawn {
	
	void Observable::AddObserver(Observer* observer) {
		m_Observers.push_front(observer);
	}

	void Observable::RemoveObserver(Observer* observer) {
		m_Observers.remove(observer);
	}

	void Observable::NotifyObservers(Event& e) {
		for (auto& observer : m_Observers) {
			observer->HandleEvent(e);
		}
	}
	
}
