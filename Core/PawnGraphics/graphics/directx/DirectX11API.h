#pragma once

#include "PawnGraphics/graphics/GraphicsAPI.h"

#include <memory>

#ifdef PAWN_DIRECTX11

namespace pawn::graphics {

	class DirectX11Context;

	class DirectX11API : public GraphicsAPI {

		public:
			DirectX11API();
			DirectX11API(const DirectX11API& other) = default;
			DirectX11API(DirectX11API&& other) noexcept = default;

			DirectX11API& operator=(const DirectX11API& other) = default;
			DirectX11API& operator=(DirectX11API&& other) noexcept = default;

			~DirectX11API() = default;

			void SetContext(std::shared_ptr<GraphicsContext>& context) override final;

			void SetClearColor(float r, float g, float b) override;
			void Clear() override final;

		private:
			float m_clearColor[4];
			DirectX11Context* m_DirectX11Context;
	};
	
}

#endif
