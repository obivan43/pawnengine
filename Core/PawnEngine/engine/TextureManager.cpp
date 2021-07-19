#include "TextureManager.h"

#include "PawnUtils/utils/logger/Logger.h"
#include "PawnUtils/utils/stbimage/StbImageLoader.h"

namespace pawn {

	namespace engine {


		bool TextureManager::HasTextureByName(const std::string& name) {
			return m_TexturesMap[name].get() != nullptr;
		}

		bool TextureManager::UploadTexture(const std::string& name, const std::shared_ptr<graphics::GraphicsTexture2D>& texture) {
			if (m_TexturesMap[name] != nullptr) {
				CONSOLE_WARN("TextureManager: texture with same name already exist")
				return false;
			}

			m_TexturesMap[name] = texture;

			return true;
		}

		bool TextureManager::UploadTextureFromFile(std::shared_ptr<graphics::GraphicsContext>& context, const std::string& path) {
			std::shared_ptr<graphics::GraphicsTexture2D> texture = graphics::GraphicsTexture2D::Create();

			std::string name = path.substr(path.find_last_of("/\\") + 1);

			if (m_TexturesMap[name] != nullptr) {
				CONSOLE_WARN("TextureManager: texture with same name already exist")
				return false;
			}

			int32_t width{ 0 }, height{ 0 }, bitsPerPixel{ 0 };
			unsigned char* data = utils::StbImageLoader::Load(path.c_str(), &width, &height, &bitsPerPixel);

			if (data == nullptr) {
				CONSOLE_ERROR("TextureManager: texture loading corrupted")
				return false;
			}

			texture->Init(
				context,
				data,
				width,
				height,
				bitsPerPixel, 
				{ graphics::GraphicsTextureWrap::CLAMP, graphics::GraphicsTextureFilter::LINEAR, graphics::GraphicsTextureFormat::RGBA }
			);

			utils::StbImageLoader::Free(data);
			m_TexturesMap[name] = texture;

			return true;
		}

		const std::shared_ptr<graphics::GraphicsTexture2D>& TextureManager::GetTextureByName(const std::string& name) {
			return m_TexturesMap[name];
		}


	}

}
