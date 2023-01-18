#pragma once
#include "YosefGL.h"
#include "YosefPrefix.h"
#include "Attribute.h"
#include "MaterialProperty.h"
#include "UniformUpdater.h"
#include "RenderState.h"
#include "RenderPass.h"
#include "Camera.h"
class Material 
{
public:
	Material();
	RenderPass* mBaseRenderPass, * mAdditiveRenderPass;
	void Bind(Camera* camera);
	void SetMatrix4(const char* uniform_name, float* mat4);
	void SetVec4(const char* uniform_name, float* ptr);
};
