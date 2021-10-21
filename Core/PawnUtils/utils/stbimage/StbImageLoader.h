#pragma once

#include <cstdint>

namespace pawn::utils {

	class StbImageLoader {

		public:
			StbImageLoader() = delete;
			StbImageLoader(const StbImageLoader& other) = delete;
			StbImageLoader(StbImageLoader&& other) noexcept = delete;

			StbImageLoader& operator=(const StbImageLoader& other) = delete;
			StbImageLoader& operator=(StbImageLoader&& other) noexcept = delete;

			static unsigned char* Load(const char* file, int32_t* width, int32_t* height, int32_t* bitsPerPixel);
			static void Free(unsigned char* data);

	};

}
