#pragma once

#include "Event.h"

namespace pawn {
	
	class KeyboardPress : public Event {
		
		public:
			KeyboardPress(uint8_t code);

			EVENT_INFO(KeyboardPress)

			const uint8_t m_Code;
	};

	class KeyboardRelease : public Event {

		public:
			KeyboardRelease(uint8_t code);

			EVENT_INFO(KeyboardRelease)

			const uint8_t m_Code;
	};
	
}
