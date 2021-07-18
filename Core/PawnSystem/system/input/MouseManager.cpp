#include "MouseManager.h"

#include "PawnUtils/utils/time/Clock.h"

#include <cstring>
#include <cassert>

namespace pawn {

	namespace system {

		uint8_t MouseManager::m_Buttons[static_cast<uint32_t>(MouseButton::Count)]{ 0 };
		uint8_t MouseManager::m_LastFrameButtons[static_cast<uint32_t>(MouseButton::Count)]{ 0 };
		int64_t MouseManager::m_ButtonPressTimestamp[static_cast<uint32_t>(MouseButton::Count)]{ 0 };
		int64_t MouseManager::m_TimeStamp{ 0 };

		int32_t MouseManager::m_MouseRawX{ 0 };
		int32_t MouseManager::m_MouseRawY{ 0 };
		int32_t MouseManager::m_MouseWheel{ 0 };

		bool MouseManager::m_IsAnyButonPressed{ false };
		bool MouseManager::m_IsAnyButtonReleased{ false };

		void MouseManager::Update() {
			m_TimeStamp = utils::Clock::TimeStamp();

			memcpy(m_LastFrameButtons, m_Buttons, sizeof(m_LastFrameButtons));

			m_MouseRawX = 0;
			m_MouseRawY = 0;
			m_MouseWheel = 0;

			m_IsAnyButonPressed = false;
			m_IsAnyButtonReleased = false;

			UpdateInternal();

			for (uint32_t i{ 0 }; i < static_cast<uint32_t>(MouseButton::Count); ++i) {
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

		void MouseManager::Reset(bool onlyButtons) {
			memset(m_Buttons, 0, sizeof(m_Buttons));
			memset(m_LastFrameButtons, 0, sizeof(m_LastFrameButtons));
			memset(m_ButtonPressTimestamp, 0, sizeof(m_ButtonPressTimestamp));

			m_IsAnyButonPressed = false;
			m_IsAnyButtonReleased = false;

			if (!onlyButtons) {
				m_MouseRawX = 0;
				m_MouseRawY = 0;
			}
		}

		int32_t MouseManager::GetRawMouseX() {
			return m_MouseRawX;
		}

		int32_t MouseManager::GetRawMouseY() {
			return m_MouseRawY;
		}

		int32_t MouseManager::GetMouseWheel() {
			return m_MouseWheel;
		}

		bool MouseManager::ButtonPressed(MouseButton button) {
			assert(IsValidMouseButton(button));
			return GetButtonState(button);
		}

		bool MouseManager::ButtonReleased(MouseButton button) {
			assert(IsValidMouseButton(button));
			return !GetButtonState(button) && GetLastFrameButtonState(button);
		}

		bool MouseManager::IsValidMouseButton(MouseButton button) {
			return button < MouseButton::Count && button != MouseButton::None;
		}

		bool MouseManager::IsAnyButtonPressed() {
			return m_IsAnyButonPressed;
		}

		bool MouseManager::IsAnyButtonReleased() {
			return m_IsAnyButtonReleased;
		}

		bool MouseManager::GetButtonState(MouseButton button) {
			assert(IsValidMouseButton(button));
			return m_Buttons[static_cast<uint32_t>(button)] != 0;
		}

		bool MouseManager::GetLastFrameButtonState(MouseButton button) {
			assert(IsValidMouseButton(button));
			return m_LastFrameButtons[static_cast<uint32_t>(button)] != 0;
		}

		int64_t MouseManager::GetButtonTimeStamp(MouseButton button) {
			assert(IsValidMouseButton(button));
			return m_ButtonPressTimestamp[static_cast<uint32_t>(button)];
		}

	}

}
