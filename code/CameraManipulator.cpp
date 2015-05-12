#include "CameraManipulator.h"


CameraManipulator::CameraManipulator()
{

	width = 640.0;
	height = 480.0;
	setupCamera();
	yaw = 0.0;
	pitch = 0.0;
	xRot = 0;
	yRot = 0;
	sensitivity = 0.01f;
	zoom = 10.0;
}


CameraManipulator::~CameraManipulator()
{
}

void CameraManipulator::setupCamera(){

	cameraPosition = glm::vec3(0.0, 0.0, zoom);
	cameraTarget = glm::vec3(0.0f, 0.0f, 1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


	//view
	/*view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));*/
	view = glm::lookAt(cameraPosition,
		cameraTarget,
		cameraUp);
	// Projection 
	setupPerspective(20.0f, width, height, 0.01f, 100.0f);
	model = glm::mat4(1);
	//model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
	GLfloat angle = 20.0f;
	//model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
}

void CameraManipulator::bindCamera(GLuint *shaderProgram){
	
	

	GLint modelLoc = glGetUniformLocation(*shaderProgram, "model");
	GLint viewLoc = glGetUniformLocation(*shaderProgram, "view");
	GLint projLoc = glGetUniformLocation(*shaderProgram, "projection");
	
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(perspectiveMat));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void CameraManipulator::changeCameraRotation(GLfloat angle, bool xaxis, bool yaxis){
	angle *= sensitivity;

	if (angle < 0){
		angle = abs(angle);
	}
	if (angle > 360){
		angle = abs(angle - 360);
	}
	if (xaxis && xRot != angle){
		model = glm::rotate(model, xRot, glm::vec3(1.0f, 0.0f, 0.0f));
		xRot = angle;
	}
	if (yaxis && yRot != angle){
		model = glm::rotate(model, yRot, glm::vec3(0.0f, 1.0f, 0.0f));
		yRot = angle;
	}
	/*
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));*/
}

void CameraManipulator::changeCameraMovement(std::string direction){
	if (direction == "ZOOM_IN"){
		zoom += 1.0;
	}
	if (direction == "ZOOM_OUT"){
		zoom -= 1.0;
	}
	cameraPosition = glm::vec3(0.0, 0.0, zoom);
	std::cout << "Zoom = " << zoom << std::endl;
	view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}

void CameraManipulator::setupPerspective(float fov, float width, float height, float zNear, float zFar){
	perspectiveMat = glm::perspective(fov, width/height, zNear, zFar);
}



