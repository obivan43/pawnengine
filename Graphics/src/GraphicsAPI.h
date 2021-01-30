#pragma once

namespace pawn {

	enum GraphicsAPIEnum {
		None,
		DirectX11,
		OpenGL,
		Count
	};
	
	class GraphicsAPI {
		
		public:
			GraphicsAPI() = default;
			GraphicsAPI(const GraphicsAPI& other) = default;
			GraphicsAPI(GraphicsAPI && other) noexcept = default;
		
			GraphicsAPI& operator=(const GraphicsAPI & other) = default;
			GraphicsAPI& operator=(GraphicsAPI && other) noexcept = default;
		
			virtual ~GraphicsAPI() = default;

			virtual void Clear(float r, float g, float b, float a);
		
			static const GraphicsAPIEnum& GetGraphicsAPI() { return m_graphicsApi; }
	
		private:
			static GraphicsAPIEnum m_graphicsApi;
	};
	
}
