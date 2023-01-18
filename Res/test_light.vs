#version 330 core
in vec4 position;
in vec4 texcoord;
in vec4 normal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec4 V_Normal;
out vec4 V_WorldPos;
out vec4 V_Color;

vec4 GetLightColor()
{
	vec4 pos = vec4(1.0f, 1.0f, 0.0f, 0.0f);
	return dot(pos.xyz, normal.xyz) * vec4(1.0f, 0.0f, 0.0, 1.0f);
}

vec4 GetLightColor2()
{
	vec4 pos = vec4(-1.0f, 1.0f, 0.0f, 0.0f);
	return dot(pos.xyz, normal.xyz) * vec4(0.0f, 1.0f, 0.0, 1.0f);
}

void main()
{
	V_WorldPos = M * position;
	V_Normal = M * normal;
	V_Color = GetLightColor() + GetLightColor2();
	gl_Position = P * V * M * position;
}