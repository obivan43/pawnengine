#include "pch.h"
#include "Renderer.h"

namespace pawn {

	void Renderer::SetShader(std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsShader>& shader) {
		m_Shader = shader;
		m_Shader->Bind(context);

		m_Transformation = GraphicsBuffer::Create(GraphicsBufferEnum::ConstantBuffer);
		m_ViewProjection = GraphicsBuffer::Create(GraphicsBufferEnum::ConstantBuffer);

		m_Transformation->Init(m_Context, nullptr, 1, sizeof(glm::mat4), GraphicsBufferUsageTypeEnum::DynamicBuffer);
		m_ViewProjection->Init(m_Context, nullptr, 1, sizeof(ViewProjection), GraphicsBufferUsageTypeEnum::DynamicBuffer);
	}

	void Renderer::Init(const std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsAPI>& api, uint32_t width, uint32_t height) {
		m_Context = context;
		m_GraphicsAPI = api;
		m_GraphicsRenderer = GraphicsRenderer::Create();
	}

	void Renderer::BeginScene(Camera& camera, glm::mat4& view) {
		ViewProjection viewProjection;

		viewProjection.projection = camera.GetProjection();
		viewProjection.view = view;

		m_ViewProjection->Update(m_Context, &viewProjection, 1, sizeof(ViewProjection));
		m_ViewProjection->Bind(m_Context, 1);
	}

	void Renderer::DrawMesh(TransformationComponent& transformationComponent, MeshComponent& meshComponent) {
		glm::mat4 transformation = transformationComponent.GetTransformation();
		m_Transformation->Update(m_Context, &transformation, 1, sizeof(glm::mat4));
		m_Transformation->Bind(m_Context, 0);

		meshComponent.Mesh->Bind(m_Context);
		m_GraphicsRenderer->DrawIndexed(m_Context, meshComponent.Mesh->GetIndexBuffer());
	}

	void Renderer::EndScene() {}

}
