#pragma once

#include "Event.h"

namespace pawn {
	
	class WindowCloseEvent : public Event {
		
		public:
			WindowCloseEvent();

			EVENT_INFO(WindowClose)
	};

	class WindowFocusEvent : public Event {

		public:
			WindowFocusEvent();

			EVENT_INFO(WindowFocus)
	};

	class WindowLostFocusEvent : public Event {

		public:
			WindowLostFocusEvent();

			EVENT_INFO(WindowLostFocus)
	};

	class WindowResizeEvent : public Event {

		public:
			WindowResizeEvent(uint32_t width, uint32_t height);

			EVENT_INFO(WindowResize)

			const int32_t m_Width;
			const int32_t m_Height;
	};

	class WindowMovedEvent : public Event {

		public:
			WindowMovedEvent(int32_t x, int32_t y);

			EVENT_INFO(WindowMoved)

			const int32_t m_X;
			const int32_t m_Y;
	};
	
}


