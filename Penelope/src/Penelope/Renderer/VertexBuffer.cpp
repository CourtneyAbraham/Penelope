#include "pnpch.hpp"

#include "VertexBuffer.hpp"

#include "Penelope/Renderer/Renderer.hpp"
#include "Platforms/OpenGL/OpenGLVertexBuffer.hpp"

namespace Penelope {

	VertexBuffer* VertexBuffer::Create(float* vertices, size_t size) {
		switch (Renderer::GetAPI()) {
			case RenderAPI::None: {
				PN_CORE_ASSERT(false, "RenderAPI::None is not currently supported");
				return nullptr;
			}
			case RenderAPI::OpenGL: {
				return new OpenGLVertexBuffer(vertices, size);
			}
			default: {
				PN_CORE_ASSERT(false, "Unknown Render API");
				return nullptr;
			}
		}
	}

}