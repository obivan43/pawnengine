#include "MouseManagerScriptRegister.h"

#include "PawnSystem/system/input/MouseManager.h"

namespace pawn {

	namespace engine {

		void MouseManagerScriptRegister::Register(sol::state& lua) {
			lua.new_enum("MouseButton",
				"LeftButton",	system::MouseButton::LeftButton,
				"RightButton",	system::MouseButton::RightButton,
				"CenterButton", system::MouseButton::CenterButton,
				"Button4",		system::MouseButton::Button4,
				"Button5",		system::MouseButton::Button5
			);

			lua.set_function("mouse_buttonPressed",			system::MouseManager::ButtonPressed);
			lua.set_function("mouse_buttonReleased",		system::MouseManager::ButtonReleased);
			lua.set_function("mouse_getRawMouseX",			system::MouseManager::GetRawMouseX);
			lua.set_function("mouse_getRawMouseY",			system::MouseManager::GetRawMouseY);
			lua.set_function("mouse_getMouseWheel",			system::MouseManager::GetMouseWheel);
			lua.set_function("mouse_isAnyButtonPressed",	system::MouseManager::IsAnyButtonPressed);
			lua.set_function("mouse_isAnyButtonReleased",	system::MouseManager::IsAnyButtonReleased);
			lua.set_function("mouse_isMouseConnected",		system::MouseManager::IsMouseConnected);
		}

	}

}
