#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CameraManipulator
{
public:
	CameraManipulator();
	~CameraManipulator();
	glm::mat4 getModelMatrix();
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	void changeCameraRotation(GLfloat angle, bool xaxis, bool yaxis);
	void changeCameraMovement(std::string direction);
	void bindCamera(GLuint *shaderProgram);
protected:
	void setupCamera();
	void setupPerspective(float fovy, float width, float height, float Znear, float zFar);
private:
	//modelviewprojection matrices
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 model;
	GLfloat width;
	GLfloat height;

	//camera vectors
	glm::vec3 cameraPosition;
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;
	glm::vec3 cameraRight;
	glm::vec3 worldUp;
	glm::vec3 cameraTarget;

	//angles
	GLfloat yaw;
	GLfloat pitch;

	//camera settings
	GLfloat speed;
	GLfloat sensitivity;
	GLfloat zoom;

	GLfloat xRot, yRot;

	glm::mat4 perspectiveMat;

};

