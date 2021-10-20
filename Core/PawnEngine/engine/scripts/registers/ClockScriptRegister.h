#pragma once

#include "RegisterScriptClass.h"

namespace pawn::engine {

	class ClockScriptRegister : public RegisterScriptClass {

		public:

			void Register(sol::state& lua) override;

	};

}
