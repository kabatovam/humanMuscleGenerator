#include "ShaderManipulator.h"


ShaderManipulator::ShaderManipulator()
{
}


ShaderManipulator::~ShaderManipulator()
{
}

void ShaderManipulator::createShader(std::string path, GLuint *shaderProgram){
	std::string vertexCode;
	std::string fragmentCode;
	std::string tcsCode;
	std::string tesCode;

	try
	{
		// Open files
		std::ifstream vShaderFile("C:/martinka/libs/vertex.vs");
		std::ifstream fShaderFile("C:/martinka/libs/fragment.fs");
		std::ifstream tcsShaderFile("C:/martinka/libs/tesselation_shader.tcs");
		std::ifstream tesShaderFile("C:/martinka/libs/tesselation_shader.tes");
		std::stringstream vShaderStream, fShaderStream,tcsShaderStream,tesShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		tcsShaderStream << tcsShaderFile.rdbuf();
		tesShaderStream << tesShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		tcsShaderFile.close();
		tesShaderFile.close();
		// Convert stream into GLchar array
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		tcsCode = tcsShaderStream.str();
		tesCode = tesShaderStream.str();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *tcsShaderCode = tcsCode.c_str();
	const GLchar *tesShaderCode = tesCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	GLuint tcsShader = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(tcsShader, 1, &tcsShaderCode, NULL);
	glCompileShader(tcsShader);
	// Check for compile time errors
	glGetShaderiv(tcsShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(tcsShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint tesShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(tesShader, 1, &tesShaderCode, NULL);
	glCompileShader(tesShader);
	// Check for compile time errors
	glGetShaderiv(tesShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(tesShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::TESS::EVALUATION::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// Link shaders
	*shaderProgram = glCreateProgram();
	glAttachShader(*shaderProgram, vertexShader);
	glAttachShader(*shaderProgram, tcsShader);
	glAttachShader(*shaderProgram, tesShader);
	glAttachShader(*shaderProgram, fragmentShader);
	glLinkProgram(*shaderProgram);
	// Check for linking errors
	glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(tcsShader);
	glDeleteShader(tesShader);
}
const GLchar *ShaderManipulator::readShaderFromFile(std::string path){
	std::string vertexCode;
	std::string fragmentCode;
	try
	{
		// Open files
		std::ifstream shaderFile(path);
		std::stringstream vShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// Convert stream into GLchar array
		vertexCode = vShaderStream.str();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	
	return vertexCode.c_str();
}
