#include "Shader.h"
#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <string>

std::string getSource(const std::string& filePath)
{
	std::ifstream file(filePath);
	std::string source;
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
			source.append(line + "\n");
		return source;
	}
	else
		std::cout << "Failed to read from " << filePath << "\n";
}

unsigned int compileShader(unsigned int type, const std::string& source)
{
	GLCALL(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCALL(glShaderSource(id, 1, &src, nullptr));
	GLCALL(glCompileShader(id));

	//Error Handling
	int result;
	GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = new char[length];
		GLCALL(glGetShaderInfoLog(id, length, &length, message));
		std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader failed to compile:\n" << message << "\n";
		delete[] message;
		GLCALL(glDeleteShader(id));
		return 0;
	}
	return id;
}

unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLCALL(unsigned int program = glCreateProgram());
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCALL(glAttachShader(program, vs));
	GLCALL(glAttachShader(program, fs));
	GLCALL(glLinkProgram(program));
	GLCALL(glValidateProgram(program));

	return program;
}

Shader::Shader() {}

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
{
	std::string vs = getSource(vertexShader);
	std::string fs = getSource(fragmentShader);

	m_renderID = createShader(vs, fs);
	bind();
}

void Shader::innit(const std::string& vertexShader, const std::string& fragmentShader)
{
	std::string vs = getSource(vertexShader);
	std::string fs = getSource(fragmentShader);

	m_renderID = createShader(vs, fs);
	bind();
}

Shader::~Shader()
{
	GLCALL(glDeleteProgram(m_renderID));
}

void Shader::bind() const
{
	GLCALL(glUseProgram(m_renderID));
}

void Shader::unbind() const
{
	GLCALL(glUseProgram(0));
}

void Shader::setUniform4f(const std::string& name, const Eigen::Vector4f& data)
{
	bind();
	GLCALL(glUniform4f(getUniformLocation(name.c_str()), data[0], data[1], data[2], data[3]));
}

int Shader::getUniformLocation(const std::string& name)
{
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
		return m_uniformLocationCache[name];

	GLCALL(int location = glGetUniformLocation(m_renderID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: " << name << " does not exist\n";
	m_uniformLocationCache[name] = location;
	return location;
}
