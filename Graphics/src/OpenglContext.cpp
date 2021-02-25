#include "pch.h"
#include "Opengl.h"
#include "OpenglContext.h"
#include "OpenglDebug.h"
#include "Window.h"

#ifdef PAWN_OPENGL

namespace pawn {
	
	bool OpenglContext::Init(const pawn::Window& window) {
        static PIXELFORMATDESCRIPTOR pixelFormatDescriptor = {
		    sizeof(PIXELFORMATDESCRIPTOR),
		    1,
		    PFD_DRAW_TO_WINDOW |
		    PFD_SUPPORT_OPENGL |
		    PFD_DOUBLEBUFFER,
		    PFD_TYPE_RGBA,
		    24,
		    0, 0, 0, 0, 0, 0,
		    0,
		    0,
		    0,
		    0, 0, 0, 0,
		    16,
		    0,
		    0,
		    PFD_MAIN_PLANE,
		    0,
		    0, 0, 0
	    };

        m_DeviceContext;
        if (!(m_DeviceContext = GetDC(static_cast<HWND>(window.GetNativeHandle())))) {
			spdlog::get("console")->error("Cannot get a device context");
			return false;
        }

        if (!(m_PixelFormat = ChoosePixelFormat(m_DeviceContext, &pixelFormatDescriptor))) {
			spdlog::get("console")->error("Cannot choose pixel format");
			return false;
        }

        if (!SetPixelFormat(m_DeviceContext, m_PixelFormat, &pixelFormatDescriptor)) {
			spdlog::get("console")->error("Cannot set pixel format");
			return false;
        }

		DescribePixelFormat(m_DeviceContext, m_PixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDescriptor);

        if (!(m_RenderingContext = wglCreateContext(m_DeviceContext))) {
			spdlog::get("console")->error("Cannot create a valid opengl context");
			return false;
        }

		wglMakeCurrent(m_DeviceContext, m_RenderingContext);

		if(glewInit() != GLEW_OK) {
			spdlog::get("console")->error("GLEW not initialized");
			return false;
		}

		OpenglCall(glEnable(GL_DEPTH_TEST))
		OpenglCall(glDepthFunc(GL_ALWAYS))

		OpenglCall(glEnable(GL_BLEND))
		OpenglCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))

		OpenglCall(glEnable(GL_CULL_FACE))
		OpenglCall(glCullFace(GL_BACK))
		
		spdlog::get("console")->info("*********************************************");
		spdlog::get("console")->info("Vendor: {}", glGetString(GL_VENDOR));
		spdlog::get("console")->info("Videocard: {}", glGetString(GL_RENDERER));
		spdlog::get("console")->info("OpenGL version: {}", glGetString(GL_VERSION));
		spdlog::get("console")->info("*********************************************");
		spdlog::get("console")->info("OpenGL context initialized");
		
		return true;
	}

	void OpenglContext::SwapBuffers() {
		::SwapBuffers(m_DeviceContext);
	}


	OpenglContext::~OpenglContext() {
		wglDeleteContext(m_RenderingContext);
	}
}

#endif