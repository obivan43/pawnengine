#pragma once

#include "MouseButton.h"

#ifdef _WIN32
#include "PawnSystem/system/windows/WindowsAPI.h"
#endif

namespace pawn::system {

	class MouseManager {

		public:

			static void Update();
			static void Reset(bool onlyButtons);

			static bool ButtonPressed(MouseButton button);
			static bool ButtonReleased(MouseButton button);

			static bool IsValidMouseButton(MouseButton button);
			static bool IsMouseConnected();
			static bool IsAnyButtonPressed();
			static bool IsAnyButtonReleased();

			static int32_t GetRawMouseX();
			static int32_t GetRawMouseY();
			static int32_t GetMouseWheel();

			static int64_t GetButtonTimeStamp(MouseButton button);

		private:

			MouseManager() = default;

			static bool GetButtonState(MouseButton button);
			static bool GetLastFrameButtonState(MouseButton button);

			static void UpdateInternal();
#ifdef _WIN32
			static void UpdateButtonState(RAWMOUSE& rawMouse, MouseButton button, USHORT down, USHORT up);
#endif

		private:

			static uint8_t m_Buttons[static_cast<uint32_t>(MouseButton::Count)];
			static uint8_t m_LastFrameButtons[static_cast<uint32_t>(MouseButton::Count)];
			static int64_t m_ButtonPressTimestamp[static_cast<uint32_t>(MouseButton::Count)];
			static int64_t m_TimeStamp;

			static int32_t m_MouseRawX;
			static int32_t m_MouseRawY;
			static int32_t m_MouseWheel;

			static bool m_IsAnyButonPressed;
			static bool m_IsAnyButtonReleased;
	};

}
