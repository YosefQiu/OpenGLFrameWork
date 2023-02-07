#pragma once

// ** This file contains all the built-in shaders
static const char* sSkyBoxVS =
"#version 330 core										\n"
"in vec4 position;										\n"
"uniform mat4 M;										\n"
"uniform mat4 V;										\n"
"uniform mat4 P;										\n"
"out vec3 V_Texcoord;									\n"
"void main()											\n"
"{														\n"
"	V_Texcoord = position.xyz;							\n"
"	vec4 pos  = P* mat4(mat3(V)) * position;			\n"
"	gl_Position = pos.xyww;								\n"
"}														\n";

static const char* sSkyBoxFS =
"#version 330 core											\n"
"precision mediump float;									\n"
"in vec3 V_Texcoord;										\n"
"uniform samplerCube U_Texture;								\n"
"out vec4 fragColor;										\n"
"void main()												\n"
"{															\n"
"	 fragColor = texture(U_Texture, normalize(V_Texcoord));	\n"
"}															\n";

static const char* sQuadDebugVS =
"#version 330 core					\n"
"in vec4 position;					\n"
"in vec4 texcoord;					\n"
"out vec2 V_Texcoord;				\n"
"void main()						\n"
"{									\n"
"	V_Texcoord = texcoord.xy;		\n"
"	gl_Position = position;			\n"
"}									\n";

static const char* sQuadDebugFS =
"#version 330 core													\n"
"in vec2 V_Texcoord;												\n"
"uniform sampler2D U_Texture;										\n"
"uniform bool bDepth;												\n"
"out vec4 FragColor;												\n"
"float LinearizeDepth(float depth) {								\n"
"	float near = 0.1f;												\n"
"	float far = 100.0f;												\n"
"	float z = depth * 2.0f - 1.0f;									\n"
"	return (2.0f * near * far) / (far + near - z * (far - near));	\n"
"}																	\n"
"void main(){														\n"
"	const float gamma = 2.2f;										\n"
"	vec3 hdrColor = vec3(0.0f);										\n"
"	vec3 mapped = vec3(0.0f);										\n"
"	if (bDepth) {													\n"
"		float depthValue = texture(U_Texture, V_Texcoord.xy).r;		\n"
"		depthValue = LinearizeDepth(depthValue) / 100.0f;			\n"
"		mapped = vec3(depthValue);									\n"
"	}																\n"
"	else {															\n"
"		hdrColor = texture(U_Texture, V_Texcoord.xy).rgb;			\n"
"		mapped = hdrColor / (hdrColor + vec3(1.0f));				\n"
"		mapped = pow(mapped, vec3(1.0f / gamma));					\n"
"	}																\n"
"	FragColor = vec4(mapped, 1.0f);									\n"
"}																	\n";

static const char* sQuadImgFS =
"#version 330 core													\n"
"in vec2 V_Texcoord;												\n"
"uniform sampler2D U_Texture;										\n"
"out vec4 FragColor;												\n"
"void main(){														\n"
"	const float gamma = 2.2f;										\n"
"	vec3 hdrColor = vec3(0.0f);										\n"
"	vec3 mapped = vec3(0.0f);										\n"
"	hdrColor = texture(U_Texture, V_Texcoord.xy).rgb;				\n"
"	mapped = hdrColor / (hdrColor + vec3(1.0f));					\n"
"	mapped = pow(mapped, vec3(1.0f / gamma));						\n"
"	FragColor = vec4(mapped, 1.0f);									\n"
"}																	\n";

static const char* sGroundVS =
"#version 330 core									\n"
"in vec4 position;									\n"
"in vec4 texcoord;									\n"
"in vec4 normal;									\n"
"uniform mat4 M;									\n"
"uniform mat4 V;									\n"
"uniform mat4 P;									\n"
"out vec4 V_Color;									\n"
"out vec4 V_Normal;									\n"
"void main()										\n"
"{													\n"
"    V_Color = normal;							\n"
"    V_Normal = transpose(inverse(M)) * normal;		\n"
"    gl_Position = P * V * M * position;			\n"
"}													\n";

static const char* sGroundFS =
"#version 330 core							\n"
"in vec4 V_Color;							\n"
"in vec4 V_Normal;							\n"
"out vec4 FragColor;						\n"
"void main()								\n"
"{											\n"
"    FragColor = V_Color;					\n"
"}											\n";
