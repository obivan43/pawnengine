#pragma once

#include "PawnGraphics/graphics/GraphicsBuffer.h"

#include "PawnSystem/system/windows/WindowsAPI.h"

#ifdef PAWN_DIRECTX11

#include <d3d11.h>

namespace pawn {

	class DirectX11BufferBase : public GraphicsBuffer {

	public:
		DirectX11BufferBase(GraphicsBufferEnum type);
		DirectX11BufferBase(const DirectX11BufferBase& other) = default;
		DirectX11BufferBase(DirectX11BufferBase&& other) noexcept = default;

		DirectX11BufferBase& operator=(const DirectX11BufferBase& other) = default;
		DirectX11BufferBase& operator=(DirectX11BufferBase&& other) noexcept = default;
		
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

		void* GetBuffer() override { return m_Buffer.Get(); }
		uint32_t GetBufferSize() const override { return m_BufferSize; }
		uint32_t GetStride() const override { return m_Stride; }
	
	private:
		static D3D11_BIND_FLAG BufferTypeToDirectXBufferType(GraphicsBufferEnum type);
		static const char* BufferTypeMessage(GraphicsBufferEnum usageType);
		static D3D11_USAGE BufferUsageTypeToDirectXBufferUsageType(GraphicsBufferUsageTypeEnum usageType);
	
	protected:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
		uint32_t m_BufferSize;
		uint32_t m_Stride;
		GraphicsBufferUsageTypeEnum m_UsageType;
	};

}

#endif

