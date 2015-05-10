#include "BoneAnimation.h"
#include <iostream>

BoneAnimation::BoneAnimation()
{
}


BoneAnimation::~BoneAnimation()
{
}

void BoneAnimation::setAnimationKeys(aiNodeAnim *node){
	translationTime.resize(node->mNumPositionKeys);
	scalingTime.resize(node->mNumScalingKeys);
	rotationTime.resize(node->mNumRotationKeys);

	translation.resize(node->mNumPositionKeys);
	scaling.resize(node->mNumScalingKeys);
	rotation.resize(node->mNumRotationKeys);
	double tempT = 0;
	aiVector3D temp;
	aiQuaternion tempq;
	for (GLuint i = 0; i < node->mNumPositionKeys; i++){
		tempT = node->mPositionKeys[i].mTime;
		translationTime[i] = tempT;
		temp = node->mPositionKeys[i].mValue;
		translation[i] = temp;
	}

	for (GLuint i = 0; i < node->mNumScalingKeys; i++){
		scalingTime[i] = node->mScalingKeys[i].mTime;
		scaling[i] = node->mScalingKeys[i].mValue;
	}

	for (GLuint i = 0; i < node->mNumRotationKeys; i++){
		tempT = node->mRotationKeys[i].mTime;
		rotationTime[i] = tempT;
		tempq = node->mRotationKeys[i].mValue;
		rotation[i] = tempq;
	}

	numScaling = node->mNumScalingKeys;
	numTranslation = node->mNumPositionKeys;
	numRotation  = node->mNumRotationKeys;

	std::cout << "Number of rotations: " << node->mNumRotationKeys << std::endl;
	std::cout << "Number of translations: " << node->mNumPositionKeys << std::endl;
}

aiVector3D BoneAnimation::getScaling(GLuint index){
	return scaling[index];
}
aiQuaternion BoneAnimation::getRotation(GLuint index){
	return rotation[index];
}
aiVector3D BoneAnimation::getTranslation(GLuint index){
	return translation[index];
}

GLuint BoneAnimation::getNumScaling(){
	return numScaling;
}
GLuint BoneAnimation::getNumRotation(){
	return numRotation;
}
GLuint BoneAnimation::getNumTranslation(){
	return numTranslation;
}

double BoneAnimation::getScalingTime(GLuint index){
	return scalingTime[index];
}
double BoneAnimation::getRotationTime(GLuint index){
	return rotationTime[index];
}
double BoneAnimation::getTranslationTime(GLuint index){
	return translationTime[index];
}
double BoneAnimation::calculateAngle(aiMatrix4x4 parentFinal, aiMatrix4x4 childFinal, std::string axis){
	aiVector3D parentX = aiVector3D(parentFinal.a1, parentFinal.b1, parentFinal.c1);
	aiVector3D parentY = aiVector3D(parentFinal.a2, parentFinal.b2, parentFinal.c2);
	aiVector3D parentZ = aiVector3D(parentFinal.a3, parentFinal.b3, parentFinal.c3);

	aiVector3D childX = aiVector3D(childFinal.a1, childFinal.b1, childFinal.c1);
	aiVector3D childY = aiVector3D(childFinal.a2, childFinal.b2, childFinal.c2);
	aiVector3D childZ = aiVector3D(childFinal.a3, childFinal.b3, childFinal.c3);

	
	double angleX = calcAngle(parentX, childX);
	double angleY = calcAngle(parentY, childY);
	double angleZ = calcAngle(parentZ, childZ);
	std::cout << "X axis Angle is: " << angleX <<std::endl;
	std::cout << "Y axis Angle is: " << angleY << std::endl;
	std::cout << "Z axis Angle is: " << angleZ << std::endl;
	if (axis.compare("X") == 0)
		return angleX;
	if (axis.compare("Y") == 0)
		return angleY;
	if (axis.compare("Z") == 0)
		return angleZ;
	return 0;
}

double BoneAnimation::calcAngle(aiVector3D parent, aiVector3D child){
	double dot = parent.x * child.x + parent.y * child.y + parent.z * child.z;
	double sizeParent = sqrt(pow(parent.x, 2) + pow(parent.y, 2) + pow(parent.z, 2));
	double sizeChild = sqrt(pow(child.x, 2) + pow(child.y, 2) + pow(child.z, 2));
	double cosAngle = dot / (sizeParent * sizeChild);
	double angle = acos(cosAngle);
	angle *= (180.0 / 3.14159265); //change to degrees
	std::cout << "Angle is: " << angle << std::endl;
	return angle;
}

double BoneAnimation::calcInterpolation(double currentAngle, int minAngle, int maxAngle){
	std::cout << "I am interpolating right now. Angles are: " << currentAngle << " , " << minAngle << " , " << maxAngle;
	currentAngle = currentAngle / maxAngle;
	minAngle = minAngle / maxAngle;
	maxAngle = maxAngle / maxAngle;
	std::cout << " Interpolation is: " << ((1 - currentAngle)*minAngle + currentAngle*maxAngle) <<std::endl;
	return ((1 - currentAngle)*minAngle + currentAngle*maxAngle);
}