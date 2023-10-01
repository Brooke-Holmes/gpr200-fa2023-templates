#include "..\ew\external\glad.h"
#include "shader.h"

namespace bh
{
	std::string bh::loadShaderSourceFromFile(const std::string& filePath)
	{
		std::ifstream fstream(filePath);
		if (!fstream.is_open())
		{
			printf("Failed to load file %s", filePath);
			return {};
		}
		std::stringstream buffer;
		buffer << fstream.rdbuf();
		return buffer.str();
	}


	unsigned int createShader(GLenum shaderType, const char* sourceCode) {
		//Create a new vertex shader object
		unsigned int shader = glCreateShader(shaderType);
		//Supply the shader object with source code
		glShaderSource(shader, 1, &sourceCode, NULL);
		//Compile the shader object
		glCompileShader(shader);
		int success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			//512 is an arbitrary length, but should be plenty of characters for our error message.
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			printf("Failed to compile shader: %s", infoLog);
		}
		return shader;
	};

	unsigned int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
		unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
		unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

		unsigned int shaderProgram = glCreateProgram();
		//Attach each stage
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		//Link all the stages together
		glLinkProgram(shaderProgram);
		int success;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			printf("Failed to link shader program: %s", infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return shaderProgram;
	};

	//Shader class
	Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		std::string vertexShaderSource = loadShaderSourceFromFile(vertexShader.c_str());
		std::string fragmentShaderSource = loadShaderSourceFromFile(fragmentShader.c_str());
		m_id = createShaderProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
	}

	void Shader::use()
	{
		glUseProgram(m_id);
	}

	void Shader::setInt(const std::string& name, int v) const
	{
		glUniform1i(glGetUniformLocation(m_id, name.c_str()), v);
	}
	void Shader::setFloat(const std::string& name, float v) const
	{
		glUniform1f(glGetUniformLocation(m_id, name.c_str()), v);
	}
};

// BY THE WAY i am still getting a linker error here but i think it's an issue with my lenovo rather than the code itself so idk how to test it, sorry if it still doesn't compile