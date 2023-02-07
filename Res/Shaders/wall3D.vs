#version 330 core
in vec4 position;
in vec4 texcoord;
in vec4 normal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec2 V_Texture;
out vec3 V_Normal;
out vec4 V_WorldPos;
void main()
{
	V_Texture = texcoord.xy;
	V_Normal = normal.xyz;
	V_WorldPos = M * position;
	gl_Position = P * V * M * position;
}