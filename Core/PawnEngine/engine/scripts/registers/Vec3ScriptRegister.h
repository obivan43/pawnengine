#pragma once

#include "RegisterScriptClass.h"

namespace pawn::engine {

	class Vec3ScriptRegister : public RegisterScriptClass {

		public:

			void Register(sol::state& lua) override;

	};

}
