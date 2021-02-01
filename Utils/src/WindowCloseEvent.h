#pragma once

#include "Event.h"

namespace pawn {
	
	class WindowCloseEvent : public Event {
		
		public:
			WindowCloseEvent();

			EVENT_INFO(WindowClose)
	};
	
}


