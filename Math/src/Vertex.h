#pragma once

namespace pawn {
	
	struct Vertex {
		struct {
			float x;
			float y;
		} position;
	};

	struct ColoredVertex {
		struct {
			float x;
			float y;
		} position;

		struct {
			float r;
			float g;
			float b;
		} color;
	};
	
}
