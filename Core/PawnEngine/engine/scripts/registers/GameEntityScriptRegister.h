#pragma once

#include "RegisterScriptClass.h"

namespace pawn {

	namespace engine {

		class GameEntityScriptRegister : public RegisterScriptClass {

			public:

				void Register(sol::state& lua) override;

		};

	}

}
