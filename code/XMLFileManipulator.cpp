#include "XMLFileManipulator.h"
#include <iostream>

//using namespace tinyxml2;

XMLFileManipulator::XMLFileManipulator(std::vector<Element*> &infVec)
{
	/*XMLDocument doc;
	XMLError result = doc.LoadFile("C:/martinka/libs/skeleton_data.xml");
	if (result != XML_SUCCESS) { printf("Error: %i\n", result); }
	XMLNode *root = doc.FirstChild();
	if (root == NULL){ std::cout << "ERROR reading file.\n"; }
	std::cout << "File reading succescfull\n";
	XMLElement *child;
	for (child = root->FirstChildElement("bone"); child != 0; child = child->NextSiblingElement("bone")){
		const char* text = child->Attribute("name");
		std::cout << text << std::endl;
		readInfluencers(child,infVec);
	}
	*/
}


XMLFileManipulator::~XMLFileManipulator()
{
}

void XMLFileManipulator::readInfluencers(tinyxml2::XMLElement *bone, std::vector<Element*> &infVec){
	/*XMLElement *inf;
	
	for (inf = bone->FirstChildElement("influencer"); inf != 0; inf = inf->NextSiblingElement("influencer")){
		Element *ei = new Element();
		ei->boneName = bone->Attribute("name");
		ei->influencerName = inf->Attribute("name");
		std::cout << "influencer:  " << inf->Attribute("name") << std::endl;
		std::cout << "influencer:  " << ei->influencerName << std::endl;
		XMLElement *children;
		for (children = inf->FirstChildElement(); children != 0; children = children->NextSiblingElement()){
			std::cout << "reading more info: \n";
			if (strcmp(children->Name(), "minAngle") == 0){
				std::cout << "minAngle: "<< children->GetText() << std::endl;
				ei->minAngle = children->GetText();
			}
			if (strcmp(children->Name(), "maxAngle") == 0){
				std::cout << "maxAngle: " << children->GetText() << std::endl;
				ei->maxAngle = children->GetText();
			}
			if (strcmp(children->Name(), "axis") == 0){
				std::cout << "axis: " << children->GetText() << std::endl;
				ei->axis = children->GetText();
			}
			if (strcmp(children->Name(), "percentage") == 0){
				std::cout << "percentage: " << children->GetText() << std::endl;
				ei->percentage = children->GetText();
			}
		}
		infVec.push_back(ei);
		//std::cout << "influencer:  " << ei.boneName <<infVec.size<< std::endl;
	}*/
}

Element *XMLFileManipulator::getInfluencer(const char* boneName){
	/*for (element_influencer in : infVec){
		std::cout << "Comparing " << boneName << " with " << in.boneName << " and " << in.influencerName << std::endl;
		if (strcmp(in.boneName, boneName) == 0)
			return &in;
		if (strcmp(in.influencerName, boneName) == 0)
			return &in;
	}
	return  NULL;*/
	return NULL;
}