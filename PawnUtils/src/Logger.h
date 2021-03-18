#pragma once

#include "Macros.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#ifdef LOG_ENABLED

#define CONSOLE_TRACE(...)	spdlog::default_logger_raw()->trace(__VA_ARGS__);
#define CONSOLE_INFO(...)	spdlog::default_logger_raw()->info(__VA_ARGS__);
#define CONSOLE_WARN(...)	spdlog::default_logger_raw()->warn(__VA_ARGS__);
#define CONSOLE_ERROR(...)	spdlog::default_logger_raw()->error(__VA_ARGS__);
#define CONSOLE_DEBUG(...)	spdlog::default_logger_raw()->debug(__VA_ARGS__);

#else

#define CONSOLE_TRACE(...)
#define CONSOLE_INFO(...)
#define CONSOLE_WARN(...)
#define CONSOLE_ERROR(...)
#define CONSOLE_DEBUG(...)

#endif