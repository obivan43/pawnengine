#pragma once

#include "RegisterScriptClass.h"

namespace pawn {

	namespace engine {

		class TransformationComponentScriptRegister : public RegisterScriptClass {

			public:

				void Register(sol::state& lua) override;

		};

	}

}
