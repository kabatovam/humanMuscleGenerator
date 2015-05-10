#pragma once
#include "tinyxml.h"
#include "tinyxml2.h"
#include "tinystr.h"
#include <vector>
#include "Element.h"


class XMLFileManipulator
{
public:
	XMLFileManipulator(std::vector<Element*> &infVec);
	~XMLFileManipulator();
	void readInfluencers(tinyxml2::XMLElement *bone, std::vector<Element*> &infVec);
	Element *getInfluencer(const char* boneName);
private:
	std::vector<Element*> elm;
	
	
	
	
};

