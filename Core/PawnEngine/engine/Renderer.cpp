#include "Renderer.h"

namespace pawn {

	namespace engine {

		void Renderer::SetShader(std::shared_ptr<graphics::GraphicsContext>& context, const std::shared_ptr<graphics::GraphicsShader>& shader) {
			m_Shader = shader;
			m_Shader->Bind(context);

			m_Transformation = graphics::GraphicsBuffer::Create(graphics::GraphicsBufferEnum::ConstantBuffer);
			m_ViewProjection = graphics::GraphicsBuffer::Create(graphics::GraphicsBufferEnum::ConstantBuffer);

			m_Transformation->Init(m_Context, nullptr, 1, sizeof(glm::mat4), graphics::GraphicsBufferUsageTypeEnum::DynamicBuffer);
			m_ViewProjection->Init(m_Context, nullptr, 1, sizeof(ViewProjection), graphics::GraphicsBufferUsageTypeEnum::DynamicBuffer);
		}

		void Renderer::Init(const std::shared_ptr<graphics::GraphicsContext>& context, const std::shared_ptr<graphics::GraphicsAPI>& api, uint32_t width, uint32_t height) {
			m_Context = context;
			m_GraphicsAPI = api;
			m_GraphicsRenderer = graphics::GraphicsRenderer::Create();
		}

		void Renderer::BeginScene(math::Camera& camera, glm::mat4& view) {
			ViewProjection viewProjection{};

			viewProjection.projection = camera.GetProjection();
			viewProjection.view = view;

			m_ViewProjection->Update(m_Context, &viewProjection, 1, sizeof(ViewProjection));
			m_ViewProjection->Bind(m_Context, 1);
		}

		void Renderer::DrawMesh(TransformationComponent& transformationComponent, MeshComponent& meshComponent) {
			glm::mat4 transformation = transformationComponent.GetTransformation();
			m_Transformation->Update(m_Context, &transformation, 1, sizeof(glm::mat4));
			m_Transformation->Bind(m_Context, 0);

			if (graphics::GraphicsMesh* mesh = meshComponent.Mesh.get()) {
				mesh->Bind(m_Context);
				m_GraphicsRenderer->DrawIndexed(m_Context, mesh->GetIndexBuffer());
			}
		}

		void Renderer::EndScene() {}

	}

}