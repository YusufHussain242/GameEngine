#pragma once
#include <string>
#include <unordered_map>
#include <Eigen/Dense>
class Shader
{
private:
	unsigned int m_renderID;
	std::unordered_map<std::string, int> m_uniformLocationCache;

	int getUniformLocation(const std::string& name);
public:
	Shader();
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	void innit(const std::string& vertexShader, const std::string& fragmentShader);
	~Shader();
	void bind() const;
	void unbind() const;
	void setUniform4f(const std::string& name, const Eigen::Vector4f& data);
};