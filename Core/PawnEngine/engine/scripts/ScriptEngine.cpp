#include "ScriptEngine.h"

#include "registers/LoggerScriptRegister.h"
#include "registers/MouseManagerScriptRegister.h"
#include "registers/KeyboardManagerScriptRegister.h"
#include "registers/ClockScriptRegister.h"
#include "registers/Vec3ScriptRegister.h"
#include "registers/TransformationComponentScriptRegister.h"

#include "PawnSystem/system/input/KeyboardManager.h"

#include "PawnUtils/utils/logger/Logger.h"

namespace pawn {

	namespace engine {

		ScriptEngine::ScriptEngine() {
			m_LuaState.open_libraries(
				sol::lib::base,
				sol::lib::math,
				sol::lib::string
			);

			Register(new LoggerScriptRegister());
			Register(new MouseManagerScriptRegister());
			Register(new KeyboardManagerScriptRegister());
			Register(new ClockScriptRegister());
			Register(new Vec3ScriptRegister());
			Register(new TransformationComponentScriptRegister());

			m_LuaState.script("logger_info('Script engine initialized')");
		}

		void ScriptEngine::ExecOnCreate(const std::string& fileName) {
			m_LuaState.script_file(fileName);

			sol::function create = m_LuaState["create"];
			if (!create.valid()) {
				CONSOLE_ERROR("create function does not exist in {} script", fileName);
				return;
			}

			create();
		}

		void ScriptEngine::ExecOnUpdate(const std::string& fileName, utils::Clock& clock) {
			m_LuaState.script_file(fileName);

			sol::function update = m_LuaState["update"];
			if (!update.valid()) {
				CONSOLE_ERROR("update function does not exist in {} script", fileName);
				return;
			}

			update(clock.DeltaTime());
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
