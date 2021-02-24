#pragma once

#include "GraphicsShader.h"

#ifdef PAWN_OPENGL

namespace pawn {

	class OpenglShader : public GraphicsShader {

		public:
			OpenglShader();
			OpenglShader(const OpenglShader& other) = default;
			OpenglShader(OpenglShader&& other) noexcept = default;

			OpenglShader& operator=(const OpenglShader& other) = default;
			OpenglShader& operator=(OpenglShader&& other) noexcept = default;

			~OpenglShader() override;

			bool InitVertexShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName) override;
			bool InitPixelShader(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName) override;
			bool Link() override;
			void Bind(std::shared_ptr<GraphicsContext>& context) override;
			void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) override;

			uint32_t GetVertexShader() const { return m_VertexShader; }
			uint32_t GetPixelShader() const { return m_PixelShader; }
			void* GetShader() const override { return reinterpret_cast<void*>(m_Shader); }

		private:
			bool Init(std::shared_ptr<GraphicsContext>& context, const std::wstring& fileName, GLenum shaderType, uint32_t* shader);
			bool CheckErrors(GLuint checkType);
			void Clean();
	
		private:
			uint32_t m_VertexShader;
			uint32_t m_PixelShader;
			uint32_t m_Shader;
			std::string m_LogInformation;
	};

}

#endif
