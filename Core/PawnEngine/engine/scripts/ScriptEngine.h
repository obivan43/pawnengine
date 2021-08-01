#pragma once

#include <sol.hpp>

#include "registers/RegisterScriptClass.h"

#include "PawnUtils/utils/time/Clock.h"

#include "PawnEngine/engine/GameEntity.h"

#include <vector>

namespace pawn {

	namespace engine {

		class ScriptEngine {

			public:
				
				ScriptEngine();
				~ScriptEngine();

				void Register(RegisterScriptClass* scriptClass);
				void ExecOnCreate(const std::string& fileName, pawn::engine::GameEntity entity);
				void ExecOnUpdate(const std::string& fileName, utils::Clock& clock, pawn::engine::GameEntity entity);

			private:
				static pawn::engine::GameEntity GetCurrentEntity() { return m_CurrentEntity; }

			private:
				static pawn::engine::GameEntity m_CurrentEntity;
				sol::state m_LuaState;
				std::vector<RegisterScriptClass*> m_ClassList;
		};

	}


}
