#pragma once

#include "RegisterScriptClass.h"

namespace pawn::engine {

	class MouseManagerScriptRegister final : public RegisterScriptClass {

		public:
		MouseManagerScriptRegister() = default;
		MouseManagerScriptRegister(const MouseManagerScriptRegister & other) = delete;
		MouseManagerScriptRegister(MouseManagerScriptRegister && other) noexcept = delete;

		MouseManagerScriptRegister& operator=(const MouseManagerScriptRegister & other) = delete;
		MouseManagerScriptRegister& operator=(MouseManagerScriptRegister && other) noexcept = delete;

			void Register(sol::state& lua) const override final;

	};

}
