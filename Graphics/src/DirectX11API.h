#pragma once

#include "GraphicsAPI.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn {
	
	class DirectX11API : public GraphicsAPI {
		
		public:
			DirectX11API() = default;
			DirectX11API(const DirectX11API& other) = default;
			DirectX11API(DirectX11API&& other) noexcept = default;
		
			DirectX11API& operator=(const DirectX11API& other) = default;
			DirectX11API& operator=(DirectX11API&& other) noexcept = default;
		
			virtual ~DirectX11API();
		
			virtual void Clear() override final;
			virtual void SetClearColor(float r, float g, float b, float a) override final;
		
	};
	
}

#endif
