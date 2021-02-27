#include "pch.h"
#include "KeyboardInputManager.h"

#include "KeyboardEvents.h"

namespace pawn {

	KeyboardInputManager::KeyboardInputManager() : m_AutoRepeat(true), m_TrimBufferSize(32) {}
	
	bool KeyboardInputManager::IsPressed(uint8_t code) { return m_KeyStates[code]; }
	void KeyboardInputManager::FlushStates() { m_KeyStates.reset(); }

	std::optional<std::shared_ptr<Event>> KeyboardInputManager::ReadKeyFromBuffer() {
		if(!m_KeysQueue.empty()) {
			std::shared_ptr<Event> event = m_KeysQueue.front();
			m_KeysQueue.pop();
			return event;
		}

		return {};
	}
	
	bool KeyboardInputManager::IsKeyBufferEmpty() const { return m_KeysQueue.empty(); }
	void KeyboardInputManager::FlushKeyBuffer() { m_KeysQueue = std::queue<std::shared_ptr<Event>>(); }

	std::optional<char> KeyboardInputManager::ReadFromCharBuffer() {
		if (!m_CharsQueue.empty()) {
			char value = m_CharsQueue.front();
			m_CharsQueue.pop();
			return value;
		}

		return {};
	}
	
	bool KeyboardInputManager::IsCharBufferEmpty() const { return m_CharsQueue.empty(); }
	void KeyboardInputManager::FlushCharBuffer() { m_CharsQueue = std::queue<int8_t>(); }

	void KeyboardInputManager::Flush() {
		FlushKeyBuffer();
		FlushCharBuffer();
	}
	
	void KeyboardInputManager::EnableAutoRepeat() { m_AutoRepeat = true; }
	void KeyboardInputManager::DisableAutoRepeat() { m_AutoRepeat = false; }
	bool KeyboardInputManager::IsAutoRepeatEnabled() const { return m_AutoRepeat; }

	void KeyboardInputManager::OnKeyPressed(uint8_t code) {
		m_KeyStates[code] = true;
		m_KeysQueue.push(std::make_shared<KeyboardPress>(KeyboardPress(code)));
	}
	
	void KeyboardInputManager::OnKeyRelease(uint8_t code) {
		m_KeyStates[code] = false;
		m_KeysQueue.push(std::make_shared<KeyboardRelease>(KeyboardRelease(code)));
	}
	
	void KeyboardInputManager::OnChar(int8_t value) {
		m_CharsQueue.push(value);
	}

	void KeyboardInputManager::TrimKeyBuffer() {
		while (m_KeysQueue.size() > m_TrimBufferSize) {
			m_KeysQueue.pop();
		}
	}
	
	void KeyboardInputManager::TrimCharBuffer() {
		while (m_CharsQueue.size() > m_TrimBufferSize) {
			m_CharsQueue.pop();
		}
	}

}