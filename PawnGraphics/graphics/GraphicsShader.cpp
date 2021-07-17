#include "GraphicsShader.h"
#include "GraphicsContext.h"
#include "directx/DirectX11Shader.h"

#include "PawnUtils/utils/codetools/Macros.h"

namespace pawn
{
	bool GraphicsShader::InitVertexShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName) {
		UNUSED(context)
		UNUSED(fileName)
		return false;
	}

	bool GraphicsShader::InitPixelShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName) {
		UNUSED(context)
		UNUSED(fileName)
		return false;
	}

	void GraphicsShader::Bind(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
	}

	void GraphicsShader::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(context)
		UNUSED(index)
	}

	std::shared_ptr<GraphicsShader> GraphicsShader::Create() {
#ifdef PAWN_DIRECTX11
		return std::shared_ptr<GraphicsShader>(new DirectX11Shader());
#else
		return std::shared_ptr<GraphicsShader>(new GraphicsShader());
#endif
	}
}
