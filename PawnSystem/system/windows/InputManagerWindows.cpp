#include "InputManagerWindows.h"
#include "../../../PawnUtils/src/Clock.h"

#ifdef _WIN32

#include <hidusage.h>
#include <vector>

namespace pawn {

	namespace system {

		std::queue<InputManagerWindows::InputData> InputManagerWindows::m_MouseInputs{};
		std::queue<InputManagerWindows::InputData> InputManagerWindows::m_KeyboardInputs{};

		bool InputManagerWindows::m_IsMouseRegistered = false;
		bool InputManagerWindows::m_IsMouseConnected = false;
		bool InputManagerWindows::m_IsKeyboardRegistered = false;
		bool InputManagerWindows::m_IsKeyboardConnected = false;

		LRESULT InputManagerWindows::HandleInput(HRAWINPUT inputHandle) {
			static Clock clock{};

			UINT size{ 0 };
			UINT result = GetRawInputData(inputHandle, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER));
			if (result == static_cast<UINT>(-1)) {
				return 0;
			}

			std::vector<uint8_t> buffer{};
			buffer.resize(size);

			RAWINPUT* input = reinterpret_cast<RAWINPUT*>(buffer.data());
			result = GetRawInputData(inputHandle, RID_INPUT, input, &size, sizeof(RAWINPUTHEADER));
			if (result == static_cast<UINT>(-1)) {
				return 0;
			}

			InputData inputData{};
			memcpy(&inputData.input, input, sizeof(RAWINPUT));

			clock.Tick();
			inputData.timestamp = clock.TimeStamp();

			switch (input->header.dwType) {
				case RIM_TYPEMOUSE:
					m_MouseInputs.push(inputData);
					break;
				case RIM_TYPEKEYBOARD:
					m_KeyboardInputs.push(inputData);
					break;

			}

			return 0;
		}

		LRESULT InputManagerWindows::HandleInputDeviceChanged() {
			m_IsMouseConnected = false;
			m_IsKeyboardConnected = false;

			UINT size{0};
			UINT result = GetRawInputDeviceList(nullptr, &size, sizeof(RAWINPUTDEVICELIST));
			if (result == static_cast<UINT>(-1) || size == 0) {
				return 0;
			}

			std::vector<RAWINPUTDEVICELIST> deviceList{};
			deviceList.resize(size);
			result = GetRawInputDeviceList(deviceList.data(), &size, sizeof(RAWINPUTDEVICELIST));
			if (result == static_cast<UINT>(-1) || result != size) {
				return 0;
			}

			for (const RAWINPUTDEVICELIST& device : deviceList) {
				switch (device.dwType) {
					case RIM_TYPEMOUSE:
						m_IsMouseConnected = m_IsMouseRegistered;
						break;
					case RIM_TYPEKEYBOARD:
						m_IsKeyboardConnected = m_IsKeyboardRegistered;
						break;
				}
			}

			return 0;
		}

		bool InputManagerWindows::WinHandle(UINT message, WPARAM wparam, LPARAM lparam, LRESULT* result) {
			switch (message) {
				case WM_INPUT: {
					HRAWINPUT inputHandle = reinterpret_cast<HRAWINPUT>(lparam);
					USHORT inputCode = GET_RAWINPUT_CODE_WPARAM(wparam);

					if (inputCode != RIM_INPUT && inputCode != RIM_INPUTSINK)
						break;

					*result = HandleInput(inputHandle);

					if (inputCode == RIM_INPUT)
						DefWindowProc(GetGameEngineWindowHWND(), message, wparam, lparam);

					return true;
				}
				case WM_INPUT_DEVICE_CHANGE: {
					*result = HandleInputDeviceChanged();
					return true;
				}
			}

			return false;
		}

		bool InputManagerWindows::ProccessMouse(uint64_t maxTimestamp, InputData& out) {
			if (m_MouseInputs.size() > 0) {
				InputData inputData{};
				inputData = m_MouseInputs.front();
				if (inputData.timestamp == 0 || inputData.timestamp > maxTimestamp)
					return false;

				out.input = inputData.input;
				out.timestamp = inputData.timestamp;

				m_MouseInputs.pop();

				return true;
			}

			return false;
		}

		bool InputManagerWindows::ProccessKeyboard(uint64_t maxTimestamp, InputData& out) {
			if (m_KeyboardInputs.size() > 0) {
				InputData inputData{};
				inputData = m_KeyboardInputs.front();
				if (inputData.timestamp == 0 || inputData.timestamp > maxTimestamp)
					return false;

				out.input = inputData.input;
				out.timestamp = inputData.timestamp;

				m_KeyboardInputs.pop();

				return true;
			}

			return false;
		}

		bool InputManagerWindows::RegisterDevice(USHORT usage, DWORD flags, HWND handle) {
			RAWINPUTDEVICE rawInputDevice{};
			rawInputDevice.usUsagePage = HID_USAGE_PAGE_GENERIC;
			rawInputDevice.usUsage = usage;
			rawInputDevice.dwFlags = flags;
			rawInputDevice.hwndTarget = handle;

			return RegisterRawInputDevices(&rawInputDevice, 1, sizeof(RAWINPUTDEVICE));
		}

		void InputManagerWindows::RegisterMouse() {
			if (!m_IsMouseRegistered) {
				bool result = RegisterDevice(HID_USAGE_GENERIC_MOUSE, RIDEV_DEVNOTIFY, GetGameEngineWindowHWND());

				if (result) {
					m_IsMouseRegistered = true;
					HandleInputDeviceChanged();
				}
			}
		}

		void InputManagerWindows::RegisterKeyboard() {
			if (!m_IsKeyboardRegistered) {
				bool result = RegisterDevice(HID_USAGE_GENERIC_KEYBOARD, RIDEV_DEVNOTIFY, GetGameEngineWindowHWND());

				if (result) {
					m_IsKeyboardRegistered = true;
					HandleInputDeviceChanged();
				}
			}
		}

		void InputManagerWindows::UnregisterMouse() {
			if (m_IsMouseRegistered) {
				bool result = RegisterDevice(HID_USAGE_GENERIC_MOUSE, RIDEV_REMOVE, nullptr);

				if (result) {
					m_IsMouseRegistered = false;
					HandleInputDeviceChanged();
				}
			}
		}

		void InputManagerWindows::UnregisterKeyboard() {
			if (m_IsKeyboardRegistered) {
				bool result = RegisterDevice(HID_USAGE_GENERIC_KEYBOARD, RIDEV_REMOVE, nullptr);

				if (result) {
					m_IsKeyboardRegistered = false;
					HandleInputDeviceChanged();
				}
			}
		}

	}

}

#endif
