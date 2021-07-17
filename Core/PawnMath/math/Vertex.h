#pragma once

namespace pawn {
	
	namespace math {

		struct Vertex {
			struct {
				float x;
				float y;
				float z;
			} Position;

			struct {
				float x;
				float y;
				float z;
			} Normal;

			struct {
				float u;
				float v;
			} TextureCoordinate;
		};

	}
	
}
