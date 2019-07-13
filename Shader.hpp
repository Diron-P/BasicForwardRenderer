#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Camera.h"

class Shader
{
public:
	// the program ID
	unsigned int ID;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	~Shader();
	// use/activate the shader
	void use();
	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string& name, const Oblivion::Math::Vector3& value) const;
	void setMat4(const std::string& name, Oblivion::Math::Matrix44& value) const;
};

