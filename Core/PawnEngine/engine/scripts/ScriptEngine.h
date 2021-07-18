#pragma once

#include <sol.hpp>

#include "registers/RegisterScriptClass.h"

#include <vector>

namespace pawn {

	namespace engine {

		class ScriptEngine {

			public:
				
				ScriptEngine();
				~ScriptEngine();

				void Register(RegisterScriptClass* scriptClass);

				void Test();

			private:

				sol::state m_LuaState;
				std::vector<RegisterScriptClass*> m_ClassList;
		};

	}


}
