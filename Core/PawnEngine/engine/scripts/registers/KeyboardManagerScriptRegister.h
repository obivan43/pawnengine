#pragma once

#include "RegisterScriptClass.h"

namespace pawn {

	namespace engine {

		class KeyboardManagerScriptRegister : public RegisterScriptClass {

		public:

			void Register(sol::state& lua) override;

		};

	}

}
