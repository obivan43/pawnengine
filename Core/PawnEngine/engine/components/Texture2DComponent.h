#pragma once

#include "glm.hpp"

#include "PawnGraphics/graphics/GraphicsTexture2D.h"

#include <memory>
#include <string>

namespace pawn::engine {

	struct Texture2DComponent {

		Texture2DComponent();
		Texture2DComponent(const std::shared_ptr<graphics::GraphicsTexture2D>& texture, const std::string& textureName = std::string());

		Texture2DComponent(const Texture2DComponent& other) = default;
		Texture2DComponent(Texture2DComponent&& other) noexcept = default;

		Texture2DComponent& operator=(const Texture2DComponent& other) = default;
		Texture2DComponent& operator=(Texture2DComponent&& other) noexcept = default;

		inline operator std::shared_ptr<graphics::GraphicsTexture2D>& () noexcept { return Texture; }
		inline operator const std::shared_ptr<graphics::GraphicsTexture2D>& () const noexcept { return Texture; }

		glm::vec3 Color;
		std::shared_ptr<graphics::GraphicsTexture2D> Texture;
		std::string TextureName;
	};

}
