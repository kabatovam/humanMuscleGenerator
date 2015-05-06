#include "Bone.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>

Bone::Bone()
{
}

Bone::Bone(aiBone *bone){
	parent = NULL;
	boneName = (bone->mName.data);
	offsetMatrix =  bone->mOffsetMatrix;
	globalTransform = aiMatrix4x4(1,0,0,0,
								  0,1,0,0,
								  0,0,1,0,
								  0,0,0,1);
	std::cout << "Creating bone named: " << bone->mName.data << std::endl;
	next = NULL;
	animation = NULL;
	
}

Bone::~Bone()
{
}

void Bone::rotateBone(float angle, aiVector3t<float> axis, aiMatrix4x4 globalInverseTransform){
	float radAngle = (angle * 2* 3.14159) / 360;
	glm::vec3 radVec = radAngle * glm::vec3(axis.x, axis.y, axis.z);
	std::cout << "\n rad vec = " << radVec.x << ", " << radVec.y << "," << radVec.z << std::endl;
	glm::quat quaternion(radVec);
	glm::mat4x4 rotationM = glm::mat4x4(quaternion);
	std::cout << "Rotation mat: ";
	std::cout << rotationM[0][0] << "," << rotationM[0][1] << "," << rotationM[0][2] << "," << rotationM[0][3] << std::endl
		<< rotationM[1][0] << "," << rotationM[1][1] << "," << rotationM[1][2] << "," << rotationM[1][3] << std::endl
		<< rotationM[2][0] << "," << rotationM[2][1] << "," << rotationM[2][2] << "," << rotationM[2][3] << std::endl
		<< rotationM[3][0] << "," << rotationM[3][1] << "," << rotationM[3][2] << "," << rotationM[3][3] << std::endl;
	glm::vec3 translation(0, 0, 0);
	//aiVector3D translation(0, 0, 0);
	//aiMatrix4x4 translationM;
	glm::mat4x4 translationM =  glm::translate(glm::mat4(1),translation);
	//translationM.Translation(translation, translationM);
	std::cout << "Translation mat: ";
	std::cout << translationM[0][0] << "," << translationM[0][1] << "," << translationM[0][2] << "," << translationM[0][3] << std::endl
		<< translationM[1][0] << "," << translationM[1][1] << "," << translationM[1][2] << "," << translationM[1][3] << std::endl
		<< translationM[2][0] << "," << translationM[2][1] << "," << translationM[2][2] << "," << translationM[2][3] << std::endl
		<< translationM[3][0] << "," << translationM[3][1] << "," << translationM[3][2] << "," << translationM[3][3] << std::endl;
	//aiMatrix4x4 scalingM;
	//aiMatrix4x4::Scaling(aiVector3D(1, 1, 1), scalingM);
	aiMatrix4x4 nodeTransform; // = translationM * rotationM * scalingM;
	glm::mat4x4 nodeTransform2 = translationM * rotationM;
	std::cout << "Node transform mat: ";
	std::cout << nodeTransform2[0][0] << "," << nodeTransform2[0][1] << "," << nodeTransform2[0][2] << "," << nodeTransform2[0][3] << std::endl
		<< nodeTransform2[1][0] << "," << nodeTransform2[1][1] << "," << nodeTransform2[1][2] << "," << nodeTransform2[1][3] << std::endl
		<< nodeTransform2[2][0] << "," << nodeTransform2[2][1] << "," << nodeTransform2[2][2] << "," << nodeTransform2[2][3] << std::endl
		<< nodeTransform2[3][0] << "," << nodeTransform2[3][1] << "," << nodeTransform2[3][2] << "," << nodeTransform2[3][3] << std::endl;
	if (parent != NULL)
		globalTransform = parent->getGlobalTransform() * boneTransform * nodeTransform ;
	else
		globalTransform = boneTransform * nodeTransform ;

	finalTransform = globalInverseTransform * globalTransform * offsetMatrix;
	std::cout << "I was rotated. My global transform is: ";
	writeMatrix(globalTransform);
	
}

