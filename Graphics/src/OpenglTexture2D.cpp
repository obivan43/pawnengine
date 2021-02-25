#include "pch.h"
#include "Opengl.h"
#include "OpenglDebug.h"
#include "OpenglTexture2D.h"

#ifdef PAWN_OPENGL

namespace pawn {

	OpenglTexture2D::~OpenglTexture2D() {
		OpenglCall(glDeleteTextures(1, &m_Texture))
	}
	
	uint32_t OpenglTexture2D::TextureWrapToOpengl(GraphicsTextureWrap wrap) {
		switch (wrap) {
			case GraphicsTextureWrap::CLAMP: return GL_CLAMP;
			case GraphicsTextureWrap::CLAMP_TO_BORDER: return GL_CLAMP_TO_BORDER;
			case GraphicsTextureWrap::CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
			case GraphicsTextureWrap::REPEAT: return GL_REPEAT;
		}

		return 0;
	}
	
	void OpenglTexture2D::Bind(std::shared_ptr<GraphicsContext>& context) {
		OpenglCall(glActiveTexture(GL_TEXTURE0));
		OpenglCall(glBindTexture(GL_TEXTURE_2D, m_Texture));
	}

	void OpenglTexture2D::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		OpenglCall(glActiveTexture(GL_TEXTURE0 + index));
		OpenglCall(glBindTexture(GL_TEXTURE_2D, m_Texture));
	}

	void OpenglTexture2D::Init(
		std::shared_ptr<GraphicsContext>& context,
		const void* data,
		int32_t width,
		int32_t height,
		int32_t bitsPerPixel,
		const GraphicsTextureParams& params
	) {
		m_Width = width;
		m_Height = height;
		m_Params = params;
		m_BitsPerPixel = bitsPerPixel;

		if (m_Texture != 0) {
			OpenglCall(glDeleteTextures(1, &m_Texture))
			m_Texture = 0;
		}

		OpenglCall(glGenTextures(1, &m_Texture));
		OpenglCall(glBindTexture(GL_TEXTURE_2D, m_Texture));

		OpenglCall(
			glTexParameteri(GL_TEXTURE_2D,
				GL_TEXTURE_MIN_FILTER,
				params.m_FilterMode == GraphicsTextureFilter::LINEAR ? GL_LINEAR : GL_NEAREST
			)
		);

		OpenglCall(
			glTexParameteri(GL_TEXTURE_2D,
				GL_TEXTURE_MAG_FILTER,
				params.m_FilterMode == GraphicsTextureFilter::LINEAR ? GL_LINEAR : GL_NEAREST
			)
		);

		OpenglCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToOpengl(params.m_WrapMode)));
		OpenglCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToOpengl(params.m_WrapMode)));

		OpenglCall(glTexImage2D(
				GL_TEXTURE_2D,
				0,
				params.m_Format == GraphicsTextureFormat::RGB ? GL_RGB : GL_RGBA,
				width,
				height,
				0,
				params.m_Format == GraphicsTextureFormat::RGB ? GL_RGB : GL_RGBA,
				GL_UNSIGNED_BYTE,
				data
			)
		);
		OpenglCall(glBindTexture(GL_TEXTURE_2D, 0));

		spdlog::get("console")->info("Texture2D created");
	}

}

#endif
