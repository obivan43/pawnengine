#pragma once

#include "RegisterScriptClass.h"

namespace pawn::engine {

	class GameEntityScriptRegister : public RegisterScriptClass {

		public:

			void Register(sol::state& lua) override;

	};

}