glm::mat4x4 Bone::getFinalTransform(){
	std::cout << "I am returning final matrix. Here it is!\n";
	writeMatrix(finalTransform);
	
	return glm::mat4x4(finalTransform.a1, finalTransform.a2, finalTransform.a3, finalTransform.a4,
		finalTransform.b1, finalTransform.b2, finalTransform.b3, finalTransform.b4,
		finalTransform.c1, finalTransform.c2, finalTransform.c3, finalTransform.c4,
		finalTransform.d1, finalTransform.d2, finalTransform.d3, finalTransform.d4);
	
}

void Bone::setBindPose(aiMatrix4x4 globalInverseTransform){
	aiMatrix4x4 nodeTransform = boneTransform;

	std::cout << "I am creating bind pose. My name is " << boneName << std::endl;
	
	if (parent != NULL){
		std::cout << "My parent's global transform is: ";
		writeMatrix(parent->getGlobalTransform());
		globalTransform = parent->getGlobalTransform() * nodeTransform;
		std::cout << "My global transform is: ";
		writeMatrix(globalTransform);
	}
		
	else{
		std::cout << "I don't have parents! I am the root bone!" << std::endl;
		globalTransform =  nodeTransform;
		std::cout << "My global transform matrix is: ";
		writeMatrix(globalTransform);
	}

	
	finalTransform = globalInverseTransform * globalTransform * offsetMatrix;
	//finalTransform = finalTransform;
	std::cout << "My final transform matrix is: ";
	writeMatrix(finalTransform);
}

/*
void Bone::setBindPose(aiMatrix4x4 globalInverseTransform){
aiMatrix4x4 nodeTransform = boneTransform;
std::cout << "I am creating bind pose. My name is " << boneName << std::endl;

if (parent != NULL){
std::cout << "My parent's global transform is: ";
writeMatrix(parent->getGlobalTransform());
globalTransform = parent->getGlobalTransform() * nodeTransform;
std::cout << "My global transform is: ";
writeMatrix(globalTransform);
}

else{
std::cout << "I don't have parents! I am the root bone!" << std::endl;
globalTransform =  nodeTransform;
std::cout << "My global transform matrix is: ";
writeMatrix(globalTransform);
}


finalTransform = globalInverseTransform * globalTransform * offsetMatrix;
//finalTransform = finalTransform;
std::cout << "My final transform matrix is: ";
writeMatrix(finalTransform);
}*/
void Bone::writeMatrix(aiMatrix4x4 mat){
	std::cout	<< mat.a1 << "," << mat.a2 << "," << mat.a3 << "," << mat.a4 << std::endl
				<< mat.b1 << "," << mat.b2 << "," << mat.b3 << "," << mat.b4 << std::endl
				<< mat.c1 << "," << mat.c2 << "," << mat.c3 << "," << mat.c4 << std::endl
				<< mat.d1 << "," << mat.d2 << "," << mat.d3 << "," << mat.d4 << std::endl;
}

void Bone::animateBone(AnimationManipulator *anim, double time, aiMatrix4x4 globalInverseTransform){
	//aiNodeAnim *node = anim->findNodeAnimation(boneName);
	aiMatrix4x4 nodeTransform = boneTransform;
	if (parent != NULL)
		std::cout << "Nastavujem kost. " << boneName << " Cas je " << time << ". Mojim rodicom je: " << parent->getName() << "\n";
	if (animation != NULL){
		std::cout << "Animujem kost. Cas je "<<time<<"\n";
		//scale matrix
		aiVector3D scaling = calcScaling(time, NULL);
		aiMatrix4x4 scalM;
		aiMatrix4x4::Scaling(scaling, scalM);
		//rotation matrix
		aiQuaternion rot;
		rot = calcRotation(time, NULL);
		aiMatrix4x4 rotM = aiMatrix4x4(rot.GetMatrix());
		//translation matrix
		aiVector3D trans = calcTranslation(time, NULL);
		aiMatrix4x4 transM;
		aiMatrix4x4::Translation(trans, transM);
		//get it together
		nodeTransform = transM * rotM ;// *scalM;
	}
	
	if (parent != NULL)
		globalTransform = parent->getGlobalTransform()  * nodeTransform;
	else
		globalTransform =  nodeTransform;

	finalTransform = globalInverseTransform * globalTransform * offsetMatrix;
	
}

