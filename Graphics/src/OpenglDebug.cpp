#include "pch.h"
#include "Opengl.h"
#include "OpenglDebug.h"

#if defined(DEBUG) | defined(_DEBUG)
#ifdef PAWN_OPENGL

#include <string>

void OpenglCallDebug(const char* file, unsigned int line, const char* expression) {
	GLenum errorCode = GL_NO_ERROR;
	std::string errorMessage = "Undefined error";

	while ((errorCode = glGetError()) != GL_NO_ERROR) {
		switch (errorCode) {
		case GL_INVALID_ENUM: {
			errorMessage = "Invalid enum";
			break;
		}
		case GL_INVALID_VALUE: {
			errorMessage = "Invalid value";
			break;
		}
		case GL_INVALID_OPERATION: {
			errorMessage = "Invalid operation";
			break;
		}
		case GL_STACK_OVERFLOW: {
			errorMessage = "Stack overflow";
			break;
		}
		case GL_STACK_UNDERFLOW: {
			errorMessage = "Stack underflow";
			break;
		}
		case GL_OUT_OF_MEMORY: {
			errorMessage = "Out of memory";
			break;
		}
		case GL_INVALID_FRAMEBUFFER_OPERATION: {
			errorMessage = "Invalid framebuffer operation";
			break;
		}
		case GL_CONTEXT_LOST: {
			errorMessage = "Context lost";
			break;
		}
		case GL_TABLE_TOO_LARGE: {
			errorMessage = "Table too large";
			break;
		}
		}

		spdlog::get("console")->error("Opengl error: {}, {}, {}, {}", errorMessage, file, line, expression);
		__debugbreak();
	}
}

#endif
#endif