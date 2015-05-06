#pragma once
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/scene.h>

class AnimationManipulator
{
public:
	AnimationManipulator(aiAnimation *anim);
	~AnimationManipulator();
	void updateTime(double time);
	double getAnimationTime(){ return currentTime; };
	aiNodeAnim *findNodeAnimation(std::string boneName);

private:
	double ticksPerSecond;
	double duration;
	double currentTime;
	aiAnimation *animation;

};

