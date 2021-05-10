#pragma once

#include "Penelope/Renderer/Shader.hpp"

namespace Penelope{
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);

		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

	private:
		uint32_t m_RendererID = 0;
	};
}

