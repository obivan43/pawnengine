#pragma once

namespace pawn {
	
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
