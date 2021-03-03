#pragma once

#include "Event.h"

namespace pawn {

	class MouseMove : public Event {

		public:
			MouseMove(int32_t x, int32_t y);

			EVENT_INFO(MouseMove)

			const int32_t m_X;
			const int32_t m_Y;
	};
	
}
