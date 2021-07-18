#include "ScriptEngine.h"

#include "registers/LoggerScriptRegister.h"
#include "registers/MouseManagerScriptRegister.h"
#include "registers/KeyboardManagerScriptRegister.h"

#include "PawnSystem/system/input/KeyboardManager.h"

namespace pawn {

	namespace engine {

		ScriptEngine::ScriptEngine() {
			m_LuaState.open_libraries(
				sol::lib::base,
				sol::lib::math,
				sol::lib::string,
				sol::lib::io
			);

			Register(new LoggerScriptRegister());
			Register(new MouseManagerScriptRegister());
			Register(new KeyboardManagerScriptRegister());

			m_LuaState.script("logger_info('Script engine initialized')");
		}

		ScriptEngine::~ScriptEngine() {
			m_ClassList.clear();
		}

		void ScriptEngine::Register(RegisterScriptClass* scriptClass) {
			scriptClass->Register(m_LuaState);
			m_ClassList.emplace_back(scriptClass);
		}

	}

}
