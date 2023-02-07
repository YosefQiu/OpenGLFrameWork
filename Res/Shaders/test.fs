#version 330 core

out vec4 fragColor;

uniform vec4 U_Color;
void main()
{
	fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}