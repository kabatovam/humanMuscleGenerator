#version 400 
in vec2 texCoord;
uniform sampler2D dispMap;
in vec4 color_ES;
out vec4 color;
void main()
{
	vec4 color_t = texture(dispMap,vec2(texCoord.x,texCoord.y));
	//color = vec4(color_t);
	//color = vec4(255,0.0,0.0,1.0);
	color = color_ES;
}