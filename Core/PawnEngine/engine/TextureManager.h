#pragma once

#include "PawnGraphics/graphics/GraphicsTexture2D.h"

#include <memory>
#include <unordered_map>
#include <string>

namespace pawn {

	namespace engine {

		class TextureManager {

			public:
				TextureManager() = default;
				TextureManager(const TextureManager& other) = delete;
				TextureManager(TextureManager&& other) noexcept = delete;

				TextureManager& operator=(const TextureManager& other) = delete;
				TextureManager& operator=(TextureManager&& other) noexcept = delete;

				bool HasTextureByName(const std::string& name);
				bool UploadTexture(const std::string& name, const std::shared_ptr<graphics::GraphicsTexture2D>& texture);

				bool UploadTextureFromFile(
					std::shared_ptr<graphics::GraphicsContext>& context, 
					const std::string& path
				);

				const std::shared_ptr<graphics::GraphicsTexture2D>& GetTextureByName(const std::string& name);

			private:
				std::unordered_map<std::string, std::shared_ptr<graphics::GraphicsTexture2D>> m_TexturesMap;
		};

	}

}
