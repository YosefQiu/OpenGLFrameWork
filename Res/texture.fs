#version 330 core

uniform sampler2D U_PositionTexture;
uniform sampler2D U_NormalTexture;
uniform sampler2D U_ColorTexture;

in vec4 V_Texcoord;
out vec4 fragColor;

void main()
{
	vec4 data = texture(U_PositionTexture, V_Texcoord.xy);
	vec3 world_pos_encoded = (data.xyz * 2.0f - vec3(1.0f)) / data.w;
	vec4 normal_data = texture(U_NormalTexture, V_Texcoord.xy);
	vec3 normal = normal_data.xyz * 2.0f - vec3(1.0f);

	vec4 color = vec4(0.74f,0.78f,0.68f,1.0f);
	vec4 light_dir = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	vec3 L = normalize(light_dir).xyz;
	vec3 N = normalize(normal).xyz;

	float diffuseIntensity = max(0.0f, dot(L, N));
	vec4 diffuseColor = color * diffuseIntensity;

	vec3 reflect_dir = normalize(reflect(-L, N));
	vec3 world_pos = world_pos_encoded;
	vec3 view_dir = normalize(vec3(0.0f) - world_pos);
	vec4 specularColor = color * pow(max(0.0f, dot(view_dir, reflect_dir)), 32.0f);

	
	vec4 color_data = texture(U_ColorTexture, V_Texcoord.xy);
	fragColor = color_data = diffuseColor + specularColor;

}