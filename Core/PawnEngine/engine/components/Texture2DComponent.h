#pragma once

#include "PawnGraphics/graphics/GraphicsTexture2D.h"

#include "glm.hpp"

#include <memory>
#include <string>

namespace pawn {

	namespace engine {

		struct Texture2DComponent {

			Texture2DComponent() = default;
			Texture2DComponent(const std::shared_ptr<graphics::GraphicsTexture2D>& texture, const std::string& textureName = std::string());
			Texture2DComponent(const Texture2DComponent& other) = default;
			Texture2DComponent(Texture2DComponent&& other) noexcept = default;

			Texture2DComponent& operator=(const Texture2DComponent& other) = default;
			Texture2DComponent& operator=(Texture2DComponent&& other) noexcept = default;

			operator std::shared_ptr<graphics::GraphicsTexture2D>& () { return Texture; }
			operator const std::shared_ptr<graphics::GraphicsTexture2D>& () const { return Texture; }

			glm::vec3 Color{ 1.0 };
			std::shared_ptr<graphics::GraphicsTexture2D> Texture;
			std::string TextureName;
		};

	}

}
