#include "pch.h"
#include "MouseEvents.h"

namespace pawn {

	MouseMove::MouseMove(int32_t x, int32_t y) : Event(EventTypeEnum::MouseMove), m_X(x), m_Y(y) {}
	
}
