#include "pnpch.hpp"

#include "Shader.hpp"

#include <Glad/glad.h>

namespace Penelope {

	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) {

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const char* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, nullptr);

		glCompileShader(vertexShader);

		int isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			int maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			PN_CORE_ERROR("{0}", infoLog.data());
			PN_CORE_ASSERT(false, "Vertex shader compilation failed!");
			return;
		}

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			int maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			PN_CORE_ERROR("{0}", infoLog.data());
			PN_CORE_ASSERT(false, "Fragment shader compilation failed!");
			return;
		}

		m_ProgramID = glCreateProgram();

		glAttachShader(m_ProgramID, vertexShader);
		glAttachShader(m_ProgramID, fragmentShader);

		glLinkProgram(m_ProgramID);

		int isLinked = 0;
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			int maxLength = 0;
			glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_ProgramID);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			PN_CORE_ERROR("{0}", infoLog.data());
			PN_CORE_ASSERT(false, "Shader program compilation failed!");

			return;
		}

		glDetachShader(m_ProgramID, vertexShader);
		glDetachShader(m_ProgramID, fragmentShader);
	}

	Shader::~Shader() {

	}

	void Shader::Bind() const {
		glUseProgram(m_ProgramID);
	}

	void Shader::Unbind() const {
		glUseProgram(0);
	}

}