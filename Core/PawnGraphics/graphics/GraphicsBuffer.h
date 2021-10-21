#pragma once

#include "GraphicsBindableResource.h"

#include <memory>
#include <string>

namespace pawn::graphics {

	class GraphicsContext;
	class GraphicsShader;

	enum class GraphicsBufferEnum {
		None,
		VertexBuffer,
		IndexBuffer,
		ConstantBuffer
	};

	enum class GraphicsBufferUsageTypeEnum {
		None,
		StaticBuffer,
		DynamicBuffer
	};

	class GraphicsBuffer : public GraphicsBindableResource {

		public:
			GraphicsBuffer();
			virtual ~GraphicsBuffer() = default;

			GraphicsBuffer(const GraphicsBuffer& other) = default;
			GraphicsBuffer(GraphicsBuffer&& other) noexcept = default;

			GraphicsBuffer& operator=(const GraphicsBuffer& other) = default;
			GraphicsBuffer& operator=(GraphicsBuffer&& other) noexcept = default;

			virtual void InitLocation(
				std::shared_ptr<GraphicsContext>& context,
				std::shared_ptr<GraphicsShader>& shader,
				const std::string& name,
				uint32_t index = 0
			);

			virtual void Update(
				std::shared_ptr<GraphicsContext>& context,
				void* data,
				uint32_t numVertices,
				uint32_t stride
			);

			virtual void Init(
				std::shared_ptr<GraphicsContext>& context,
				void* data,
				uint32_t numVertices,
				uint32_t stride,
				GraphicsBufferUsageTypeEnum type
			);

			void Bind(std::shared_ptr<GraphicsContext>& context) override;
			void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) override;
			void Unbind(std::shared_ptr<GraphicsContext>& context) override;

			inline virtual void* GetBuffer() { return nullptr; };
			inline virtual uint32_t GetBufferSize() const { return 0; };
			inline virtual uint32_t GetStride() const { return 0; };

			inline const GraphicsBufferEnum& GetGraphicsBufferType() const noexcept { return m_GraphicsBufferType; }

			static std::shared_ptr<GraphicsBuffer> Create(GraphicsBufferEnum bufferType);

		protected:
			GraphicsBufferEnum m_GraphicsBufferType;
	};
}
