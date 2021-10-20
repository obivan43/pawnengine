#pragma once

#include "PawnGraphics/graphics/GraphicsInputLayout.h"

#include "PawnSystem/system/windows/WindowsAPI.h"

#include <memory>

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn::graphics {

	class DirectX11InputLayout : public GraphicsInputLayout {

		public:
			DirectX11InputLayout() = default;
			DirectX11InputLayout(const DirectX11InputLayout & other) = default;
			DirectX11InputLayout(DirectX11InputLayout && other) noexcept = default;

			DirectX11InputLayout& operator=(const DirectX11InputLayout & other) = default;
			DirectX11InputLayout& operator=(DirectX11InputLayout && other) noexcept = default;

			void Init(std::shared_ptr<GraphicsContext>&context, const std::initializer_list<GraphicsInputElement>&elements, void* shaderData) override;
			void Bind(std::shared_ptr<GraphicsContext>&context) override;
			void Bind(std::shared_ptr<GraphicsContext>&context, uint32_t index) override;
			void Unbind(std::shared_ptr<GraphicsContext>& context) override;

			ID3D11InputLayout* GetInputLayout() const { return m_InputLayout.Get(); }

			static DXGI_FORMAT GraphicsInputElementTypeToDX11Type(GraphicsInputElementType type);

		private:
			Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
	};
	
}

#endif
