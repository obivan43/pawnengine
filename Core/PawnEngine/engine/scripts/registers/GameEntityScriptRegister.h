#pragma once

#include "RegisterScriptClass.h"

namespace pawn::engine {

	class GameEntityScriptRegister final : public RegisterScriptClass {

		public:
			GameEntityScriptRegister() = default;
			GameEntityScriptRegister(const GameEntityScriptRegister& other) = delete;
			GameEntityScriptRegister(GameEntityScriptRegister&& other) noexcept = delete;

			GameEntityScriptRegister& operator=(const GameEntityScriptRegister& other) = delete;
			GameEntityScriptRegister& operator=(GameEntityScriptRegister&& other) noexcept = delete;

			void Register(sol::state& lua) const override final;

	};

}
