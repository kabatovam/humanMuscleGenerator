#pragma once
#include "ShaderManipulator.h"
#include "CameraManipulator.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "MeshManipulator.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <soil/SOIL.h>

class GLManipulator
{
public:
	GLManipulator();
	~GLManipulator();
	void initialize();
	void paint();
	void rotateCamera(GLfloat angle, bool xaxis, bool yaxis);
	void moveCamera(std::string direction);
	void stopAnimation();
protected:
	void loadMesh(const std::string path);
	void processNode(aiNode *node);
	void bindVAO();
	void setupModel(aiMesh *mesh);
	void setupShaders();
	void setupTexture();
private:
	const aiScene *scene;
	const GLchar* fragmentShaderSource = "#version 400 \n"
		"in vec2 out_texCoord;\n"
		"uniform sampler2D tex;\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"vec3 color_t = texture(tex,out_texCoord).rgb;\n"
		"color = vec4(color_t, 1.0f);\n"
		"}\n\0";
	const GLchar* vertexShaderSource = "#version 400 \n"
		"in vec3 position;\n"
		"in vec2 texCoord;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"out vec2 out_texCoord;\n"
		"void main()\n"
		"{\n"
		"gl_Position = projection *  view * model * vec4(position, 1.0f);\n"
		"out_texCoord = texCoord;\n"
		"}\0";
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	GLuint VBO, VAO, EBO;
	GLuint texCoordVBO;
	GLuint indices_size;
	MeshManipulator *m;
	GLuint positionPosition;
	GLuint texCoordPosition;
	CameraManipulator *cm;
	GLuint texture;
	GLuint dispMap;
	aiMatrix4x4 globalInverseTransform;
	bool animationStopped;
	//Assimp::Importer importer;

	
};

