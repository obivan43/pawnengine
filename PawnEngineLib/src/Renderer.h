#pragma once

#include "Entity.h"
#include "Components.h"

namespace pawn {

	struct ViewProjection {
		glm::mat4 projection;
		glm::mat4 view;
	};

	class Renderer {

		public:

			static void Init(const std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsAPI>& api, uint32_t width, uint32_t height);
			static void BeginScene(Camera& camera, glm::mat4& view);
			static void EndScene();

			static void DrawMesh(TransformationComponent& transformationComponent, MeshComponent& meshComponent);

			static void SetShader(std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsShader>& shader);

		private:
			static std::shared_ptr<GraphicsBuffer> m_Transformation;
			static std::shared_ptr<GraphicsBuffer> m_ViewProjection;

			static std::shared_ptr<GraphicsContext> m_Context;
			static std::shared_ptr<GraphicsAPI> m_GraphicsAPI;
			static std::shared_ptr<GraphicsShader> m_Shader;
			static std::shared_ptr<GraphicsRenderer> m_GraphicsRenderer;
			static std::shared_ptr<GraphicsFrameBuffer> m_FrameBuffer;
	};

}
