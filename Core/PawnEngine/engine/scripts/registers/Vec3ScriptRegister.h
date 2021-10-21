#pragma once

#include "RegisterScriptClass.h"

namespace pawn::engine {

	class Vec3ScriptRegister final : public RegisterScriptClass {

		public:
			Vec3ScriptRegister() = default;
			Vec3ScriptRegister(const Vec3ScriptRegister& other) = delete;
			Vec3ScriptRegister(Vec3ScriptRegister&& other) noexcept = delete;

			Vec3ScriptRegister& operator=(const Vec3ScriptRegister& other) = delete;
			Vec3ScriptRegister& operator=(Vec3ScriptRegister&& other) noexcept = delete;

			void Register(sol::state& lua) const override final;

	};

}
