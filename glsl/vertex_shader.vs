#version 400



in vec4 pos;

out vec3 vPosition;
void main(void)
{
	vPosition = pos.xyz;
	
}