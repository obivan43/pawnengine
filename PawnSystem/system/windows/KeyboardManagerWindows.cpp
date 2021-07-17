#include "input/KeyboardManager.h"

#include "PawnUtils/utils/time/Clock.h"

#ifdef _WIN32

#include "InputManagerWindows.h"

namespace pawn {

	namespace system {

		static Button ConvertCodeToButton(uint16_t makeCode, uint16_t virtualKey, bool prefixE0, bool prefixE1) {
			if (!prefixE0 && !prefixE1) {
				return static_cast<Button>(makeCode);
			}
			else if (prefixE0) {
				switch (static_cast<Button>(makeCode)) {
					case Button::Slash:
						return Button::NumpadDivide;
					case Button::Numpad0:
						return Button::Insert;
					case Button::NumpadDot:
						return Button::Delete;
					case Button::Numpad1:
						return Button::End;
					case Button::Numpad2:
						return Button::DownArrow;
					case Button::Numpad3:
						return Button::PageDown;
					case Button::Numpad4:
						return Button::LeftArrow;
					case Button::Numpad6:
						return Button::RightArrow;
					case Button::Numpad7:
						return Button::Home;
					case Button::Numpad8:
						return Button::UpArrow;
					case Button::Numpad9:
						return Button::PageUp;
					case Button::LeftControl:
						return Button::RightControl;
					case Button::LeftAlt:
						return Button::RightAlt;
					case Button::Return:
						return Button::NumpadEnter;
				}
			}

			return Button::None;
		}

		void KeyboardManager::UpdateInternal() {
			uint64_t timestamp = utils::Clock::TimeStamp();

			InputManagerWindows::InputData input;
			while (InputManagerWindows::ProccessKeyboard(timestamp, input)) {
				const RAWKEYBOARD& rawKeyboard = input.input.data.keyboard;

				uint16_t makeCode = rawKeyboard.MakeCode;
				uint16_t virtualKey = rawKeyboard.VKey;
				bool prefixE0 = (rawKeyboard.Flags & RI_KEY_E0) == RI_KEY_E0;
				bool prefixE1 = (rawKeyboard.Flags & RI_KEY_E1) == RI_KEY_E1;

				Button button = ConvertCodeToButton(makeCode, virtualKey, prefixE0, prefixE1);
				if (!IsValidKeyboardButton(button)) {
					continue;
				}

				m_Buttons[static_cast<uint32_t>(button)] = (rawKeyboard.Flags & RI_KEY_BREAK) != RI_KEY_BREAK;
			}
		}

		bool KeyboardManager::IsKeyboardConnected() {
			return InputManagerWindows::IsKeyboardConnected();
		}

	}

}
#endif
