#pragma once

#include "GraphicsBindableResource.h"

#include <memory>
#include <vector>
#include <string>

namespace pawn::graphics {

	class GraphicsContext;
	class GraphicsInputLayout;

	enum class GraphicsInputElementType {
		None,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4
	};

	class GraphicsInputElement {

		friend GraphicsInputLayout;

		public:
			GraphicsInputElement(const std::string& name, GraphicsInputElementType type);
			GraphicsInputElement(const GraphicsInputElement& other) = default;
			GraphicsInputElement(GraphicsInputElement&& other) noexcept = default;

			GraphicsInputElement& operator=(const GraphicsInputElement& other) = default;
			GraphicsInputElement& operator=(GraphicsInputElement&& other) noexcept = default;

			~GraphicsInputElement();

			uint32_t ElementCount() const;

			static uint32_t GraphicsInputElementTypeSize(GraphicsInputElementType type);

			std::string m_Name;
			GraphicsInputElementType m_Type;
			uint32_t m_Size;
			size_t m_Offset;
	};

	class GraphicsInputLayout : public GraphicsBindableResource {

		public:
			GraphicsInputLayout();
			GraphicsInputLayout(const GraphicsInputLayout& other) = default;
			GraphicsInputLayout(GraphicsInputLayout&& other) noexcept = default;

			GraphicsInputLayout& operator=(const GraphicsInputLayout& other) = default;
			GraphicsInputLayout& operator=(GraphicsInputLayout&& other) noexcept = default;

			virtual ~GraphicsInputLayout();

			virtual void Init(std::shared_ptr<GraphicsContext>& context, const std::initializer_list<GraphicsInputElement>& elements, void* shaderData);

			void Bind(std::shared_ptr<GraphicsContext>& context) override;
			void Bind(std::shared_ptr<GraphicsContext>& context, uint32_t index) override;
			void Unbind(std::shared_ptr<GraphicsContext>& context) override;

			uint32_t GetStride() const { return m_Stride; }

			void RecalculateStride();

			static std::shared_ptr<GraphicsInputLayout> Create();

		protected:
			std::vector<GraphicsInputElement> m_Elements;
			uint32_t m_Stride;
	};

}