aiQuaternion Bone::calcRotation(double animationTime, aiNodeAnim *anim){
	if (animation->getNumRotation() < 2){
		return aiQuaternion(1, 0, 0, 0); //w,x,y,z
	}
	GLuint index = 0;
	for (GLuint i = 0; i < animation->getNumRotation(); i++){
		if (animationTime < animation->getRotationTime(i)){
			index = i;
			break;
		}
	}
	if (!((index + 1) < animation->getNumRotation())){
		return aiQuaternion(1, 0, 0, 0);
	}
	double delta = animation->getRotationTime(index + 1) - animation->getRotationTime(index);
	double factor = (animation->getRotationTime(index) - animationTime) / delta;
	factor = abs(factor);
	std::cout << index << std::endl;
	std::cout << animation->getRotationTime(index) << std::endl;
	std::cout << factor <<std::endl;
	assert(factor >= 0.0f && factor <= 1.0f);
	aiQuaternion start = animation->getRotation(index);
	aiQuaternion end = animation->getRotation(index+1);
	aiQuaternion rotation;
	aiQuaternion::Interpolate(rotation,start,end,factor);
	return rotation;
}

aiVector3D Bone::calcScaling(double animationTime, aiNodeAnim *anim){
	if (animation->getNumScaling() < 2)
		return aiVector3D(1, 1, 1);
	GLuint index = 0;
	for (GLuint i = 0; i < animation->getNumScaling(); i++){
		if (animationTime < animation->getScalingTime(i)){
			index = i;
			break;
		}
	}
	if (!((index + 1) < animation->getNumScaling())){
		return aiVector3D(1, 1, 1);
	}
	double delta = animation->getScalingTime(index+1) - animation->getScalingTime(index);
	float factor = (float)(animation->getScalingTime(index) - animationTime) / delta;
	assert(factor >= 0.0f && factor <= 1.0f);
	aiVector3D start = animation->getScaling(index);
	aiVector3D end = animation->getScaling(index+1);
	return (start + factor * (end - start));
	return aiVector3D(1, 1, 1);
}

aiVector3D Bone::calcTranslation(double animationTime, aiNodeAnim *anim){
	if (animation->getNumTranslation() < 2)
		return aiVector3D(0,0,0);
	GLuint index = 0;
	for (GLuint i = 0; i < animation->getNumTranslation(); i++){
		if (animationTime < animation->getTranslationTime(i)){
			index = i;
			break;
		}
	}
	if (!((index + 1) < animation->getNumTranslation())){
		return aiVector3D(0, 0, 0);
	}
	double delta = animation->getTranslationTime(index +1) - animation->getTranslationTime(index);
	float factor = (float)(animation->getTranslationTime(index) - animationTime) / delta;
	factor = abs(factor);
	assert(factor >= 0.0f && factor <= 1.0f);
	aiVector3D start = animation->getTranslation(index);
	aiVector3D end = animation->getTranslation(index + 1);
	return (start + factor * (end - start));
}

void Bone::createAnimationInfo(aiNodeAnim *node){
	std::cout << "Mnau. I am here! Node's name is: " << node->mNodeName.data << std::endl;
	animation = new BoneAnimation();
	animation->setAnimationKeys(node);
}

void Bone::setBoneTransform(aiMatrix4x4 transform){
	std::cout << "Setujem boneTransform. Here is the input: \n";
	writeMatrix(transform);
	boneTransform = transform; 

	std::cout << "and the boneTransform matrix: \n";
	writeMatrix(boneTransform);
}