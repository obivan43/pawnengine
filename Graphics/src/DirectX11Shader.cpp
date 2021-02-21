#include "pch.h"
#include "DirectX11Shader.h"
#include "DirectX11Debug.h"
#include "DirectX11Context.h"

namespace pawn {
	
	void DirectX11VertexShader::Init(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		D3DReadFileToBlob(fileName.c_str(), &m_Blob);
		DirectX11Call(directX11Context->GetDevice()->CreateVertexShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_Shader))
	}

	void DirectX11VertexShader::Bind(std::shared_ptr<GraphicsContext>& context) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		directX11Context->GetDeviceContext()->VSSetShader(m_Shader.Get(), nullptr, 0);
	}

	void DirectX11PixelShader::Init(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		D3DReadFileToBlob(fileName.c_str(), &m_Blob);
		DirectX11Call(directX11Context->GetDevice()->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_Shader))
	}

	void DirectX11PixelShader::Bind(std::shared_ptr<GraphicsContext>& context) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		directX11Context->GetDeviceContext()->PSSetShader(m_Shader.Get(), nullptr, 0);
	}
	
}

