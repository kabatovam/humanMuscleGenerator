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
