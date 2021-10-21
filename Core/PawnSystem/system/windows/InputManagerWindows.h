#pragma once

#ifdef _WIN32

#include "SystemPC.h"

#include <queue>

namespace pawn::system {

	class InputManagerWindows {

		public:
			InputManagerWindows() = delete;
			InputManagerWindows(const InputManagerWindows& other) = delete;
			InputManagerWindows(InputManagerWindows&& other) noexcept = delete;

			InputManagerWindows& operator=(const InputManagerWindows& other) = delete;
			InputManagerWindows& operator=(InputManagerWindows&& other) noexcept = delete;

			struct InputData {
				RAWINPUT input;
				int64_t timestamp;
			};

			static bool WinHandle(UINT message, WPARAM wparam, LPARAM lparam, LRESULT* result);

			static bool ProccessMouse(int64_t maxTimestamp, InputData& out);
			static bool ProccessKeyboard(int64_t maxTimestamp, InputData& out);

			static void RegisterMouse();
			static void RegisterKeyboard();
			static void UnregisterMouse();
			static void UnregisterKeyboard();

			inline static bool IsMouseConnected() noexcept { return m_IsMouseConnected; }
			inline static bool IsKeyboardConnected() noexcept { return m_IsKeyboardConnected; }

		private:
			static LRESULT HandleInput(HRAWINPUT inputHandle);
			static LRESULT HandleInputDeviceChanged();
			static bool RegisterDevice(USHORT usage, DWORD flags, HWND handle);

		private:
			static std::queue<InputData> m_MouseInputs;
			static std::queue<InputData> m_KeyboardInputs;

			static bool m_IsMouseRegistered;
			static bool m_IsMouseConnected;
			static bool m_IsKeyboardRegistered;
			static bool m_IsKeyboardConnected;
	};

}

#endif
