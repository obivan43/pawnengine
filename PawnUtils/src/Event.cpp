#include "pch.h"
#include "Event.h"

namespace pawn {
	Event::Event(EventTypeEnum type)
	: m_Type(type), m_IsHandeled(false)
	{}
}
