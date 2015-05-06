#pragma once
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>



// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;



class ShaderManipulator
{
public:
	ShaderManipulator();
	~ShaderManipulator();
	void createShader(std::string path, GLuint *shaderProgram);

	const GLchar *readShaderFromFile(std::string path);
private:
	const GLchar* fragmentShaderSource = "#version 400 \n"
		"in vec2 out_texCoord;\n"
		"uniform sampler2D tex;\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"vec3 color_t = texture(tex,out_texCoord).rgb;\n"
		"color = vec4(color_t, 1.0f);\n"
		"}\n\0";
};

