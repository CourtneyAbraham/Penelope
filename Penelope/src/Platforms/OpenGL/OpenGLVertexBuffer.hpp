#pragma once

#include "Penelope/Renderer/VertexBuffer.hpp"

namespace Penelope {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, size_t size);

		~OpenGLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		const BufferLayout& GetLayout() const override { return m_Layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};
}