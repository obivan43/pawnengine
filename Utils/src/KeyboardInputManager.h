#pragma once

#include <optional>
#include <queue>
#include <bitset>

#include "Event.h"

namespace pawn {
	
	class KeyboardInputManager {
		
		public:
			KeyboardInputManager();
			KeyboardInputManager(const KeyboardInputManager& other) = default;
			KeyboardInputManager(KeyboardInputManager&& other) noexcept = default;
		
			KeyboardInputManager& operator=(const KeyboardInputManager& other) = default;
			KeyboardInputManager& operator=(KeyboardInputManager&& other) noexcept = default;

			bool IsPressed(uint8_t code);
			void FlushStates();

			std::optional<std::shared_ptr<Event>> ReadKeyFromBuffer();
			bool IsKeyBufferEmpty() const;
			void FlushKeyBuffer();

			std::optional<char> ReadFromCharBuffer();
			bool IsCharBufferEmpty() const;
			void FlushCharBuffer();

			void Flush();
		
			void EnableAutoRepeat();
			void DisableAutoRepeat();
			bool IsAutoRepeatEnabled() const;

			void OnKeyPressed(uint8_t code);
			void OnKeyRelease(uint8_t code);
			void OnChar(int8_t value);

		private:
			void TrimKeyBuffer();
			void TrimCharBuffer();
	
		private:
			std::bitset<256> m_KeyStates;
			std::queue<std::shared_ptr<Event>> m_KeysQueue;
			std::queue<int8_t> m_CharsQueue;
			bool m_AutoRepeat;

			uint32_t m_TrimBufferSize;
	};
	
}
