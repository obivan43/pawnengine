#include "pch.h"
#include "Opengl.h"
#include "OpenglDebug.h"
#include "OpenglUniformManager.h"

namespace pawn {
	
	void OpenglUniformManager::SetUniform(std::shared_ptr<GraphicsShader>& shader, const char* name, int32_t value) {
		glUniform1i(GetUniformLocation(shader, name), value);
	}

	void OpenglUniformManager::SetUniform(std::shared_ptr<GraphicsShader>& shader, const char* name, uint32_t value) {
		glUniform1ui(GetUniformLocation(shader, name), value);
	}
	
	void OpenglUniformManager::SetUniform(std::shared_ptr<GraphicsShader>& shader, const char* name, float value) {
		glUniform1f(GetUniformLocation(shader, name), value);
	}

	int32_t OpenglUniformManager::GetUniformLocation(std::shared_ptr<GraphicsShader>& shader, const char* name) {
		const uint32_t shaderID = FROM_VOIDP(uint32_t, shader->GetShader());
		const int32_t location = glGetUniformLocation(shaderID, name);

		if (location == -1) {
			spdlog::get("console")->error("Uniform location undefined");
		}

		return location;
	}
	
}