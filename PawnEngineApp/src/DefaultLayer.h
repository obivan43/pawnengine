#pragma once

namespace pawn {
	
	class DefaultLayer : public Layer {
		
		public:
			DefaultLayer();
			DefaultLayer(const DefaultLayer& other) = delete;
			DefaultLayer(DefaultLayer&& other) noexcept = default;

			DefaultLayer& operator=(const DefaultLayer& other) = delete;
			DefaultLayer& operator=(DefaultLayer&& other) noexcept = delete;
		
			void OnInit() override;
			void OnUpdate(Clock& clock) override;
			void OnRelease() override;
	
		private:
			std::shared_ptr<GraphicsShader> m_Shader;

			std::wstring m_VertexShaderPath;
			std::wstring m_PixelShaderPath;

			MeshManager m_MeshManager;

			Scene m_Scene;
			Entity m_Entity;
			Entity m_Camera;
	};
	
}
