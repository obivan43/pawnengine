#include "MouseManagerScriptRegister.h"

#include "PawnEngine/engine/EngineGlobals.h"
#include "PawnSystem/system/input/MouseManager.h"

namespace pawn::engine {

	void MouseManagerScriptRegister::Register(sol::state& lua) const {
		lua.new_enum("MouseButton",
			"LeftButton", system::MouseButton::LeftButton,
			"RightButton", system::MouseButton::RightButton,
			"CenterButton", system::MouseButton::CenterButton,
			"Button4", system::MouseButton::Button4,
			"Button5", system::MouseButton::Button5
		);

		lua.set_function("mouse_buttonPressed",
			[](system::MouseButton button) {
				return GetMouseHandlingStateInScripts() ? system::MouseManager::ButtonPressed(button) : false;
			}
		);

		lua.set_function("mouse_buttonReleased",
			[](system::MouseButton button) {
				return GetMouseHandlingStateInScripts() ? system::MouseManager::ButtonReleased(button) : false;
			}
		);

		lua.set_function("mouse_getRawMouseX", []() {
			return GetMouseHandlingStateInScripts() ? system::MouseManager::GetRawMouseX() : 0;
			});

		lua.set_function("mouse_getRawMouseY",
			[]() {
				return GetMouseHandlingStateInScripts() ? system::MouseManager::GetRawMouseY() : 0;
			}
		);

		lua.set_function("mouse_getMouseWheel",
			[]() {
				return GetMouseHandlingStateInScripts() ? system::MouseManager::GetMouseWheel() : 0;
			}
		);

		lua.set_function("mouse_isAnyButtonPressed",
			[]() {
				return GetMouseHandlingStateInScripts() ? system::MouseManager::IsAnyButtonPressed() : false;
			}
		);

		lua.set_function("mouse_isAnyButtonReleased",
			[]() {
				return GetMouseHandlingStateInScripts() ? system::MouseManager::IsAnyButtonReleased() : false;
			}
		);

		lua.set_function("mouse_isMouseConnected",
			[]() {
				return GetMouseHandlingStateInScripts() ? system::MouseManager::IsMouseConnected() : false;
			}
		);
	}

}
