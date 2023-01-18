#version 330 core

in vec4 V_Color;
in vec4 V_Normal;
in vec4 V_WorldPos;
layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 posColor;
layout (location = 2) out vec4 norColor;
uniform vec4 U_Color;

void main()
{
	float scale = 1.0f;
	float w = 1.0f / scale;
	vec3 world_pos_scaled = V_WorldPos.xyz / scale;
	vec3 world_pos_encoded = 0.5f * (world_pos_scaled + vec3(1.0f));
	posColor = vec4(world_pos_encoded, w);
	norColor = vec4(0.5f * (normalize(V_Normal).xyz + vec3(1.0f)), 1.0f);
	fragColor = V_Color + U_Color;
}