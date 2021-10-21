#pragma once

#include "registers/RegisterScriptClass.h"

#include "PawnEngine/engine/GameEntity.h"
#include "PawnUtils/utils/time/Clock.h"

#include <memory>
#include <sol.hpp>
#include <vector>

namespace pawn::engine {

	class ScriptEngine {

		public:
			ScriptEngine();
			~ScriptEngine();

			ScriptEngine(const ScriptEngine& other) = delete;
			ScriptEngine(ScriptEngine&& other) noexcept = delete;

			ScriptEngine& operator=(const ScriptEngine& other) = delete;
			ScriptEngine& operator=(ScriptEngine&& other) noexcept = delete;

			void Register(std::unique_ptr<RegisterScriptClass>&& scriptRegister);
			void ExecOnCreate(const std::string& path, pawn::engine::GameEntity entity);
			void ExecOnUpdate(const std::string& path, utils::Clock& clock, pawn::engine::GameEntity entity);

			void SetIsPaused(bool state);
			bool GetIsPaused() const { return m_IsPaused; }

		private:
			static inline pawn::engine::GameEntity GetScriptableEntity() { return m_ScriptableEntity; }

		private:
			static pawn::engine::GameEntity m_ScriptableEntity;

			bool m_IsPaused;

			sol::state m_LuaState;
			std::vector<std::unique_ptr<RegisterScriptClass>> m_ScriptsRegisters;
	};

}
