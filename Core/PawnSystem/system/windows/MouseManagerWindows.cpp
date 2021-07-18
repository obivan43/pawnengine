#include "input/MouseManager.h"

#include "PawnUtils/utils/time/Clock.h"

#ifdef _WIN32

#include "InputManagerWindows.h"

namespace pawn {

	namespace system {

		void MouseManager::UpdateButtonState(RAWMOUSE& rawMouse, MouseButton button, USHORT down, USHORT up) {
			if (rawMouse.usButtonFlags & down) {
				m_Buttons[static_cast<uint32_t>(button)] = true;
			}
			else if (rawMouse.usButtonFlags & up) {
				m_Buttons[static_cast<uint32_t>(button)] = false;
			}
		}

		void MouseManager::UpdateInternal() {
			int64_t timestamp{ utils::Clock::TimeStamp() };

			InputManagerWindows::InputData input;
			while (InputManagerWindows::ProccessMouse(timestamp, input)) {
				RAWMOUSE& rawMouse = input.input.data.mouse;

				UpdateButtonState(rawMouse, MouseButton::LeftButton, RI_MOUSE_BUTTON_1_DOWN, RI_MOUSE_BUTTON_1_UP);
				UpdateButtonState(rawMouse, MouseButton::RightButton, RI_MOUSE_BUTTON_2_DOWN, RI_MOUSE_BUTTON_2_UP);
				UpdateButtonState(rawMouse, MouseButton::CenterButton, RI_MOUSE_BUTTON_3_DOWN, RI_MOUSE_BUTTON_3_UP);
				UpdateButtonState(rawMouse, MouseButton::Button4, RI_MOUSE_BUTTON_4_DOWN, RI_MOUSE_BUTTON_4_UP);
				UpdateButtonState(rawMouse, MouseButton::Button5, RI_MOUSE_BUTTON_5_DOWN, RI_MOUSE_BUTTON_5_UP);

				if (rawMouse.usFlags == MOUSE_MOVE_RELATIVE && (rawMouse.lLastX != 0 || rawMouse.lLastY != 0)) {
					m_MouseRawX = rawMouse.lLastX;
					m_MouseRawY = rawMouse.lLastY;
				}

				if (rawMouse.usButtonFlags & RI_MOUSE_WHEEL) {
					m_MouseWheel += static_cast<int16_t>(rawMouse.usButtonData);
				}
			}
		}

		bool MouseManager::IsMouseConnected() {
			return InputManagerWindows::IsMouseConnected();
		}

	}

}

#endif
