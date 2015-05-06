#version 400

in vec4 pos;
in vec2 vl_TexCoord;
uniform sampler2D sampler0;
out vec3 vPosition;

void main(void)
{
	vPosition = pos.xyz;
	
}