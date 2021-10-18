#include "Renderer.h"

namespace pawn {

	namespace engine {

		void Renderer::SetShader(std::shared_ptr<graphics::GraphicsContext>& context, const std::shared_ptr<graphics::GraphicsShader>& shader) {
			m_Shader = shader;
			m_Shader->Bind(context);

			m_Transformation = graphics::GraphicsBuffer::Create(graphics::GraphicsBufferEnum::ConstantBuffer);
			m_ViewProjection = graphics::GraphicsBuffer::Create(graphics::GraphicsBufferEnum::ConstantBuffer);
			m_Texture2D = graphics::GraphicsBuffer::Create(graphics::GraphicsBufferEnum::ConstantBuffer);

			m_Transformation->Init(m_Context, nullptr, 1, sizeof(glm::mat4), graphics::GraphicsBufferUsageTypeEnum::DynamicBuffer);
			m_ViewProjection->Init(m_Context, nullptr, 1, sizeof(ViewProjectionCB), graphics::GraphicsBufferUsageTypeEnum::DynamicBuffer);
			m_Texture2D->Init(m_Context, nullptr, 1, sizeof(Texture2DCB), graphics::GraphicsBufferUsageTypeEnum::DynamicBuffer);
		}

		void Renderer::Init(const std::shared_ptr<graphics::GraphicsContext>& context, const std::shared_ptr<graphics::GraphicsAPI>& api, uint32_t width, uint32_t height) {
			m_Context = context;
			m_GraphicsAPI = api;
			m_GraphicsRenderer = graphics::GraphicsRenderer::Create();
		}

		void Renderer::BeginScene(math::Camera& camera, glm::mat4& view) {
			ViewProjectionCB viewProjection{};

			viewProjection.projection = camera.GetProjection();
			viewProjection.view = view;

			m_ViewProjection->Update(m_Context, &viewProjection, 1, sizeof(ViewProjectionCB));
			m_ViewProjection->Bind(m_Context, 1);
		}

		void Renderer::DrawMesh(TransformationComponent& transformationComponent, MeshComponent& meshComponent) {
			if (Mesh* mesh = meshComponent.MeshData.get()) {
				std::shared_ptr<graphics::GraphicsMesh> graphicsMesh = mesh->GetGraphicsMesh();
				graphicsMesh->Bind(m_Context);

				for (const MeshNodeData& meshNodeData : mesh->GetMeshNodeData()) {
					glm::mat4 transformation = transformationComponent.GetTransformation();
					transformation *= meshNodeData.Transformation;

					m_Transformation->Update(m_Context, &transformation, 1, sizeof(glm::mat4));
					m_Transformation->Bind(m_Context, 0);

					m_GraphicsRenderer->DrawIndexed(m_Context, meshNodeData.IndexCount, meshNodeData.IndexShift, meshNodeData.VertexShift);
				}
			}
		}

		void Renderer::DrawMesh(
			TransformationComponent& transformationComponent, 
			MeshComponent& meshComponent, 
			Texture2DComponent& textureComponent
		) {
			if (textureComponent.Texture.get()) {
				textureComponent.Texture->Bind(m_Context);
			}

			Texture2DCB texture2DCB{ glm::vec4(textureComponent.Color, 0.0) };
			m_Texture2D->Update(m_Context, &texture2DCB, 1, sizeof(Texture2DCB));
			m_Texture2D->Bind(m_Context, 2);

			DrawMesh(transformationComponent, meshComponent);

			if (textureComponent.Texture.get()) {
				textureComponent.Texture->Unbind(m_Context);
			}
		}

		void Renderer::EndScene() {}

	}

}
