#include "RenderPass.h"
#include "Utils/FileIO.h"
#include "VertexData.h"
void RenderPass::Bind(Camera* camera)
{
	glUseProgram(mShader->mProgram);
	GlobalRenderState::SetBlendState(mRenderState.mbEnableBlend);
	GlobalRenderState::SetBlendFunc(mRenderState.mSrcBlendFunc, mRenderState.mDstBlendFunc);
	GlobalRenderState::SetDepthTestState(mRenderState.mbEnableDepthTest);
	GlobalRenderState::SetDepthMask(mRenderState.mbWriteDepthBuffer);
	if (mShader->mAttributes != nullptr) 
	{
		mShader->mAttributes->Active();
	}
	UniformUpdater* uniform_updater = mUniforms;
	while (uniform_updater != nullptr)
	{
		uniform_updater->mUpdateFunction(uniform_updater->mLocation, camera, uniform_updater->mTargetProperty);
		uniform_updater = uniform_updater->Next<UniformUpdater>();
	}
}
void RenderPass::SetMatrix4(const char* uniform_name, float* mat4) 
{
	auto iter = mProperties.find(uniform_name);
	if (iter != mProperties.end()) 
	{
		((MaterialPropertyMatrix4*)iter->second)->mPropertyValue = mat4;
	}
}
void RenderPass::SetVec4(const char* uniform_name, float* ptr) 
{
	auto iter = mProperties.find(uniform_name);
	if (iter != mProperties.end())
	{
		((MaterialPropertyVec4*)iter->second)->mPropertyValue = ptr;
	}
}

void RenderPass::SetMatrix3(const char* uniform_name, float* mat3)
{
	auto iter = mProperties.find(uniform_name);
	if (iter != mProperties.end())
	{
		((MaterialPropertyMatrix3*)iter->second)->mPropertyValue = mat3;
	}
}
void RenderPass::SetMatrix2(const char* uniform_name, float* mat2)
{
	auto iter = mProperties.find(uniform_name);
	if (iter != mProperties.end())
	{
		((MaterialPropertyMatrix2*)iter->second)->mPropertyValue = mat2;
	}
}

void RenderPass::SetVec3(const char* uniform_name, float* ptr)
{
	auto iter = mProperties.find(uniform_name);
	if (iter != mProperties.end())
	{
		((MaterialPropertyVec3*)iter->second)->mPropertyValue = ptr;
	}
}
void RenderPass::SetVec2(const char* uniform_name, float* ptr)
{
	auto iter = mProperties.find(uniform_name);
	if (iter != mProperties.end())
	{
		((MaterialPropertyVec2*)iter->second)->mPropertyValue = ptr;
	}
}
void RenderPass::SetBool(const char* uniform_name, bool value)
{
	auto iter = mProperties.find(uniform_name);
	if (iter != mProperties.end())
	{
		((MaterialPropertyBool*)iter->second)->mPropertyValue = value;
	}
}
void RenderPass::SetFloat(const char* uniform_name, float value)
{
	auto iter = mProperties.find(uniform_name);
	if (iter != mProperties.end())
	{
		((MaterialPropertyFloat*)iter->second)->mPropertyValue = value;
	}
}
void RenderPass::SetInt(const char* uniform_name, int value)
{
	auto iter = mProperties.find(uniform_name);
	if (iter != mProperties.end())
	{
		((MaterialPropertyInt*)iter->second)->mPropertyValue = value;
	}
}

void RenderPass::SetSampler2D(const char* uniform_name, GLuint texture_name)
{
	auto iter = mProperties.find(uniform_name);
	if (iter != mProperties.end()) {
		((MaterialPropertySampler2D*)iter->second)->mTextureName = texture_name;
	}
}

void RenderPass::SetSamplerCube(const char* uniform_name, GLuint texture_name) 
{
	auto iter = mProperties.find(uniform_name);
	if (iter != mProperties.end()) {
		((MaterialPropertySampler2D*)iter->second)->mTextureName = texture_name;
	}
}

void RenderPass::SetShader(Shader* shader) 
{
	mShader = shader;
	mUniforms = nullptr;
	UniformUpdater* current_uniform_updater = shader->mUniforms;
	while (current_uniform_updater != nullptr) 
	{
		UniformUpdater* uniform_updater = current_uniform_updater->Clone();
		AppendUniformUpdater(uniform_updater);
		if (uniform_updater->mTargetProperty != nullptr)
		{
			mProperties.insert(std::pair<std::string, MaterialProperty*>(uniform_updater->mTargetProperty->mName, uniform_updater->mTargetProperty));
		}
		current_uniform_updater = current_uniform_updater->Next<UniformUpdater>();
	}
}
void RenderPass::AppendUniformUpdater(UniformUpdater* uniform_updater)
{
	if (mUniforms == nullptr)
	{
		mUniforms = uniform_updater;
	}
	else 
	{
		mUniforms->PushBack(uniform_updater);
	}
}