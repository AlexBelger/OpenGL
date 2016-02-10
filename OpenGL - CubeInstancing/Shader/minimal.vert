#version 430
 
in layout(location=0) vec3 position;
in layout(location=1) vec3 inColor;
in layout(location=2) mat4 fullTransformMatrix;

out vec3 color; 

void main(void)
{
	vec4 v = vec4(position, 1.0);
	gl_Position = fullTransformMatrix * v;
	color = inColor;
}