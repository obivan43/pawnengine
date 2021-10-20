#pragma once

#include "RegisterScriptClass.h"

namespace pawn::engine {

	class LoggerScriptRegister : public RegisterScriptClass {

		public:

			void Register(sol::state& lua) override;

	};

}
