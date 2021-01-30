#pragma once

namespace pawn {

	class GraphicsContext;

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

			virtual void SetContext(std::shared_ptr<GraphicsContext>& context) { m_graphicsContext = context; }

			virtual void SetClearColor(float r, float g, float b);
			virtual void Clear();
		
			static const GraphicsAPIEnum& GetGraphicsAPI() { return m_graphicsApi; }
	
		private:
			std::shared_ptr<GraphicsContext> m_graphicsContext;
			static GraphicsAPIEnum m_graphicsApi;
	};
	
}
