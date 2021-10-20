#pragma once

#include <stdint.h>

#include "KeyboardButton.h"

namespace pawn::system {

	class KeyboardManager {

		public:

			static void Update();
			static void Reset();

			static bool ButtonPressed(Button button);
			static bool ButtonReleased(Button button);

			static bool IsValidKeyboardButton(Button button);
			static bool IsKeyboardConnected();
			static bool IsAnyButtonPressed();
			static bool IsAnyButtonReleased();

			static int64_t GetButtonTimeStamp(Button button);
			
		private:

			KeyboardManager() = default;

			static bool GetButtonState(Button button);
			static bool GetLastFrameButtonState(Button button);

			static void UpdateInternal();

		private:

			static uint8_t m_Buttons[static_cast<uint32_t>(Button::Count)];
			static uint8_t m_LastFrameButtons[static_cast<uint32_t>(Button::Count)];
			static int64_t m_ButtonPressTimestamp[static_cast<uint32_t>(Button::Count)];
			static int64_t m_TimeStamp;

			static bool m_IsAnyButonPressed;
			static bool m_IsAnyButtonReleased;
	};

}
