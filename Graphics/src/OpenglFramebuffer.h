#pragma once

#include "GraphicsFrameBuffer.h"

namespace pawn {

	class OpenglFramebuffer : public GraphicsFrameBuffer {

		public:
			OpenglFramebuffer() = default;
			OpenglFramebuffer(const OpenglFramebuffer& other) = default;
			OpenglFramebuffer(OpenglFramebuffer&& other) noexcept = default;

			OpenglFramebuffer& operator=(const OpenglFramebuffer& other) = default;
			OpenglFramebuffer& operator=(OpenglFramebuffer&& other) noexcept = default;

			~OpenglFramebuffer() override;

			void Init(std::shared_ptr<GraphicsContext>&context, int32_t width, int32_t height) override;

			void Bind(std::shared_ptr<GraphicsContext>&context) override;
			void Bind(std::shared_ptr<GraphicsContext>&context, uint32_t index) override;

			void Unbind(std::shared_ptr<GraphicsContext>& context) override;

		private:
			uint32_t m_Width;
			uint32_t m_Height;
			uint32_t m_FrameBuffer;
			uint32_t m_ColorBuffer;
			uint32_t m_DepthBuffer;
	};

}
