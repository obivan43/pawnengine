#pragma once

#include "GraphicsBuffer.h"

#ifdef PAWN_OPENGL

namespace pawn {

	class OpenglBufferBase : public GraphicsBuffer {

	public:
		OpenglBufferBase(GraphicsBufferEnum type);
		OpenglBufferBase(const OpenglBufferBase& other) = default;
		OpenglBufferBase(OpenglBufferBase&& other) noexcept = default;

		OpenglBufferBase& operator=(const OpenglBufferBase& other) = default;
		OpenglBufferBase& operator=(OpenglBufferBase&& other) noexcept = default;

		~OpenglBufferBase() override;

		void Update(
			std::shared_ptr<GraphicsContext>& context,
			void* data,
			uint32_t numVertices,
			uint32_t sizeofBufferDataType
		) override;

		void Init(
			std::shared_ptr<GraphicsContext>& context,
			void* data,
			uint32_t numVertices,
			uint32_t sizeofBufferDataType,
			GraphicsBufferUsageTypeEnum type
		) override;

		void Bind(std::shared_ptr<GraphicsContext>& context) override;
		void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) override;

		void* GetBuffer() override { return &m_Buffer; }
		uint32_t GetBufferSize() const override { return m_BufferSize; }
		uint32_t GetStride() const override { return m_Stride; }

	private:
		static uint32_t BufferTypeToOpenglBufferType(GraphicsBufferEnum type);
		static const char* BufferTypeMessage(GraphicsBufferEnum usageType);
		static uint32_t BufferUsageTypeToOpenglBufferUsageType(GraphicsBufferUsageTypeEnum usageType);
	
	protected:
		uint32_t m_Buffer;
		uint32_t m_BufferSize;
		uint32_t m_Stride;
		GraphicsBufferUsageTypeEnum m_UsageType;
	};

}

#endif
