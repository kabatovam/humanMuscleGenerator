#pragma once
#include <assimp/scene.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#include "AnimationManipulator.h"
#include "BoneAnimation.h"

class Bone
{
public:
	Bone();
	Bone(aiBone *bone);
	~Bone();
	std::string getName(){return boneName; }
	//std::string getParent(){ return parent; }
	std::string getChild(){ return child; }
	void setParentBone(Bone *bone){ parent = bone; }
	void setChildBode(Bone *bone){ next = bone; }
	void setBoneTransform(aiMatrix4x4 transform);
	Bone *next;
	Bone *parent;
	void rotateBone(float angle, aiVector3t<float> axis, aiMatrix4x4 globalInverseTransform);
	aiMatrix4x4 getGlobalTransform(){ return globalTransform; }
	glm::mat4x4 getFinalTransform();
	void setBindPose(aiMatrix4x4 globalInverseTransform);
	void setBoneID(GLuint id){ boneID = id; }
	GLuint getBoneID(){ return boneID; }
	void animateBone(AnimationManipulator *anim, double time, aiMatrix4x4 globalInverseTransform);
	void createAnimationInfo(aiNodeAnim *node);
protected:
	void setChildren(); 
	void writeMatrix(aiMatrix4x4 mat);
	aiQuaternion calcRotation(double AnimationTime, aiNodeAnim *anim);
	aiVector3D calcScaling(double AnimationTime, aiNodeAnim *anim);
	aiVector3D calcTranslation(double AnimationTime, aiNodeAnim *anim);
private:
	std::string child;
	aiMatrix4x4 offsetMatrix;
	std::string boneName;
	aiMatrix4x4 globalTransform;
	aiMatrix4x4 finalTransform;
	aiMatrix4x4 boneTransform;
	GLuint boneID;
	BoneAnimation *animation;
	
};

