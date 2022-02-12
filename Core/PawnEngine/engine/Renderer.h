#pragma once

#include "GameEntity.h"

#include "components/MeshComponent.h"
#include "components/Texture2DComponent.h"
#include "components/TransformationComponent.h"
#include "components/DirectionalLightComponent.h"

#include "PawnGraphics/graphics/GraphicsAPI.h"
#include "PawnGraphics/graphics/GraphicsContext.h"
#include "PawnGraphics/graphics/GraphicsRenderer.h"
#include "PawnGraphics/graphics/GraphicsShader.h"

namespace pawn::engine {

	struct TransfromCB {
		glm::mat4 transform;
		glm::mat4 inserseTransposeTransform;
	};

	struct ViewProjectionCB {
		glm::mat4 projection;
		glm::mat4 view;
	};

	struct Texture2DCB {
		glm::vec4 color;
	};

	struct DirectionalLightCB {
		glm::vec3 ambient;
		float ambientIntensity;
		glm::vec3 diffuse;
		float diffuseIntensity;
		glm::vec3 specular;
		float specularIntensity;
		alignas(16) glm::vec3 direction;
	};

	struct LightCB {
		DirectionalLightCB directionalLight;
		alignas(16) glm::vec3 eyePosition;
	};

	struct alignas(16) ASCIICB {
		int asciiWidth;
		int asciiHeight;
	};

	class Renderer {

		public:
			Renderer() = default;
			Renderer(const Renderer& other) = delete;
			Renderer(Renderer&& other) noexcept = delete;

			Renderer& operator=(const Renderer& other) = delete;
			Renderer& operator=(Renderer&& other) noexcept = delete;

			void Init(
				const std::shared_ptr<graphics::GraphicsContext>& context,
				const std::shared_ptr<graphics::GraphicsAPI>& api,
				uint32_t width,
				uint32_t height
			);
			void SetShader(std::shared_ptr<graphics::GraphicsContext>& context, const std::shared_ptr<graphics::GraphicsShader>& shader);
			void SetASCIITexture(const std::shared_ptr<graphics::GraphicsTexture2D>& texture) { m_ASCIITexture = texture; }

			void BeginScene(math::Camera& camera, glm::mat4& view);
			void UpdateLights(DirectionalLightComponent& directionalLight, const glm::vec3& eyePosition);
			void EndScene();

			void DrawMesh(TransformationComponent& transformationComponent, MeshComponent& meshComponent);
			void DrawMesh(TransformationComponent& transformationComponent, MeshComponent& meshComponent, Texture2DComponent& textureComponent);

		private:
			std::shared_ptr<graphics::GraphicsBuffer> m_Transformation;
			std::shared_ptr<graphics::GraphicsBuffer> m_ViewProjection;
			std::shared_ptr<graphics::GraphicsBuffer> m_Texture2D;
			std::shared_ptr<graphics::GraphicsBuffer> m_Light;
			std::shared_ptr<graphics::GraphicsBuffer> m_ASCII;

			std::shared_ptr<graphics::GraphicsTexture2D> m_ASCIITexture;

			std::shared_ptr<graphics::GraphicsContext> m_Context;
			std::shared_ptr<graphics::GraphicsAPI> m_GraphicsAPI;
			std::shared_ptr<graphics::GraphicsShader> m_Shader;
			std::shared_ptr<graphics::GraphicsRenderer> m_GraphicsRenderer;

			uint32_t m_CacheWidth;
			uint32_t m_CacheHeight;
	};

}
