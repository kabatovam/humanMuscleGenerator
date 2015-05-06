#include "AnimationManipulator.h"
#include <iostream>

AnimationManipulator::AnimationManipulator(aiAnimation *anim)
{
	animation = anim;
	if (anim->mTicksPerSecond == 0)
		ticksPerSecond = 25.0;
	else
		ticksPerSecond = anim->mTicksPerSecond;
	duration = anim->mDuration ;
	std::cout << "My animation name: " << anim->mTicksPerSecond <<std::endl;
	
}


AnimationManipulator::~AnimationManipulator()
{
}

aiNodeAnim *AnimationManipulator::findNodeAnimation(std::string boneName){ //asi bude lepsie posielat animaciu
	std::cout << "I have " << animation->mNumChannels << " chanels.\n";
	for (GLuint i = 0; i < animation->mNumChannels; i++){
		if (boneName.compare(animation->mChannels[i]->mNodeName.data) == 0)
			return animation->mChannels[i];
	}
	return NULL;
}

void AnimationManipulator::updateTime(double time){
	 currentTime += (time); 
	 if (currentTime > (duration)){
		 currentTime = 0;
	 }
}