
#version 400

in vec2 texCoord;
uniform sampler2D sampler0;
out vec4 FragColor;
void main(void)
{
	vec4 texColor = texture(sampler0,texCoord);	
	FragColor = texColor;
	
}