#version 330 core
in vec4 normal;
in vec4 position;
in vec4 texcoord;


uniform mat4 M;
uniform mat4 V;
uniform mat4 P;


void main()
{
	gl_Position = P * V * M * position;
}