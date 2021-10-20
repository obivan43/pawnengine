#pragma once

#include "RegisterScriptClass.h"

namespace pawn::engine {

	class MouseManagerScriptRegister : public RegisterScriptClass {

		public:

			void Register(sol::state& lua) override;

	};

}
