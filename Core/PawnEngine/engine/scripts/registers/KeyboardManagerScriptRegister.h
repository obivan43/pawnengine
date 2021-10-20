#pragma once

#include "RegisterScriptClass.h"

namespace pawn::engine {

		class KeyboardManagerScriptRegister : public RegisterScriptClass {

			public:

				void Register(sol::state& lua) override;

		};

}
