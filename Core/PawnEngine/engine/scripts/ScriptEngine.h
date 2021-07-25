#pragma once

#include <sol.hpp>

#include "registers/RegisterScriptClass.h"

#include "PawnUtils/utils/time/Clock.h"

#include <vector>

namespace pawn {

	namespace engine {

		class ScriptEngine {

			public:
				
				ScriptEngine();
				~ScriptEngine();

				void Register(RegisterScriptClass* scriptClass);
				void ExecOnCreate(const std::string& fileName);
				void ExecOnUpdate(const std::string& fileName, utils::Clock& clock);

			private:

				sol::state m_LuaState;
				std::vector<RegisterScriptClass*> m_ClassList;
		};

	}


}
