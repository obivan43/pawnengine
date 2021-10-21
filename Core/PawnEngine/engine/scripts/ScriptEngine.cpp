#include "ScriptEngine.h"

#include "registers/LoggerScriptRegister.h"
#include "registers/MouseManagerScriptRegister.h"
#include "registers/KeyboardManagerScriptRegister.h"
#include "registers/ClockScriptRegister.h"
#include "registers/Vec3ScriptRegister.h"
#include "registers/TransformationComponentScriptRegister.h"
#include "registers/GameEntityScriptRegister.h"

#include "PawnSystem/system/input/KeyboardManager.h"
#include "PawnUtils/utils/logger/Logger.h"

namespace pawn::engine {

	pawn::engine::GameEntity ScriptEngine::m_ScriptableEntity;

	ScriptEngine::ScriptEngine() : m_IsPaused(true) {
		m_LuaState.open_libraries(
			sol::lib::base,
			sol::lib::math,
			sol::lib::string
		);

		Register(std::make_unique<LoggerScriptRegister>());
		Register(std::make_unique<MouseManagerScriptRegister>());
		Register(std::make_unique<KeyboardManagerScriptRegister>());
		Register(std::make_unique<ClockScriptRegister>());
		Register(std::make_unique<Vec3ScriptRegister>());
		Register(std::make_unique<TransformationComponentScriptRegister>());
		Register(std::make_unique<GameEntityScriptRegister>());

		m_LuaState.set_function("current_entity", GetScriptableEntity);
		m_LuaState.script("logger_info('Script engine initialized')");
	}

	void ScriptEngine::ExecOnCreate(const std::string& fileName, pawn::engine::GameEntity entity) {
		m_LuaState.script_file(fileName);
		m_ScriptableEntity = entity;

		sol::function create = m_LuaState["create"];
		if (!create.valid()) {
			CONSOLE_ERROR("create function does not exist in {} script", fileName);
			return;
		}

		create();
	}

	void ScriptEngine::SetIsPaused(bool state) {
		m_IsPaused = state;

		if (m_IsPaused) {
			m_LuaState.stack_clear();
		}
	}

	void ScriptEngine::ExecOnUpdate(const std::string& fileName, utils::Clock& clock, pawn::engine::GameEntity entity) {
		m_LuaState.stack_clear();
		auto& res = m_LuaState.script_file(fileName);
		m_ScriptableEntity = entity;

		if (!res.valid()) {
			CONSOLE_ERROR("invalid script file {}", fileName);
			return;
		}

		sol::function update = m_LuaState["update"];
		if (!update.valid()) {
			CONSOLE_ERROR("update function does not exist in {} script", fileName);
			return;
		}

		update(clock.DeltaTime());
	}

	ScriptEngine::~ScriptEngine() {
		m_ScriptsRegisters.clear();
	}

	void ScriptEngine::Register(std::unique_ptr<RegisterScriptClass>&& scriptRegister) {
		scriptRegister->Register(m_LuaState);
		m_ScriptsRegisters.emplace_back(std::move(scriptRegister));
	}

}
