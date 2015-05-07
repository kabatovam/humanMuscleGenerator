#version 400 
in vec2 texCoord;
uniform sampler2D tex;
out vec4 color;
void main()
{
	vec4 color_t = texture(tex,vec2(texCoord.x,texCoord.y));
	color = vec4(color_t);
	//color = vec4(1.0,0.0,0.0,1.0);
}