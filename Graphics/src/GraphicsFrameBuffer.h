#pragma once

#include "GraphicsBindableResource.h"

namespace pawn {

	class GraphicsFrameBuffer : public GraphicsBindableResource {

		public:
			GraphicsFrameBuffer() = default;
			GraphicsFrameBuffer(const GraphicsFrameBuffer& other) = default;
			GraphicsFrameBuffer(GraphicsFrameBuffer && other) noexcept = default;

			GraphicsFrameBuffer& operator=(const GraphicsFrameBuffer & other) = default;
			GraphicsFrameBuffer& operator=(GraphicsFrameBuffer && other) noexcept = default;

			virtual ~GraphicsFrameBuffer() = default;

			virtual void Init(std::shared_ptr<GraphicsContext>& context, int32_t width, int32_t height);

			void Bind(std::shared_ptr<GraphicsContext>&context) override;
			void Bind(std::shared_ptr<GraphicsContext>&context, uint32_t index) override;

			virtual void Unbind(std::shared_ptr<GraphicsContext>& context);

			static std::shared_ptr<GraphicsFrameBuffer> Create();
	};

}
