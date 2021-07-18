#pragma once

#include <sol.hpp>

namespace pawn {

	namespace engine {

		class RegisterScriptClass {

			public:

				virtual ~RegisterScriptClass() = default;

				virtual void Register(sol::state& lua) = 0;

		};

	}

}
