#pragma once

#include <cstdint>

namespace pawn {

	namespace system {

		enum class MouseButton : uint32_t {
			LeftButton = 0,
			RightButton = 1,
			CenterButton = 2,
			Button4 = 3,
			Button5 = 4,

			Count = 5,
			None = 0xFFFFFFFF
		};

	}

}
