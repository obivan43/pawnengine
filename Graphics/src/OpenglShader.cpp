#include "pch.h"
#include "Opengl.h"
#include "OpenglDebug.h"
#include "OpenglShader.h"

#include <fstream>

#ifdef PAWN_OPENGL

namespace pawn {

	OpenglShader::OpenglShader() : m_VertexShader(0), m_PixelShader(0){}

	OpenglShader::~OpenglShader() {
		OpenglCall(glDeleteProgram(m_Shader))
	}
	
	bool OpenglShader::InitVertexShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName) {
		return Init(context, fileName, GL_VERTEX_SHADER, &m_VertexShader);
	}
	
	bool OpenglShader::InitPixelShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName) {
		return Init(context, fileName, GL_FRAGMENT_SHADER, &m_PixelShader);
	}
	
	bool OpenglShader::Init(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName, GLenum shaderType, uint32_t* shader) {
		std::ifstream file(fileName.c_str());
		if (file.good()) {
			OpenglCall(*shader = glCreateShader(shaderType))
			std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			const char* cSource = source.c_str();

			OpenglCall(glShaderSource(*shader, 1, &cSource, nullptr))
			OpenglCall(glCompileShader(*shader))

			int logLength = 0;
			GLint result = GL_FALSE;

			OpenglCall(glGetShaderiv(*shader, GL_COMPILE_STATUS, &result))
			OpenglCall(glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength))

			if (result == GL_FALSE) {
				if (logLength > 0) {
					m_LogInformation.resize(logLength + 1);
					OpenglCall(glGetShaderInfoLog(*shader, logLength, NULL, &m_LogInformation[0]))
					spdlog::get("console")->error("Shader error: {}", m_LogInformation);
				}
				OpenglCall(glDeleteShader(*shader))
				return false;
			}

			return true;
		}

		return false;
	}

	bool OpenglShader::Link() {
		OpenglCall(m_Shader = glCreateProgram())

		if(m_VertexShader != 0) {
			OpenglCall(glAttachShader(m_Shader, m_VertexShader))
		}

		if (m_PixelShader != 0) {
			OpenglCall(glAttachShader(m_Shader, m_PixelShader))
		}

		OpenglCall(glLinkProgram(m_Shader))
		if (!CheckErrors(GL_LINK_STATUS)) {
			return false;
		}

		OpenglCall(glValidateProgram(m_Shader))
		if (!CheckErrors(GL_VALIDATE_STATUS)) {
			return false;
		}
		
		Clean();

		return true;
	}

	bool OpenglShader::CheckErrors(GLuint checkType) {
		int logLength = 0;
		GLint result = GL_FALSE;
		OpenglCall(glGetProgramiv(m_Shader, checkType, &result))
		OpenglCall(glGetProgramiv(m_Shader, GL_INFO_LOG_LENGTH, &logLength))

		if (result == GL_FALSE) {
			if (logLength > 0) {
				m_LogInformation.resize(logLength + 1);
				OpenglCall(glGetProgramInfoLog(m_Shader, logLength, NULL, &m_LogInformation[0]))
				spdlog::get("console")->error("Shader error: {}", m_LogInformation);
			}
			Clean();
			OpenglCall(glDeleteProgram(m_Shader))

			m_Shader = 0;

			return false;
		}

		return true;
	}

	void OpenglShader::Clean() {
		if (m_VertexShader != 0) {
			OpenglCall(glDetachShader(m_Shader, m_VertexShader))
			OpenglCall(glDeleteShader(m_VertexShader))
			m_VertexShader = 0;
		}

		if (m_PixelShader != 0) {
			OpenglCall(glDetachShader(m_Shader, m_PixelShader))
			OpenglCall(glDeleteShader(m_PixelShader))
			m_PixelShader = 0;
		}
	}
	
	void OpenglShader::Bind(std::shared_ptr<GraphicsContext>& context) {
		OpenglCall(glUseProgram(m_Shader))
	}

	void OpenglShader::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
		UNUSED(index)
		Bind(context);
	}
	
}

#endif
