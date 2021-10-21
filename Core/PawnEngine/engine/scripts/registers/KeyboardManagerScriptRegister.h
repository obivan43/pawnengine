#pragma once

#include "RegisterScriptClass.h"

namespace pawn::engine {

		class KeyboardManagerScriptRegister final : public RegisterScriptClass {

			public:
				KeyboardManagerScriptRegister() = default;
				KeyboardManagerScriptRegister(const KeyboardManagerScriptRegister& other) = delete;
				KeyboardManagerScriptRegister(KeyboardManagerScriptRegister&& other) noexcept = delete;

				KeyboardManagerScriptRegister& operator=(const KeyboardManagerScriptRegister& other) = delete;
				KeyboardManagerScriptRegister& operator=(KeyboardManagerScriptRegister&& other) noexcept = delete;

				void Register(sol::state& lua) const override final;

		};

}
