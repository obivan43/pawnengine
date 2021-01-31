#pragma once

#include <string>

#include "GraphicsContext.h"

namespace pawn {
	
	class Window {
		
		public:

			Window() = default;

			virtual void Update() = 0;

			virtual uint32_t GetWidth() const = 0;
			virtual uint32_t GetHeight() const = 0;
			virtual void* GetNativeHandle() const = 0;
			virtual bool IsClosed() const = 0;
			virtual std::shared_ptr<pawn::GraphicsContext>& GetGraphicsContext() = 0;
	};

}

