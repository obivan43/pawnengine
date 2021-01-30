#pragma once

#include "GraphicsAPI.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn {

	class DirectX11Context;
	
	class DirectX11API : public GraphicsAPI {
		
		public:
			DirectX11API();
			DirectX11API(const DirectX11API& other) = default;
			DirectX11API(DirectX11API&& other) noexcept = default;
		
			DirectX11API& operator=(const DirectX11API& other) = default;
			DirectX11API& operator=(DirectX11API&& other) noexcept = default;
		
			~DirectX11API() = default;

			virtual void SetContext(std::shared_ptr<GraphicsContext>& context) override final;

			virtual void SetClearColor(float r, float g, float b) override;
			virtual void Clear() override final;
	
		private:
			float m_clearColor[4];
			DirectX11Context* m_DirectX11Context;
	};
	
}

#endif
