#include "StbImageLoader.h"
#include "StbImage.h"

namespace pawn {

	namespace utils {

		unsigned char* StbImageLoader::Load(const char* file, int32_t* width, int32_t* height, int32_t* bitsPerPixel) {
			stbi_set_flip_vertically_on_load(1);
			return stbi_load(file, width, height, bitsPerPixel, 4);
		}

		void StbImageLoader::Free(unsigned char* data) {
			if (data) {
				stbi_image_free(data);
			}
		}

	}
	
}
