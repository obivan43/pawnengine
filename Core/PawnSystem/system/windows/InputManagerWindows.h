#pragma once

#ifdef _WIN32

#include "SystemPC.h"
#include <queue>

namespace pawn {

	namespace system {

		class InputManagerWindows {

			private:
				InputManagerWindows() = default;

				static LRESULT HandleInput(HRAWINPUT inputHandle);
				static LRESULT HandleInputDeviceChanged();
				static bool RegisterDevice(USHORT usage, DWORD flags, HWND handle);

			public:

				struct InputData {
					RAWINPUT input;
					uint64_t timestamp;
				};

				static bool WinHandle(UINT message, WPARAM wparam, LPARAM lparam, LRESULT* result);

				static bool ProccessMouse(uint64_t maxTimestamp, InputData& out);
				static bool ProccessKeyboard(uint64_t maxTimestamp, InputData& out);

				static void RegisterMouse();
				static void RegisterKeyboard();
				static void UnregisterMouse();
				static void UnregisterKeyboard();

				static bool IsMouseConnected() { return m_IsMouseConnected; }
				static bool IsKeyboardConnected() { return m_IsKeyboardConnected; }

			private:
				static std::queue<InputData> m_MouseInputs;
				static std::queue<InputData> m_KeyboardInputs;

				static bool m_IsMouseRegistered;
				static bool m_IsMouseConnected;
				static bool m_IsKeyboardRegistered;
				static bool m_IsKeyboardConnected;
		};

	}

}

#endif
