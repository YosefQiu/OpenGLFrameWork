#pragma once
#include "YosefGL.h"
#include "YosefPrefix.h"
#include "GL30/VAO.h"
#include "GL30/VBO.h"
#include "GL30/EBO.h"
#include "Material.h"
#include "DrawCall.h"
#include "VertexData.h"

class Object
{
public:
	VertexDataFull* mData;
	VAO* mVAO;
	VBO* mVBO;
	EBO* mEBO;
	Material* mMaterial;
	DrawCall* mDC;
	int mVertexCount;
	glm::mat4 mModelMatrix = glm::mat4(1.0f);
	Object()
	{
		mData = nullptr;
		mVAO = nullptr;
		mEBO = nullptr;
		mMaterial = nullptr;
		mDC = nullptr;
		mVertexCount = -1;
	}
public:
	void SetShader(Shader* shader, bool baseFlag = true)
	{
		mMaterial->mBaseRenderPass->SetShader(shader);
	}
	void SetMatrix4(const char* uniform_name, float* mat4, bool baseFlag = true)
	{
		if (baseFlag)
		{
			if (mMaterial != nullptr && mMaterial->mBaseRenderPass)
			{
				mMaterial->mBaseRenderPass->SetMatrix4(uniform_name, mat4);
			}
		}
		else
		{
			if (mMaterial != nullptr && mMaterial->mAdditiveRenderPass)
			{
				mMaterial->mAdditiveRenderPass->SetMatrix4(uniform_name, mat4);
			}
		}

	}
	void SetVec4(const char* uniform_name, float* vec4, bool baseFlag = true)
	{
		if (baseFlag)
		{
			if (mMaterial != nullptr && mMaterial->mBaseRenderPass)
			{
				mMaterial->mBaseRenderPass->SetVec4(uniform_name, vec4);
			}
		}
		else
		{
			if (mMaterial != nullptr && mMaterial->mAdditiveRenderPass)
			{
				mMaterial->mAdditiveRenderPass->SetVec4(uniform_name, vec4);
			}
		}
	}
	DrawCall* GetDrawCall() { return mDC; }
};

class Model 
{
public:
	void* mData;
	VAO* mVAO;
	VBO* mVBO;
	EBO* mEBO;
	Material* mMaterial;
	DrawCall* mDraw;
	int mVertexCount;
	glm::vec4 mMin = glm::vec4(std::numeric_limits<float>::max());
	glm::vec4 mMax = glm::vec4(std::numeric_limits<float>::min());
	glm::vec3 mCameraPos = glm::vec3(1.0f);
	glm::vec3 mTargetPos = glm::vec3(1.0f);
	glm::mat4 mModelMatrix = glm::mat4(1.0f);
public:
	Model();
	virtual ~Model();
	void Init(const char*modelPath);
	void ModelProcess(Shader* shader);
	void SetMatrix4(const char* uniform_name, float* mat4, bool baseFlag = true);
	void SetVec4(const char* uniform_name, float* vec4, bool baseFlag = true);
	DrawCall* GetDrawCall() { return mDraw; }
	glm::vec3 GetCameraPos() { return mCameraPos; }
	glm::vec3 GetTargetPos() { return mTargetPos; }
};