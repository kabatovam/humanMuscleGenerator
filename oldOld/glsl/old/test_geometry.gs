#version 330
 
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
 
in VertexData {
    vec2 texCoord;
	vec4 mapColor;
} VertexIn[];
 
out vec2 texCoord;

void main(void) {
	for (int i = 0; i < gl_in.length(); ++i) {
	
		vec3 distance = vec3(VertexIn[i].mapColor.r,VertexIn[i].mapColor.g,VertexIn[i].mapColor.b);
                vec4 position = vec4(gl_in[i].gl_Position.x,gl_in[i].gl_Position.y,gl_in[i].gl_Position.z*distance.g,gl_in[i].gl_Position.w);
		gl_Position = position;
		EmitVertex();
	}
	EndPrimitive();
}
