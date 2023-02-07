#version 330 core
out vec4 fragColor;
uniform vec4 U_COLOR;
void main()
{
	vec4 color = U_COLOR;
	fragColor = color;
}