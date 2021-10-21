#pragma once

#include "RegisterScriptClass.h"

namespace pawn::engine {

	class LoggerScriptRegister final : public RegisterScriptClass {

		public:
			LoggerScriptRegister() = default;
			LoggerScriptRegister(const LoggerScriptRegister& other) = delete;
			LoggerScriptRegister(LoggerScriptRegister&& other) noexcept = delete;

			LoggerScriptRegister& operator=(const LoggerScriptRegister& other) = delete;
			LoggerScriptRegister& operator=(LoggerScriptRegister&& other) noexcept = delete;

			void Register(sol::state& lua) const override final;

	};

}
