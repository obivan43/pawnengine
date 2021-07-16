#include "Keyboard.h"
#include "../windows/SystemPC.h"

#ifdef _WIN32

#include <WinUser.h>

#define HIGH_BIT(button) (button << 7)
#define KEYBOARD_STATE_FLAG (1 << 2)

namespace pawn {

	namespace system {

		char Keyboard::ConvertToPrintable(Keyboard::Key key, bool isShiftPressed) {
			const DWORD threadID = GetWindowThreadProcessId(GetGameEngineWindowHWND(), nullptr);
			const HKL keyboardLayout = GetKeyboardLayout(threadID);
			const UINT vkCode = static_cast<UINT>(key);
			const UINT scanCode = MapVirtualKeyEx(vkCode, MAPVK_VK_TO_VSC_EX, keyboardLayout);

			if (!scanCode) {
				return '\0';
			}

			BYTE keyboardState[256] = { 0 };
			keyboardState[VK_SHIFT] = HIGH_BIT(isShiftPressed);
			keyboardState[VK_NUMLOCK] = 1;
			keyboardState[VK_CAPITAL] = 0;

			const UINT charBufferSize = 1;
			WCHAR charBuffer[charBufferSize] = { 0 };

			int charsConverted = ToUnicodeEx(
				vkCode, 
				scanCode,
				keyboardState, 
				charBuffer,
				charBufferSize,
				KEYBOARD_STATE_FLAG,
				keyboardLayout
			);

			if (charsConverted != 1) {
				return '\0';
			}

			return static_cast<char>(charBuffer[0]);
		}

	}

}

#endif
