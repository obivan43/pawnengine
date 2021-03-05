﻿#pragma once

#include <vector>

#include "GraphicsBindableResource.h"

namespace pawn {

	enum class GraphicsInputElementType {
		None,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4
	};

	class GraphicsInputElement {
		
		public:
			GraphicsInputElement(const std::string& name, GraphicsInputElementType type);
			GraphicsInputElement(const GraphicsInputElement& other) = default;
			GraphicsInputElement(GraphicsInputElement&& other) noexcept = default;

			GraphicsInputElement& operator=(const GraphicsInputElement& other) = default;
			GraphicsInputElement& operator=(GraphicsInputElement&& other) noexcept = default;

			~GraphicsInputElement() = default;

			uint32_t ElementCount() const;
		
			static uint32_t GraphicsInputElementTypeSize(GraphicsInputElementType type);

		public:
			std::string Name;
			GraphicsInputElementType Type;
			uint32_t Size;
			size_t Offset;
	};
	
	class GraphicsInputLayout : public GraphicsBindableResource {
		
		public:
			GraphicsInputLayout();
			GraphicsInputLayout(const GraphicsInputLayout& other) = default;
			GraphicsInputLayout(GraphicsInputLayout&& other) noexcept = default;

			GraphicsInputLayout& operator=(const GraphicsInputLayout& other) = default;
			GraphicsInputLayout& operator=(GraphicsInputLayout&& other) noexcept = default;

			virtual ~GraphicsInputLayout() = default;

			virtual void Init(std::shared_ptr<GraphicsContext>& context, const std::initializer_list<GraphicsInputElement>& elements, void* shaderData);

			void Bind(std::shared_ptr<GraphicsContext>& context) override;
			void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) override;

			const std::vector<GraphicsInputElement>& GetElements() const { return m_Elements; }
			uint32_t GetStride() const { return m_Stride; }

			std::vector<GraphicsInputElement>::iterator begin() { return m_Elements.begin(); }
			std::vector<GraphicsInputElement>::iterator end() { return m_Elements.end(); }
			std::vector<GraphicsInputElement>::const_iterator begin() const { return m_Elements.begin(); }
			std::vector<GraphicsInputElement>::const_iterator end() const { return m_Elements.end(); }

			void RecalculateStride();

			static std::shared_ptr<GraphicsInputLayout> Create();
	
		protected:
			std::vector<GraphicsInputElement> m_Elements;
			uint32_t m_Stride;
	};

}
