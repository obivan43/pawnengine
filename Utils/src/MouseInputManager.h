#pragma once

#include <optional>
#include <queue>

#include "Event.h"

namespace pawn {

	class MouseInputManager {
		
		public:
			MouseInputManager();
			MouseInputManager(const MouseInputManager& other) = default;
			MouseInputManager(MouseInputManager&& other) noexcept = default;

			MouseInputManager& operator=(const MouseInputManager& other) = default;
			MouseInputManager& operator=(MouseInputManager&& other) noexcept = default;

			std::optional<std::shared_ptr<Event>> ReadFromBuffer();
			bool IsBufferEmpty() const;
			void Flush();

			void OnMouseMove(int32_t x, int32_t y);
		
			void TrimBuffer();

			int32_t GetX() const { return m_X; }
			int32_t GetY() const { return m_Y; }
	
		private:
			int32_t m_X;
			int32_t m_Y;
;			std::queue<std::shared_ptr<Event>> m_Queue;

			uint32_t m_TrimBufferSize;
	};

}