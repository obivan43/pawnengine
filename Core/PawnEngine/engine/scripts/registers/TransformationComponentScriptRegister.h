#pragma once

#include "RegisterScriptClass.h"

namespace pawn::engine {

	class TransformationComponentScriptRegister : public RegisterScriptClass {

		public:

			void Register(sol::state& lua) override;

	};

}
