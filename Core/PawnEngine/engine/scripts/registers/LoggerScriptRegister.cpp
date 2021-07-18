#include "LoggerScriptRegister.h"

#include "PawnUtils/utils/logger/Logger.h"

namespace pawn {

	namespace engine {

		void LoggerScriptRegister::Register(sol::state& lua) {
			lua.set_function("logger_trace",	utils::LuaTrace);
			lua.set_function("logger_info",		utils::LuaInfo);
			lua.set_function("logger_warning",	utils::LuaWarning);
			lua.set_function("logger_error",	utils::LuaError);
			lua.set_function("logger_debug",	utils::LuaDebug);
		}

	}

}
