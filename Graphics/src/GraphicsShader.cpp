#include "pch.h"
#include "GraphicsShader.h"

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

	bool GraphicsShader::Link() {
		return false;
	}

	void GraphicsShader::Bind(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
	}
}
