#pragma once

#include "GameEntity.h"
#include "components\TransformationComponent.h"
#include "components\TagComponent.h"
#include "components\CameraComponent.h"
#include "components\MeshComponent.h"

#include "PawnGraphics/src/GraphicsContext.h"
#include "PawnGraphics/src/GraphicsAPI.h"
#include "PawnGraphics/src/GraphicsShader.h"
#include "PawnGraphics/src/GraphicsRenderer.h"

namespace pawn {

	struct ViewProjection {
		glm::mat4 projection;
		glm::mat4 view;
	};

	class Renderer {

		public:
			Renderer() = default;
			void Init(const std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsAPI>& api, uint32_t width, uint32_t height);
			void SetShader(std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsShader>& shader);

			void BeginScene(Camera& camera, glm::mat4& view);
			void EndScene();

			void DrawMesh(TransformationComponent& transformationComponent, MeshComponent& meshComponent);

		private:
			std::shared_ptr<GraphicsBuffer> m_Transformation;
			std::shared_ptr<GraphicsBuffer> m_ViewProjection;

			std::shared_ptr<GraphicsContext> m_Context;
			std::shared_ptr<GraphicsAPI> m_GraphicsAPI;
			std::shared_ptr<GraphicsShader> m_Shader;
			std::shared_ptr<GraphicsRenderer> m_GraphicsRenderer;
	};

}
