#pragma once

#include "Penelope/Renderer/IndexBuffer.hpp"

namespace Penelope {
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, size_t count);
		~OpenGLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		size_t GetCount() const { return m_Count; }

	private:
		uint32_t m_RendererID;
		size_t m_Count;

	};
}