#include "ClockScriptRegister.h"

#include "PawnUtils/utils/time/Clock.h"

#include <sol.hpp>

namespace pawn::engine {

	void ClockScriptRegister::Register(sol::state& lua) {
		lua.set_function("clock_timestamp", utils::Clock::TimeStamp);
		lua.set_function("clock_timestampToSeconds", utils::Clock::TimeStampToSeconds);
	}

}
