#pragma once

#include "PawnUtils/utils/codetools/Rtti.h"

#include "PawnSystem/system/windows/WindowsAPI.h"

#include <memory>

namespace pawn {
	
	namespace graphics {

		class GraphicsContext : public Rtti {
			RTTI_DECLARATIONS(GraphicsContext, Rtti)

			public:
				GraphicsContext() = default;
				GraphicsContext(const GraphicsContext& other) = default;
				GraphicsContext(GraphicsContext&& other) noexcept = default;

				GraphicsContext& operator=(const GraphicsContext& other) = default;
				GraphicsContext& operator=(GraphicsContext&& other) noexcept = default;

				virtual ~GraphicsContext() = default;

				virtual bool Init(HWND handle, uint32_t width, uint32_t height);
				virtual void SwapBuffers();

				static std::shared_ptr<GraphicsContext> Create();
		};

	}

}
