#include "pch.h"
#include "StbImageLoader.h"

#include "StbImage.h"

namespace pawn {
	
	unsigned char* StbImageLoader::Load(const char* file, int32_t* width, int32_t* height, int32_t* bitsPerPixel) {
		spdlog::get("console")->debug("stb: texture file loading started {}", file);
		stbi_set_flip_vertically_on_load(1);
		return stbi_load(file, width, height, bitsPerPixel, 4);
	}

	void StbImageLoader::Free(unsigned char* data) {
		if(data) {
			spdlog::get("console")->debug("std: data released");
			stbi_image_free(data);
		}
	}
	
}
