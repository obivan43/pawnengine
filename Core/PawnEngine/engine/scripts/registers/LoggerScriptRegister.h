#pragma once

#include "RegisterScriptClass.h"

namespace pawn {

	namespace engine {

		class LoggerScriptRegister : public RegisterScriptClass {

			public:

				void Register(sol::state& lua) override;

		};

	}

}
