#pragma once

#include "GraphicsContext.h"

namespace pawn {
	
	class DirectX11Context : public GraphicsContext {
		
		public:
			DirectX11Context() = default;
			DirectX11Context(const DirectX11Context& other) = default;
			DirectX11Context(DirectX11Context&& other) noexcept = default;
			
			DirectX11Context& operator=(const DirectX11Context& other) = default;
			DirectX11Context& operator=(DirectX11Context&& other) noexcept = default;

			~DirectX11Context() override;
		
			virtual void Initialize() override final;
			virtual void SwapBuffers() override final;

	};
	
}
