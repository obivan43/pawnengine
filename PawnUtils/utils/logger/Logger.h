#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/msvc_sink.h"
#include "spdlog/sinks/ostream_sink.h"
#include "spdlog/sinks/dist_sink.h"

#include <memory>

namespace pawn {

	class Logger {
		public:
			static void Init();
			
			static std::shared_ptr<spdlog::logger>& GetLogger() { return m_Logger; }

		private:
			static std::shared_ptr<spdlog::logger> m_Logger;
	};

}

#ifdef LOG_ENABLED

#define CONSOLE_TRACE(...)	pawn::Logger::GetLogger()->trace(__VA_ARGS__);
#define CONSOLE_INFO(...)	pawn::Logger::GetLogger()->info(__VA_ARGS__);
#define CONSOLE_WARN(...)	pawn::Logger::GetLogger()->warn(__VA_ARGS__);
#define CONSOLE_ERROR(...)	pawn::Logger::GetLogger()->error(__VA_ARGS__);
#define CONSOLE_DEBUG(...)	pawn::Logger::GetLogger()->debug(__VA_ARGS__);

#else

#define CONSOLE_TRACE(...)
#define CONSOLE_INFO(...)
#define CONSOLE_WARN(...)
#define CONSOLE_ERROR(...)
#define CONSOLE_DEBUG(...)

#endif