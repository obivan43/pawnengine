#include "pch.h"
#include "Renderer.h"
#include "Components.h"

namespace pawn {


	std::shared_ptr<GraphicsBuffer> Renderer::m_Transformation(nullptr);
	std::shared_ptr<GraphicsBuffer> Renderer::m_ViewProjection(nullptr);

	std::shared_ptr<GraphicsContext> Renderer::m_Context(nullptr);
	std::shared_ptr<GraphicsAPI> Renderer::m_GraphicsAPI(nullptr);
	std::shared_ptr<GraphicsShader> Renderer::m_Shader(nullptr);
	std::shared_ptr<GraphicsRenderer> Renderer::m_GraphicsRenderer(nullptr);

	void Renderer::SetShader(std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsShader>& shader) {
		m_Shader = shader; 
		m_Shader->Bind(context);
	}

	void Renderer::Init(const std::shared_ptr<GraphicsContext>& context, const std::shared_ptr<GraphicsAPI>& api) {
		m_Context = context;
		m_GraphicsAPI = api;

		m_Transformation = GraphicsBuffer::Create(GraphicsBufferEnum::ConstantBuffer);
		m_ViewProjection = GraphicsBuffer::Create(GraphicsBufferEnum::ConstantBuffer);
		m_GraphicsRenderer = GraphicsRenderer::Create(m_Context);

		m_Transformation->Init(m_Context, nullptr, 1, sizeof(glm::mat4), GraphicsBufferUsageTypeEnum::DynamicBuffer);
		m_Transformation->InitLocation(m_Context, m_Shader, "Transformation", 0);

		m_ViewProjection->Init(m_Context, nullptr, 1, sizeof(ViewProjection), GraphicsBufferUsageTypeEnum::DynamicBuffer);
		m_ViewProjection->InitLocation(m_Context, m_Shader, "ViewProjection", 1);
	}

	void Renderer::BeginScene(Camera& camera, glm::mat4& view) {
		ViewProjection viewProjection;

		viewProjection.projection = camera.GetProjection();
		viewProjection.view = view;

		m_ViewProjection->Update(m_Context, &viewProjection, 1, sizeof(ViewProjection));
		m_ViewProjection->Bind(m_Context);
	}

	void Renderer::Submit(Entity& entity) {
		TransformationComponent& transformationComponent = entity.GetComponent<TransformationComponent>();
		m_Transformation->Update(m_Context, &transformationComponent.m_Transformation, 1, sizeof(glm::mat4));
		m_Transformation->Bind(m_Context);

		MeshComponent& meshComponent = entity.GetComponent<MeshComponent>();
		meshComponent.m_Mesh->Bind(m_Context);
		m_GraphicsRenderer->DrawIndexed(meshComponent.m_Mesh->GetIndexBuffer());
	}

	void Renderer::EndScene() {}

}
