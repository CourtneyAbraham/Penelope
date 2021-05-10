#pragma once

#include <string>

namespace Penelope {
	class Shader {
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		unsigned int m_ProgramID = 0;
	};
}