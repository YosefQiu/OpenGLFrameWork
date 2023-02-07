#version 330 core
out vec4 fragColor;
uniform vec4 U_COLOR;
uniform vec3 U_CameraPos;
uniform sampler2D U_Texture;
in vec2 V_Texture;
in vec3 V_Normal;
in vec4 V_WorldPos;
void main()
{
	vec4 ambient = vec4(0.3f, 0.2f, 0.3f, 1.0f);
	vec3 lightPos = vec3(0.0f,  0.0f, 0.0f);
	vec3 cameraPos = U_CameraPos;
	vec3 worldPos = V_WorldPos.xyz;

	vec3 L = normalize(lightPos - worldPos);
	vec3 N = normalize(V_Normal);

	vec4 blendColor = U_COLOR;
	vec4 baseColor = texture(U_Texture, V_Texture);

	float diffIntensity = max(0.0f, dot(L, N));
	vec4 diff = blendColor * baseColor * diffIntensity;

	vec3 reflectDir = normalize(reflect(-L, N));
	
	vec3 viewDir = normalize(cameraPos - worldPos);
	vec4 spec =  baseColor * pow(max(0.0f, dot(viewDir, reflectDir)), 128.0f);


	fragColor = diff + spec;
}