#include "pch.h"
#include "MouseInputManager.h"

#include "MouseEvents.h"

namespace pawn {
	
	MouseInputManager::MouseInputManager() : m_X(0), m_Y(0), m_TrimBufferSize(32) {}

	std::optional<std::shared_ptr<Event>> MouseInputManager::ReadFromBuffer() {
		if (!m_Queue.empty()) {
			std::shared_ptr<Event> event = m_Queue.front();
			m_Queue.pop();
			return event;
		}

		return {};
	}

	bool MouseInputManager::IsBufferEmpty() const {
		return m_Queue.empty();
	}

	void MouseInputManager::Flush() {
		m_Queue = std::queue<std::shared_ptr<Event>>();
	}

	void MouseInputManager::TrimBuffer() {
		while (m_Queue.size() > m_TrimBufferSize) {
			m_Queue.pop();
		}
	}

	void MouseInputManager::OnMouseMove(int32_t x, int32_t y) {
		m_X = x;
		m_Y = y;
		m_Queue.push(std::make_shared<MouseMove>(MouseMove(x, y)));
	}
	
}
