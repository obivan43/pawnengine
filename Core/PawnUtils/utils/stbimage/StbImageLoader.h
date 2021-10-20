#pragma once

#include <cstdint>

namespace pawn::utils {

	class StbImageLoader {

		public:

			static unsigned char* Load(const char* file, int32_t* width, int32_t* height, int32_t* bitsPerPixel);
			static void Free(unsigned char* data);

	};

}
