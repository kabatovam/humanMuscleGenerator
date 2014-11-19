uniform sampler2D heightMap;
out VertexData {
	vec4 mapColor;
} VertexOut;

void main(void)
{
	VertexOut.mapColor = texture2D(heightMap,gl_MultiTexCoord0);	
	vec4 position = ftransform();
	gl_Position = position;
}