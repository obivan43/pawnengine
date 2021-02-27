#pragma once

#include <string>

namespace pawn {

	class KeyboardInputManager;
	
	class Window : public Observable {
		
		public:

			Window() = default;

			virtual void Update() = 0;

			virtual uint32_t GetWidth() const = 0;
			virtual uint32_t GetHeight() const = 0;
			virtual void* GetNativeHandle() const = 0;
			virtual bool IsClosed() const = 0;

			KeyboardInputManager& GetKeyBoardInputManager() { return m_KeyboardInputManager; }

		protected:
			KeyboardInputManager m_KeyboardInputManager;
	};

}

