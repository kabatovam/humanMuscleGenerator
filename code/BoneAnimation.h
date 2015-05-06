#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <vector>
class BoneAnimation
{
public:
	BoneAnimation();
	~BoneAnimation();

	void setAnimationKeys(aiNodeAnim *node);


	aiVector3D getScaling(GLuint index);
	aiQuaternion getRotation(GLuint index);
	aiVector3D getTranslation(GLuint index);

	double getScalingTime(GLuint index);
	double getRotationTime(GLuint index);
	double getTranslationTime(GLuint index);

	GLuint getNumScaling();
	GLuint getNumRotation();
	GLuint getNumTranslation();
private:
	GLuint numScaling;
	GLuint numTranslation;
	GLuint numRotation;

	std::vector<double> translationTime;
	std::vector<double> scalingTime;
	std::vector<double> rotationTime;

	std::vector<aiVector3D> translation;
	std::vector<aiVector3D> scaling;
	std::vector<aiQuaternion> rotation;

};

