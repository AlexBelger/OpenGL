#version 430
 
in layout(location=0) vec2 position;
in layout(location=1) vec3 inColor;
out vec3 color; 

void main(void)
{
	gl_Position = vec4(position, 0.0, 1.0);
	color = inColor;
}