#include "Material.h"
#include "VertexData.h"
#include "Utils/FileIO.h"
#include "Camera.h"
Material::Material()
{
	mBaseRenderPass = nullptr;
	mAdditiveRenderPass = nullptr;
}
void Material::Bind(Camera* camera) 
{
	mBaseRenderPass->Bind(camera);
}
void Material::SetMatrix4(const char* uniform_name, float* mat4) 
{
	if (mBaseRenderPass != nullptr) 
	{
		mBaseRenderPass->SetMatrix4(uniform_name, mat4);
	}
	if (mAdditiveRenderPass != nullptr) 
	{
		mAdditiveRenderPass->SetMatrix4(uniform_name, mat4);
	}
}
void Material::SetVec4(const char* uniform_name, float* ptr) 
{
	if (mBaseRenderPass != nullptr) {
		mBaseRenderPass->SetVec4(uniform_name, ptr);
	}
	if (mAdditiveRenderPass != nullptr) {
		mAdditiveRenderPass->SetVec4(uniform_name, ptr);
	}
}
