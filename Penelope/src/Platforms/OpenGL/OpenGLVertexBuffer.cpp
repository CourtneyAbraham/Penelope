#include "pnpch.hpp"

#include "OpenGLVertexBuffer.hpp"
#include <Glad/glad.h>

namespace Penelope {

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, size_t size) {
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer() {
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}