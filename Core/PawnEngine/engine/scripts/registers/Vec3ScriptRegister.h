#pragma once

#include "RegisterScriptClass.h"

namespace pawn {

	namespace engine {

		class Vec3ScriptRegister : public RegisterScriptClass {

			public:

				void Register(sol::state& lua) override;

		};

	}

}
