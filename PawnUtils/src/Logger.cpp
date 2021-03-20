#include "pch.h"
#include "Logger.h"

#include <iostream>

namespace pawn {

	std::shared_ptr<spdlog::logger> Logger::m_Logger;

	void Logger::Init() {
		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		auto msvc_sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
		auto dist_sink = std::make_shared<spdlog::sinks::dist_sink_st>();
		auto ostream_sink = std::make_shared<spdlog::sinks::ostream_sink_st>(std::cout);

		dist_sink->add_sink(msvc_sink);
		dist_sink->add_sink(console_sink);
		dist_sink->add_sink(ostream_sink);

		m_Logger = std::make_shared<spdlog::logger>("pawn", dist_sink);
	}

}