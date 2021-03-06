#include "pnpch.hpp"

#include "Shader.hpp"

#include "Penelope/Renderer/Renderer.hpp"
#include "Platforms/OpenGL/OpenGLShader.hpp"

namespace Penelope {

	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource) {
		switch (Renderer::GetAPI()) {
			case RenderAPI::None: {
				PN_CORE_ASSERT(false, "RenderAPI::None is not currently supported");
				return nullptr;
			}
			case RenderAPI::OpenGL: {
				return new OpenGLShader(vertexSource, fragmentSource);
			}
			default: {
				PN_CORE_ASSERT(false, "Unknown Render API");
				return nullptr;
			}
		}
	}

}