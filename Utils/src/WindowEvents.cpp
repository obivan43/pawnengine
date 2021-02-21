#include "pch.h"
#include "WindowEvents.h"

namespace pawn {
	
	WindowCloseEvent::WindowCloseEvent() : Event(EventTypeEnum::WindowClose) {}

	WindowFocusEvent::WindowFocusEvent() : Event(EventTypeEnum::WindowFocus) {}

	WindowLostFocusEvent::WindowLostFocusEvent() : Event(EventTypeEnum::WindowLostFocus) {}

	WindowResizeEvent::WindowResizeEvent(uint32_t width, uint32_t height) : Event(EventTypeEnum::WindowResize), m_Width(width), m_Height(height) {}

	WindowMovedEvent::WindowMovedEvent(int32_t x, int32_t y) : Event(EventTypeEnum::WindowMoved), m_X(x), m_Y(y) {}
	
}
