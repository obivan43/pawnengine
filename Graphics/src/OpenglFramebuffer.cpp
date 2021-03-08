#include "pch.h"
#include "Opengl.h"
#include "OpenglDebug.h"
#include "OpenglFramebuffer.h"

namespace pawn {

	OpenglFramebuffer::~OpenglFramebuffer() {
		OpenglCall(glDeleteFramebuffers(1, &m_FrameBuffer))
	}

	void OpenglFramebuffer::Init(std::shared_ptr<GraphicsContext>& context, int32_t width, int32_t height) {
		m_Width = width;
		m_Height = height;

		OpenglCall(glGenTextures(1, &m_ColorBuffer))
		OpenglCall(glBindTexture(GL_TEXTURE_2D, m_ColorBuffer))
		OpenglCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR))
		OpenglCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR))
		OpenglCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER))
		OpenglCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER))
		OpenglCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL))
		OpenglCall(glBindTexture(GL_TEXTURE_2D, 0))

		OpenglCall(glGenTextures(1, &m_DepthBuffer))
		OpenglCall(glBindTexture(GL_TEXTURE_2D, m_DepthBuffer))
		OpenglCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST))
		OpenglCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST))
		OpenglCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE))
		OpenglCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE))
		OpenglCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL))
		OpenglCall(glBindTexture(GL_TEXTURE_2D, 0))

		OpenglCall(glGenFramebuffers(1, &m_FrameBuffer))
		OpenglCall(glBindFramebuffer(GL_FRAMEBUFFER, (GLuint)m_FrameBuffer))
		OpenglCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorBuffer, 0))
		OpenglCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthBuffer, 0))

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE) {
			spdlog::get("console")->error("Framebuffer is not complete");
		}

		OpenglCall(glBindFramebuffer(GL_FRAMEBUFFER, 0))

		spdlog::get("console")->info("Framebuffer created");
	}

	void OpenglFramebuffer::Bind(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
		OpenglCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_FrameBuffer))
	}

	void OpenglFramebuffer::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(index)
		Bind(context);
	}

	void OpenglFramebuffer::Unbind(std::shared_ptr<GraphicsContext>& context) {
		UNUSED(context)
		OpenglCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0))
		OpenglCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_FrameBuffer))

		OpenglCall(glReadBuffer(GL_COLOR_ATTACHMENT0))
		OpenglCall(glBlitFramebuffer(
			0, 0, m_Width, m_Height,
			0, 0, m_Width, m_Height,
			GL_COLOR_BUFFER_BIT,
			GL_NEAREST
		))
	}

}
