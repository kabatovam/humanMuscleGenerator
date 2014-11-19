uniform sampler2D texture;
in VertexData
{
	vec4 mapColor;
}VertexIn;
void main(void){
   
   vec4 pom = texture2D(texture,gl_TexCoord[0].st);
   gl_FragColor = mapColor;
}
