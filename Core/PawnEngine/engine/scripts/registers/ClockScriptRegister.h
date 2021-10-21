#pragma once

#include "RegisterScriptClass.h"

namespace pawn::engine {

	class ClockScriptRegister final : public RegisterScriptClass {

		public:
			ClockScriptRegister() = default;
			ClockScriptRegister(const ClockScriptRegister& other) = delete;
			ClockScriptRegister(ClockScriptRegister&& other) noexcept = delete;

			ClockScriptRegister& operator=(const ClockScriptRegister& other) = delete;
			ClockScriptRegister& operator=(ClockScriptRegister&& other) noexcept = delete;

			void Register(sol::state& lua) const override final;

	};

}
