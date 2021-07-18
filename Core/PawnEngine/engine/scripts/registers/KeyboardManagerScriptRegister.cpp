#include "KeyboardManagerScriptRegister.h"

#include "PawnSystem/system/input/KeyboardManager.h"

namespace pawn {

	namespace engine {

		void KeyboardManagerScriptRegister::Register(sol::state& lua) {
			lua.new_enum("Button",
				"Escape", system::Button::Escape,
				"One", system::Button::One,
				"Two", system::Button::Two,
				"Three", system::Button::Three,
				"Four", system::Button::Four,
				"Five", system::Button::Five,
				"Six", system::Button::Six,
				"Seven", system::Button::Seven,
				"Eight", system::Button::Eight,
				"Nine", system::Button::Nine,
				"Zero", system::Button::Zero,
				"Minus", system::Button::Minus,
				"Equals", system::Button::Equals,
				"Backspace", system::Button::Backspace,
				"Tab", system::Button::Tab,
				"Q", system::Button::Q,
				"W", system::Button::W,
				"E", system::Button::E,
				"R", system::Button::R,
				"T", system::Button::T,
				"Y", system::Button::Y,
				"U", system::Button::U,
				"I", system::Button::I,
				"O", system::Button::O,
				"P", system::Button::P,
				"LeftBracket", system::Button::LeftBracket,
				"RightBracket", system::Button::RightBracket,
				"Return", system::Button::Return,
				"LeftControl", system::Button::LeftControl,
				"A", system::Button::A,
				"S", system::Button::S,
				"D", system::Button::D,
				"F", system::Button::F,
				"G", system::Button::G,
				"H", system::Button::H,
				"J", system::Button::J,
				"K", system::Button::K,
				"L", system::Button::L,
				"Semicolon", system::Button::Semicolon,
				"Apostrophe", system::Button::Apostrophe,
				"Grave", system::Button::Grave,
				"LeftShift", system::Button::LeftShift,
				"Backslash", system::Button::Backslash,
				"Z", system::Button::Z,
				"X", system::Button::X,
				"C", system::Button::C,
				"V", system::Button::V,
				"B", system::Button::B,
				"N", system::Button::N,
				"M", system::Button::M,
				"Comma", system::Button::Comma,
				"Period", system::Button::Period,
				"Slash", system::Button::Slash,
				"RightShift", system::Button::RightShift,
				"NumpadMultiply", system::Button::NumpadMultiply,
				"LeftAlt", system::Button::LeftAlt,
				"Space", system::Button::Space,
				"CapsLock", system::Button::CapsLock,
				"F1", system::Button::F1,
				"F2", system::Button::F2,
				"F3", system::Button::F3,
				"F4", system::Button::F4,
				"F5", system::Button::F5,
				"F6", system::Button::F6,
				"F7", system::Button::F7,
				"F8", system::Button::F8,
				"F9", system::Button::F9,
				"F10", system::Button::F10,
				"ScrollLock", system::Button::ScrollLock,
				"F11", system::Button::F11,
				"F12", system::Button::F12,
				"RightControl", system::Button::RightControl,
				"SysReq", system::Button::SysReq,
				"RightAlt", system::Button::RightAlt,
				"Pause", system::Button::Pause,
				"Home", system::Button::Home,
				"UpArrow", system::Button::UpArrow,
				"PageUp", system::Button::PageUp,
				"LeftArrow", system::Button::LeftArrow,
				"RightArrow", system::Button::RightArrow,
				"End", system::Button::End,
				"DownArrow", system::Button::DownArrow,
				"PageDown", system::Button::PageDown,
				"Insert", system::Button::Insert,
				"Delete", system::Button::Delete,
				"Count", system::Button::Count,
				"None", system::Button::None
			);

			lua.set_function("keyboard_buttonPressed",			system::KeyboardManager::ButtonPressed);
			lua.set_function("keyboard_buttonReleased",			system::KeyboardManager::ButtonReleased);
			lua.set_function("keyboard_isAnyButtonPressed",		system::KeyboardManager::IsAnyButtonPressed);
			lua.set_function("keyboard_isAnyButtonReleased",	system::KeyboardManager::IsAnyButtonReleased);
			lua.set_function("keyboard_isKeyboardConnected",	system::KeyboardManager::IsKeyboardConnected);
		}

	}

}
