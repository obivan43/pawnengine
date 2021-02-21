#include "pch.h"
#include "OpenglContext.h"
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
			return false;
        }

        if (!(m_PixelFormat = ChoosePixelFormat(m_DeviceContext, &pixelFormatDescriptor))) {
			return false;
        }

        if (!SetPixelFormat(m_DeviceContext, m_PixelFormat, &pixelFormatDescriptor)) {
			return false;
        }

		DescribePixelFormat(m_DeviceContext, m_PixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDescriptor);

        if (!(m_RenderingContext = wglCreateContext(m_DeviceContext))) {
			return false;
        }

		wglMakeCurrent(m_DeviceContext, m_RenderingContext);
		
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