#include "DirectX11Shader.h"
#include "DirectX11Debug.h"
#include "DirectX11Context.h"

#include "PawnUtils/utils/codetools/Macros.h"
#include "PawnUtils/utils/logger/Logger.h"

#include <d3dcompiler.h>

#ifdef PAWN_DIRECTX11

namespace pawn {
	
	bool DirectX11Shader::InitVertexShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		D3DReadFileToBlob(fileName.c_str(), &m_VertexShaderInfo);
		DirectX11Call(directX11Context->GetDevice()->CreateVertexShader(
			m_VertexShaderInfo->GetBufferPointer(),
			m_VertexShaderInfo->GetBufferSize(),
			nullptr, 
			&m_VertexShader
		))
		CONSOLE_INFO("Vertex shader created")
		return true;
	}

	bool DirectX11Shader::InitPixelShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		D3DReadFileToBlob(fileName.c_str(), &m_PixelShaderInfo);
		DirectX11Call(directX11Context->GetDevice()->CreatePixelShader(
			m_PixelShaderInfo->GetBufferPointer(),
			m_PixelShaderInfo->GetBufferSize(),
			nullptr,
			&m_PixelShader
		))
		CONSOLE_INFO("Pixel shader created")
		return true;
	}

	bool DirectX11Shader::Link() {
		return true;
	}

	void DirectX11Shader::Bind(std::shared_ptr<GraphicsContext>& context) {
		DirectX11Context* directX11Context = context->As<DirectX11Context>();
		directX11Context->GetDeviceContext()->VSSetShader(m_VertexShader.Get(), nullptr, 0);
		directX11Context->GetDeviceContext()->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	}

	void DirectX11Shader::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(index)
		Bind(context);
	}
	
}

#endif
