#include "pnpch.hpp"

#include "IndexBuffer.hpp"

#include "Penelope/Renderer/Renderer.hpp"
#include "Platforms/OpenGL/OpenGLIndexBuffer.hpp"

namespace Penelope {

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, size_t count) {
		switch (Renderer::GetAPI()) {
			case RenderAPI::None: {
				PN_CORE_ASSERT(false, "RenderAPI::None is not currently supported");
				return nullptr;
			}
			case RenderAPI::OpenGL: {
				return new OpenGLIndexBuffer(indices, count);
			}
			default: {
				PN_CORE_ASSERT(false, "Unknown Render API");
				return nullptr;
			}
		}
	}

}