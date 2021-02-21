#pragma once

#include "GraphicsBindableResource.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>
#include <d3dcompiler.h>

namespace pawn {

	class DirectX11VertexShader : public GraphicsBindableResource {

		public:
			void Init(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName);
			void Bind(std::shared_ptr<GraphicsContext>& context) override;

			ID3D11VertexShader* GetShader() const { return m_Shader.Get(); }
			ID3DBlob* GetBlob() const { return m_Blob.Get(); }

		private:
			Microsoft::WRL::ComPtr<ID3D11VertexShader> m_Shader;
			Microsoft::WRL::ComPtr<ID3DBlob> m_Blob;
	};

	class DirectX11PixelShader : public GraphicsBindableResource {

		public:
			void Init(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName);
			void Bind(std::shared_ptr<GraphicsContext>& context) override;

			ID3D11PixelShader* GetShader() const { return m_Shader.Get(); }
			ID3DBlob* GetBlob() const { return m_Blob.Get(); }

		private:
			Microsoft::WRL::ComPtr<ID3D11PixelShader> m_Shader;
			Microsoft::WRL::ComPtr<ID3DBlob> m_Blob;
	};

}

#endif
