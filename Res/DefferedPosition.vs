#version 330 core
in vec4 position;
in vec4 texcoord;
in vec4 normal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec4 V_WorldPos;
out vec4 V_Normal;

void main()
{
	V_WorldPos = M * position;
	V_Normal = M * normal;
	gl_Position = P * V * M * position;
}