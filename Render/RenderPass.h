#pragma once
#include "YosefGL.h"
#include "YosefPrefix.h"
#include "Attribute.h"
#include "MaterialProperty.h"
#include "UniformUpdater.h"
#include "RenderState.h"
#include "Shader.h"
#include "Camera.h"
class RenderPass 
{
public:
	Shader* mShader;
	RenderState mRenderState;
	UniformUpdater* mUniforms;
	std::unordered_map<std::string, MaterialProperty*> mProperties;
	void SetMatrix4(const char* uniform_name, float* mat4);
	void SetMatrix3(const char* uniform_name, float* mat3);
	void SetMatrix2(const char* uniform_name, float* mat2);
	void SetVec4(const char* uniform_name, float* ptr);
	void SetVec3(const char* uniform_name, float* ptr);
	void SetVec2(const char* uniform_name, float* ptr);
	void SetBool(const char* uniform_name, bool value);
	void SetFloat(const char* uniform_name, float value);
	void SetInt(const char* uniform_name, int value);
	void SetSampler2D(const char* uniform_name, GLuint texture_name);
	void SetSamplerCube(const char* uniform_name, GLuint texture_name);
	void SetShader(Shader* shader);
	void Bind(Camera* camera);
	void AppendUniformUpdater(UniformUpdater* uniform_updater);
};