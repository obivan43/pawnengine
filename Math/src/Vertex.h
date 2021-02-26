#pragma once

namespace pawn {
	
	struct Vertex {
		struct {
			float x;
			float y;
			float z;
		} Position;

		struct {
			float u;
			float v;
		} TextureCoordinats;
	};

	struct ColoredVertex {
		struct {
			float x;
			float y;
		} Position;

		struct {
			float r;
			float g;
			float b;
		} Color;
	};
	
}
