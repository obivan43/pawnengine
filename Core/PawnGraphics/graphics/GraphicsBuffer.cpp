#include "GraphicsBuffer.h"
#include "GraphicsContext.h"
#include "GraphicsShader.h"
#include "directx/buffer/DirectX11VertexBuffer.h"
#include "directx/buffer/DirectX11ContantBuffer.h"
#include "directx/buffer/DirectX11IndexBuffer.h"

#include "PawnUtils/utils/codetools/Macros.h"

namespace pawn {

	namespace graphics {

		GraphicsBuffer::GraphicsBuffer()
			: m_GraphicsBufferType(GraphicsBufferEnum::None)
		{}

		void GraphicsBuffer::InitLocation(
			std::shared_ptr<GraphicsContext>& context,
			std::shared_ptr<GraphicsShader>& shader,
			const std::string& name,
			uint32_t index
		) {
			UNUSED(context)
			UNUSED(shader)
			UNUSED(name)
			UNUSED(index)
		}

		void GraphicsBuffer::Update(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t stride) {
			UNUSED(context)
			UNUSED(data)
			UNUSED(numVertices)
			UNUSED(stride)
		}

		void GraphicsBuffer::Init(std::shared_ptr<GraphicsContext>& context, void* data, uint32_t numVertices, uint32_t stride, GraphicsBufferUsageTypeEnum type) {
			UNUSED(context)
			UNUSED(data)
			UNUSED(numVertices)
			UNUSED(stride)
			UNUSED(type)
		}

		void GraphicsBuffer::Bind(std::shared_ptr<GraphicsContext>& context) { UNUSED(context) }

		void GraphicsBuffer::Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) {
			UNUSED(context)
			UNUSED(index)
		}

		void GraphicsBuffer::Unbind(std::shared_ptr<GraphicsContext>& context) { UNUSED(context) }

		std::shared_ptr<GraphicsBuffer> GraphicsBuffer::Create(GraphicsBufferEnum bufferType) {
#ifdef PAWN_DIRECTX11
			switch (bufferType) {
				case GraphicsBufferEnum::VertexBuffer:
					return std::shared_ptr<GraphicsBuffer>(new DirectX11VertexBuffer());
				case GraphicsBufferEnum::IndexBuffer:
					return std::shared_ptr<GraphicsBuffer>(new DirectX11IndexBuffer());
				case GraphicsBufferEnum::ConstantBuffer:
					return std::shared_ptr<GraphicsBuffer>(new DirectX11ContantBuffer());
			}

			return std::shared_ptr<GraphicsBuffer>(new GraphicsBuffer());
#else
			return std::shared_ptr<GraphicsBuffer>(new GraphicsBuffer());
#endif
		}

	}

}
