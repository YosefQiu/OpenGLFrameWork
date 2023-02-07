#version 330 core
in vec4 position;
in vec4 texcoord;
in vec4 normal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec4 V_Color;

void main()
{
	V_Color = normal;
	gl_Position = P * V * M * position;
}