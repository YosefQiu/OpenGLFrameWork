#version 330 core

in vec4 position;
in vec4 texcoord;
out vec4 V_Texcoord;


void main()
{
	V_Texcoord = texcoord;
	gl_Position = position;
}
