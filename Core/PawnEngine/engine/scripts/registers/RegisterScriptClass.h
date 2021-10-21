#pragma once

#include <sol.hpp>

namespace pawn::engine {

	class RegisterScriptClass {

		public:
			RegisterScriptClass() = default;
			virtual ~RegisterScriptClass() = default;

			RegisterScriptClass(const RegisterScriptClass& other) = delete;
			RegisterScriptClass(RegisterScriptClass&& other) noexcept = delete;

			RegisterScriptClass& operator=(const RegisterScriptClass& other) = delete;
			RegisterScriptClass& operator=(RegisterScriptClass&& other) noexcept = delete;

			virtual void Register(sol::state& lua) const = 0;

	};
}
