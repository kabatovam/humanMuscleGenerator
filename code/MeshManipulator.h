#pragma once
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
// GLFW
#include <GLFW/glfw3.h>
#include <assimp/mesh.h>
#include <vector>

#include "Bone.h"
#include "AnimationManipulator.h"

class MeshManipulator
{
public:
	MeshManipulator(aiMesh *mesh);
	MeshManipulator();
	~MeshManipulator();
	GLuint getNumvertices(){ return vertices.size(); }
	const glm::vec3 *getVertices(){ return &vertices[0]; }
	GLuint getNumIndices(){ return indices.size(); }
	const GLuint *getIndices(){ return &indices[0]; }
	GLuint getNumTexCoords(){ return texCoords.size(); }
	const glm::vec2 *getTexCoords(){ return &texCoords[0]; }
	GLuint getNumVertexBoneIDs(){ return vertexBoneIDs.size(); }
	const GLuint *getVertexBoneIDs(){ return &vertexBoneIDs[0]; }
	GLuint getNumVertexBoneWeights(){ return vertexBoneWeights.size(); }
	const float *getVertexBoneWeights(){ return &vertexBoneWeights[0]; }
	void findChildren(std::string parentName, std::string childsName);
	void writeBones();
	void bindBones(GLuint *shaderProgram);
	void RotateBone(std::string BoneName, float angle, float x, float y, float z, bool parentTransformation, aiMatrix4x4 globalInverseTransform);
	void setTransform(std::string boneName, aiMatrix4x4 transform);
	void setupBindPose(aiMatrix4x4 globalInverseTransform);
	void startAnimation(aiAnimation *_anim);
	void tick(aiMatrix4x4 git,aiAnimation *_anim);

private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<GLuint> indices;
	std::vector<aiBone> bones;
	std::vector<GLuint> vertexBoneIDs;
	std::vector<GLfloat> vertexBoneWeights;
	std::vector<glm::mat4x4> offsetMatrices;
	Bone *rootBone;
	GLuint boneCount;
	GLuint tickCounter;
	GLuint ticksPerSecond;
	AnimationManipulator *anim;
	std::vector<std::string> boneMap;
};

