#pragma once

#include "GraphicsShader.h"

namespace pawn {
	
	class OpenglUniformManager {
		
		public:

			static void SetUniform(std::shared_ptr<GraphicsShader>& shader,const char* name, int32_t value);
			static void SetUniform(std::shared_ptr<GraphicsShader>& shader, const char* name, uint32_t value);
			static void SetUniform(std::shared_ptr<GraphicsShader>& shader, const char* name, float value);

		private:
			static int32_t GetUniformLocation(std::shared_ptr<GraphicsShader>& shader, const char* name);
		
	};
	
}
