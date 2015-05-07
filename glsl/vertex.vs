#version 400 
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in ivec4 boneIDs;
layout (location = 3) in vec4 boneWeights;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 bones[3];

out vec3 vPosition;
out vec2 vTexCoord;
void main()
{
	mat4 boneTransform = bones[boneIDs[0]] * boneWeights[0]; 
	boneTransform += bones[boneIDs[1]] * boneWeights[1];
	boneTransform += bones[boneIDs[2]] * boneWeights[2];
	boneTransform += bones[boneIDs[3]] * boneWeights[3];
	
	vec4 bonePosition = boneTransform * vec4(position, 1.0f);
	//gl_Position = projection *  view * model * bonePosition;
	vPosition = bonePosition.xyz;
	vTexCoord = texCoord;
}