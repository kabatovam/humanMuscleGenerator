#include "MeshManipulator.h"
#include <iostream>
#include <string>
MeshManipulator::MeshManipulator(){

}

MeshManipulator::MeshManipulator(aiMesh *mesh)
{
	std::cout << "som tu!\n";
	if (mesh->mNumVertices > 0){
		
		for (GLuint i = 0; i < mesh->mNumVertices; i++){

			vertices.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
		}
	}
	else{
	}

	if (mesh->HasNormals()){
		for (GLuint i = 0; i<mesh->mNumVertices; i++){
			normals.push_back(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		}
	}
	
	if (mesh->HasTextureCoords(0)){
		std::cout << "readin texture!\n";
		for (GLuint i = 0; i < mesh->mNumVertices; i++){
			texCoords.push_back(glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
			
		}

	}
	if (mesh->HasFaces()){
		std::cout << "reading faces!\n";
		for (GLuint i = 0; i < mesh->mNumFaces; i++){
			aiFace face = mesh->mFaces[i];
			for (GLuint i = 0; i < face.mNumIndices; i++){
				indices.push_back(face.mIndices[i]);
			}

		}
	}
	if (mesh->HasBones()){
		boneMap.resize(mesh->mNumBones);
		std::cout << "I have " << mesh->mNumBones << " bones!" << std::endl;
		vertexBoneIDs.resize(mesh->mNumVertices * 4,0); //we allow 4 bones
		vertexBoneWeights.resize(mesh->mNumVertices * 4,0.0); //we allow 4 bones
		boneCount = mesh->mNumBones - 1;
		for (GLuint i = 0; i < mesh->mNumBones; i++){
			std::cout << "Creating bone with name: " << mesh->mBones[i]->mName.data << "and index" << i <<std::endl;
			Bone bone(mesh->mBones[i]);
			bones.push_back(*mesh->mBones[i]);
			boneMap[i] = mesh->mBones[i]->mName.data;
			std::cout << "I have " << mesh->mBones[i]->mNumWeights << "weights";
			std::cout << "Number of vertices: " << mesh->mNumVertices << std::endl;
			for (GLuint j = 0; j < mesh->mBones[i]->mNumWeights; j++){
				GLuint startingIndex = mesh->mBones[i]->mWeights[j].mVertexId;
				//std::cout << "VertexIndex: " << mesh->mBones[i]->mWeights[j].mVertexId << ", : "<< i <<", :" << mesh->mBones[i]->mWeights[j].mWeight <<std::endl;
				startingIndex *= 4;
				for (int k = 0; k < 4; k++){
					if (!(vertexBoneWeights[startingIndex + k] > 0.0)){
						vertexBoneWeights[startingIndex + k] = mesh->mBones[i]->mWeights[j].mWeight;
						vertexBoneIDs[startingIndex + k] = i;
						break;
					}
				}
			}

			//std::cout << "i: " << i << "kost cislo: " << bones[i].mName.data<<std::endl;
			//setupBindPose();
			//offsetMatrices.push_back(mat);
			offsetMatrices.resize(4);
			
		}
		
	}
	std::cout << "Bone map! :\n";
	for (GLuint i = 0; i < boneMap.size(); i++){
		std::cout <<i << ":"<< boneMap[i] << std::endl;
	}

	
}


MeshManipulator::~MeshManipulator()
{
}

void MeshManipulator::findChildren(std::string parentName, std::string childsName){
	std::string parentBone;
	std::string childBone;
	
	std::cout << "Parent name: " << parentName << ". Childs name: " << parentName << std::endl;
	
	for (aiBone b : bones){
		if (parentName.compare(b.mName.data) == 0){
			parentBone = b.mName.data;
		}
		if (childsName.compare(b.mName.data) == 0){
			childBone = b.mName.data;
		}
		//std::cout<<b.getName()<<std::endl;
	}
	if (!parentBone.empty() && !childBone.empty()){
	}

	Bone *bone = NULL;
	if (parentBone.empty() && !childBone.empty()){ //create root
		std::cout << "Setting root bone named: " << childBone << std::endl;
		for (aiBone b : bones){
			if (childBone.compare(b.mName.data) == 0){
				rootBone = new Bone(&b);
				for (GLuint i = 0; i < boneMap.size(); i++){
					if (rootBone->getName().compare(boneMap[i]) == 0){
						std::cout <<"Settin bone!" << i << ":" << boneMap[i] << std::endl;
						rootBone->setBoneID(i);
					}
				}
				
			}
		}
	}
	else if (parentBone.compare(childBone) != 0 && !childBone.empty()){
		
		std::cout << "Parent name: " << parentBone << ". Childs name: " << childBone << std::endl;
		for (aiBone b : bones){
			if (childsName.compare(b.mName.data) == 0){
				bone = new Bone(&b);
				for (GLuint i = 0; i < boneMap.size(); i++){
					if (bone->getName().compare(boneMap[i]) == 0){
						std::cout << "Settin bone!" << i << ":" << boneMap[i] << std::endl;
						bone->setBoneID(i);
					}
				}
				
			}
		}
		Bone *temp = rootBone;
		while (temp != NULL){
			if (temp->getName() == parentBone){ //compare
				bone->setParentBone(temp);
				temp->setChildBode(bone);
				break;
			}
			temp = temp->next;
		}
	}
		
}

void MeshManipulator::writeBones(){
	Bone *temp = rootBone;
	while (temp != NULL){
		std::cout << "I am bone: " << temp->getName() << ". I have id: " << temp->getBoneID() << std::endl;
		temp = temp->next;
	}

}

void MeshManipulator::bindBones(GLuint *shaderProgram){
	const GLuint MAX_BONES = 4;
	GLuint boneLoc[MAX_BONES];
	
	for (GLuint i = 0; i < MAX_BONES; i++){
		std::string name = "bones[";
			name += std::to_string(i);
			name += "]";
		boneLoc[i] = glGetUniformLocation(*shaderProgram, name.c_str());
	}



	for (GLuint i = 0; i < MAX_BONES; i++){
		glm::mat4 mat = offsetMatrices[i];
		/*
			std::cout << "I am binding final matrix number: " << i << " . Here it is!:\n";
			std::cout << mat[0][0] << "," << mat[0][1] << "," << mat[0][2] << "," << mat[0][3] << std::endl
				<< mat[1][0] << "," << mat[1][1] << "," << mat[1][2] << "," << mat[1][3] << std::endl
				<< mat[2][0] << "," << mat[2][1] << "," << mat[2][2] << "," << mat[2][3] << std::endl
				<< mat[3][0] << "," << mat[3][1] << "," << mat[3][2] << "," << mat[3][3] << std::endl;
		*/
		glUniformMatrix4fv(boneLoc[i], 1, GL_TRUE, glm::value_ptr(mat));
	}
		
}

void MeshManipulator::RotateBone(std::string boneName, float angle, float x, float y, float z, bool parentTransformation, aiMatrix4x4 globalInverseTransform){
	Bone *temp = rootBone;
	bool transform = parentTransformation;
	while (temp != NULL){
		//if we have match with boneName
		if (boneName.compare(temp->getName()) == 0){
			//Rotate the bone
			std::cout << "Rotating bone! " << temp->getName() << std::endl;
			temp->rotateBone(angle, aiVector3t<float>(x, y, z), globalInverseTransform);
			transform = true;
		
			glm::mat4x4 mat = temp->getFinalTransform();
			GLuint i = temp->getBoneID();
			//priradenie pre maticu - supnut do samostatnej funkcie
			offsetMatrices[i][0][0] = mat[0][0]; offsetMatrices[i][0][1] = mat[0][1]; offsetMatrices[i][0][2] = mat[0][2]; offsetMatrices[i][0][3] = mat[0][3];
			offsetMatrices[i][1][0] = mat[1][0]; offsetMatrices[i][1][1] = mat[1][1]; offsetMatrices[i][1][2] = mat[1][2]; offsetMatrices[i][1][3] = mat[1][3];
			offsetMatrices[i][2][0] = mat[2][0]; offsetMatrices[i][2][1] = mat[2][1]; offsetMatrices[i][2][2] = mat[1][2]; offsetMatrices[i][2][3] = mat[2][3];
			offsetMatrices[i][3][0] = mat[3][0]; offsetMatrices[i][3][1] = mat[3][1]; offsetMatrices[i][3][2] = mat[3][2]; offsetMatrices[i][3][3] = mat[3][3];
				
			
		}
		//if our parent matched the BoneName
		else {
			std::cout << "Rotating child bone! " << temp->getName() << std::endl;
			temp->setBindPose(globalInverseTransform);
			glm::mat4x4 mat = temp->getFinalTransform();
			GLuint i = temp->getBoneID();

			//priradenie pre maticu - supnut do samostatnej funkcie
			offsetMatrices[i][0][0] = mat[0][0]; offsetMatrices[i][0][1] = mat[0][1]; offsetMatrices[i][0][2] = mat[0][2]; offsetMatrices[i][0][3] = mat[0][3];
			offsetMatrices[i][1][0] = mat[1][0]; offsetMatrices[i][1][1] = mat[1][1]; offsetMatrices[i][1][2] = mat[1][2]; offsetMatrices[i][1][3] = mat[1][3];
			offsetMatrices[i][2][0] = mat[2][0]; offsetMatrices[i][2][1] = mat[2][1]; offsetMatrices[i][2][2] = mat[1][2]; offsetMatrices[i][2][3] = mat[2][3];
			offsetMatrices[i][3][0] = mat[3][0]; offsetMatrices[i][3][1] = mat[3][1]; offsetMatrices[i][3][2] = mat[3][2]; offsetMatrices[i][3][3] = mat[3][3];
			
		}
		//else
		temp = temp->next;
	}
		
		
		

}

void MeshManipulator::setTransform(std::string boneName, aiMatrix4x4 transform){
	Bone *temp = rootBone;
	std::cout << "I am in the bone transform setting function. Bone name is: " << boneName <<"\n";
	while (temp != NULL){
		if (boneName.compare(temp->getName()) == 0){
			temp->setBoneTransform(transform);
		}
		temp = temp->next;
	}
}

void MeshManipulator::setupBindPose(aiMatrix4x4 globalInverseTransform){
	Bone *temp = rootBone;
	std::cout << "I am here!\n";
	while (temp != NULL){
		std::cout << "I am here!" << temp->getName() << std::endl;
		temp->setBindPose(globalInverseTransform);
		glm::mat4x4 mat = temp->getFinalTransform();
		GLuint i = temp->getBoneID();

		
		
		std::cout << "I received matrix. Here it is: ";
			std::cout << mat[0][0] << "," << mat[0][1] << "," << mat[0][2] << "," << mat[0][3] << std::endl
			<< mat[1][0] << "," << mat[1][1] << "," << mat[1][2] << "," << mat[1][3] << std::endl
			<< mat[2][0] << "," << mat[2][1] << "," << mat[2][2] << "," << mat[2][3] << std::endl
			<< mat[3][0] << "," << mat[3][1] << "," << mat[3][2] << "," << mat[3][3] << std::endl;

		std::cout << "I am binding final matrix number: " << i << " . Here it is!:\n";
		offsetMatrices[i][0][0] = mat[0][0]; offsetMatrices[i][0][1] = mat[0][1]; offsetMatrices[i][0][2] = mat[0][2]; offsetMatrices[i][0][3] = mat[0][3];
		offsetMatrices[i][1][0] = mat[1][0]; offsetMatrices[i][1][1] = mat[1][1]; offsetMatrices[i][1][2] = mat[1][2]; offsetMatrices[i][1][3] = mat[1][3];
		offsetMatrices[i][2][0] = mat[2][0]; offsetMatrices[i][2][1] = mat[2][1]; offsetMatrices[i][2][2] = mat[2][2]; offsetMatrices[i][2][3] = mat[2][3];
		offsetMatrices[i][3][0] = mat[3][0]; offsetMatrices[i][3][1] = mat[3][1]; offsetMatrices[i][3][2] = mat[3][2]; offsetMatrices[i][3][3] = mat[3][3];

		std::cout << offsetMatrices[i][0][0] << "," << offsetMatrices[i][0][1] << "," << offsetMatrices[i][0][2] << "," << offsetMatrices[i][0][3] << std::endl
			<< offsetMatrices[i][1][0] << "," << offsetMatrices[i][1][1] << "," << offsetMatrices[i][1][2] << "," << offsetMatrices[i][1][3] << std::endl
			<< offsetMatrices[i][2][0] << "," << offsetMatrices[i][2][1] << "," << offsetMatrices[i][2][2] << "," << offsetMatrices[i][2][3] << std::endl
			<< offsetMatrices[i][3][0] << "," << offsetMatrices[i][3][1] << "," << offsetMatrices[i][3][2] << "," << offsetMatrices[i][3][3] << std::endl;


		temp = temp->next;
	}
}

void MeshManipulator::startAnimation(aiAnimation *_anim){
	anim = new AnimationManipulator(_anim);
	Bone *temp = rootBone;
	aiNodeAnim *node = NULL;
	while (temp != NULL){
		for (GLuint i = 0; i < _anim->mNumChannels; i++){
			if (temp->getName().compare(_anim->mChannels[i]->mNodeName.data) == 0)
			{
				node = _anim->mChannels[i];
				break;
			}
		}
		if (node != NULL)
			temp->createAnimationInfo(node);
		node = NULL;
		temp = temp->next;
	}
	
}

void MeshManipulator::tick(aiMatrix4x4 git, aiAnimation *_anim){
	anim->updateTime(0.001);
	Bone *temp = rootBone;
	std::cout << "Nova animacia." << anim->getAnimationTime() << std::endl;
	aiNodeAnim *node = NULL;
	while (temp != NULL){
		
		temp->animateBone(anim, anim->getAnimationTime(), git);
		glm::mat4x4 mat = temp->getFinalTransform();
		GLuint i = temp->getBoneID();

		offsetMatrices[i][0][0] = mat[0][0]; offsetMatrices[i][0][1] = mat[0][1]; offsetMatrices[i][0][2] = mat[0][2]; offsetMatrices[i][0][3] = mat[0][3];
		offsetMatrices[i][1][0] = mat[1][0]; offsetMatrices[i][1][1] = mat[1][1]; offsetMatrices[i][1][2] = mat[1][2]; offsetMatrices[i][1][3] = mat[1][3];
		offsetMatrices[i][2][0] = mat[2][0]; offsetMatrices[i][2][1] = mat[2][1]; offsetMatrices[i][2][2] = mat[2][2]; offsetMatrices[i][2][3] = mat[2][3];
		offsetMatrices[i][3][0] = mat[3][0]; offsetMatrices[i][3][1] = mat[3][1]; offsetMatrices[i][3][2] = mat[3][2]; offsetMatrices[i][3][3] = mat[3][3];

		temp = temp->next;
	}
}