#include "Logger.h"

#include <iostream>

namespace pawn {

	namespace utils {

		std::shared_ptr<spdlog::logger> Logger::m_Logger;
		std::shared_ptr<spdlog::logger> Logger::m_LuaLogger;

		void Logger::Init() {
			auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			auto msvc_sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
			auto dist_sink = std::make_shared<spdlog::sinks::dist_sink_st>();
			auto ostream_sink = std::make_shared<spdlog::sinks::ostream_sink_st>(std::cout);

			dist_sink->add_sink(msvc_sink);
			dist_sink->add_sink(console_sink);
			dist_sink->add_sink(ostream_sink);

			m_Logger = std::make_shared<spdlog::logger>("pawn", dist_sink);
#ifdef PAWN_TRACE_LOGGER_LEVEL
			m_Logger->set_level(spdlog::level::trace);
#endif

			m_LuaLogger = std::make_shared<spdlog::logger>("Lua", dist_sink);
		}

		void LuaTrace(const char* str) {
#ifdef PAWN_LOG_ENABLED
			pawn::utils::Logger::GetLuaLogger()->trace(str);
#endif
		}

		void LuaInfo(const char* str) {
#ifdef PAWN_LOG_ENABLED
			pawn::utils::Logger::GetLuaLogger()->info(str);
#endif
		}

		void LuaWarning(const char* str) {
#ifdef PAWN_LOG_ENABLED
			pawn::utils::Logger::GetLuaLogger()->warn(str);
#endif
		}

		void LuaError(const char* str) {
#ifdef PAWN_LOG_ENABLED
			pawn::utils::Logger::GetLuaLogger()->error(str);
#endif
		}

		void LuaDebug(const char* str) {
#ifdef PAWN_LOG_ENABLED
			pawn::utils::Logger::GetLuaLogger()->debug(str);
#endif
		}

	}

}
