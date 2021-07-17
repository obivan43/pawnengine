#include "KeyboardManager.h"

#include "PawnUtils/utils/time/Clock.h"

#include <cstring>
#include <cassert>

namespace pawn {

	namespace system {

		uint8_t KeyboardManager::m_Buttons[static_cast<uint32_t>(Button::Count)]{ 0 };
		uint8_t KeyboardManager::m_LastFrameButtons[static_cast<uint32_t>(Button::Count)]{ 0 };
		int64_t KeyboardManager::m_ButtonPressTimestamp[static_cast<uint32_t>(Button::Count)]{ 0 };
		int64_t KeyboardManager::m_TimeStamp{ 0 };

		bool KeyboardManager::m_IsAnyButonPressed{ false };
		bool KeyboardManager::m_IsAnyButtonReleased{ false };

		void KeyboardManager::Update() {
			m_TimeStamp = utils::Clock::TimeStamp();

			memcpy(m_LastFrameButtons, m_Buttons, sizeof(m_LastFrameButtons));

			m_IsAnyButonPressed = false;
			m_IsAnyButtonReleased = false;

			UpdateInternal();

			for (uint32_t i{ 0 }; i < static_cast<uint32_t>(Button::Count); ++i) {
				if (m_Buttons[i]) {
					m_IsAnyButonPressed = true;
					if (!m_LastFrameButtons[i]) {
						m_ButtonPressTimestamp[i] = m_TimeStamp;
					}
				}
				else if (m_LastFrameButtons[i]) {
					m_IsAnyButtonReleased = true;
				}
			}
		}

		void KeyboardManager::Reset() {
			memset(m_Buttons, 0, sizeof(m_Buttons));
			memset(m_LastFrameButtons, 0, sizeof(m_LastFrameButtons));
			memset(m_ButtonPressTimestamp, 0, sizeof(m_ButtonPressTimestamp));

			m_IsAnyButonPressed = false;
			m_IsAnyButtonReleased = false;
		}

		bool KeyboardManager::ButtonPressed(Button button) {
			assert(IsValidKeyboardButton(button));
			return GetButtonState(button);
		}

		bool KeyboardManager::ButtonReleased(Button button) {
			assert(IsValidKeyboardButton(button));
			return !GetButtonState(button) && GetLastFrameButtonState(button);
		}

		bool KeyboardManager::IsValidKeyboardButton(Button button) {
			return button < Button::Count && button != Button::None;
		}

		bool KeyboardManager::IsAnyButtonPressed() {
			return m_IsAnyButonPressed;
		}

		bool KeyboardManager::IsAnyButtonReleased() {
			return m_IsAnyButtonReleased;
		}

		bool KeyboardManager::GetButtonState(Button button) {
			assert(IsValidKeyboardButton(button));
			return m_Buttons[static_cast<uint8_t>(button)] != 0;
		}

		bool KeyboardManager::GetLastFrameButtonState(Button button) {
			assert(IsValidKeyboardButton(button));
			return m_LastFrameButtons[static_cast<uint8_t>(button)] != 0;
		}

		int64_t KeyboardManager::GetButtonTimeStamp(Button button) {
			assert(IsValidKeyboardButton(button));
			return m_ButtonPressTimestamp[static_cast<uint8_t>(button)];
		}

	}

}