#include "Texture2DComponent.h"

namespace pawn::engine {

	Texture2DComponent::Texture2DComponent(const std::shared_ptr<graphics::GraphicsTexture2D>& texture, const std::string& textureName)
		: Color(1.0), Texture(texture), TextureName(textureName) {};

}
