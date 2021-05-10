#pragma once

#include "Penelope/Renderer/VertexBuffer.hpp"

namespace Penelope {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, size_t size);

		~OpenGLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

	private:
		uint32_t m_RendererID;
	};
}