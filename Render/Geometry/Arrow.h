#pragma once
#include "../YosefGL.h"
#include "../YosefPrefix.h"
#include "../VertexData.h"
#include "../GL30/VAO.h"
#include "../GL30/VBO.h"
#include "../GL30/EBO.h"
#include "../Material.h"
#include "../DrawCall.h"
class Arrow2D 
{
public:
	Arrow2D()
	{
		mData = new VertexDataFull[6];
		mVAO = nullptr;
		mVBO = nullptr;
		mMaterial = nullptr;
		mDC = nullptr;
	}
	~Arrow2D()
	{
		delete[] mData;
		delete mVAO;
		delete mVBO;
		delete mMaterial;
		delete mDC;
		mVAO = nullptr;
		mVBO = nullptr;
		mMaterial = nullptr;
		mDC = nullptr;
	}
	void Init()
	{
		mVAO = new VAO;
		mVAO->Init();
		mVBO = new VBO;
		mVBO->SetSize(6, GL_DYNAMIC_DRAW);

		mMaterial = new Material;
		mMaterial->mBaseRenderPass = new RenderPass;
		

		mDC = new DrawCall;
		mDC->mVAO = mVAO;
		mDC->mVBO = mVBO;
		mDC->mMaterial = mMaterial;
	}
	void SetShader(Shader* shader)
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
	void UpdateForce(float x_press, float y_press, float x_release, float y_release, DrawCall* dc2)
	{
		mVAO->Bind();
		mVBO->Bind();

		float x_start = (float)x_press;
		float y_start = (float)y_press;
	
		glm::vec2 force_end = glm::vec2(x_release, y_release);
		force_end = glm::normalize(force_end) * 0.35f;

		float x_end = x_start + (float)force_end.x;
		float y_end = y_start + (float)force_end.y;

		
		/*x_end = (x_end - 146) / (1135 - 146) * 3 - 1.5f;
		y_end = (y_end - 30) / (690 - 30) * 2 - 1.0f;*/

		float length = sqrt((x_end - x_start) * (x_end - x_start) + (y_end - y_start) * (y_end - y_start));
		float angle = atan2(y_end - y_start, x_end - x_start);

		float x_left = x_end - 0.1f * length * cos(angle + 3.1415f / 4.0f);
		float y_left = y_end - 0.1f * length * sin(angle + 3.1415f / 4.0f);

		float x_right = x_end - 0.1f * length * cos(angle - 3.1415f / 4.0f);
		float y_right = y_end - 0.1f * length * sin(angle - 3.1415f / 4.0f);

		mData[0].mVertex = glm::vec4(x_start, y_start, -2.0f, 1.0f);
		mData[1].mVertex = glm::vec4(x_end, y_end, -2.0f, 1.0f);
		mData[2].mVertex = glm::vec4(x_left, y_left, -2.0f, 1.0f);
		mData[3].mVertex = glm::vec4(x_end, y_end, -2.0f, 1.0f);
		mData[4].mVertex = glm::vec4(x_end, y_end, -2.0f, 1.0f);
		mData[5].mVertex = glm::vec4(x_right, y_right, -2.0f, 1.0f);
		float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
		float red[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
		if (length < 1.0f)
			mMaterial->mBaseRenderPass->SetBool("U_Color", true);
		else
			mMaterial->mBaseRenderPass->SetBool("U_Color", false);

		mVBO->SubmitData(mData, sizeof(VertexDataFull) * 6);
		mDC->mVAO = mVAO;
		mDC->mVBO = mVBO;
		mDC->mMaterial = mMaterial;
		dc2 = mDC;
	}
	void Update(float x_press, float y_press, float x_release, float y_release, DrawCall* dc2)
	{
		mVAO->Bind();
		mVBO->Bind();

		float x_start = (float)x_press;
		float y_start = (float)y_press;
		/*x_start = (x_start - 146) / (1135 - 146) * 3 - 1.5f;
		y_start = (y_start - 30) / (690 - 30) * 2 - 1.0f;*/

		float x_end = (float)x_release;
		float y_end = 720.0f - (float)y_release;

		x_end = x_end < 146 ? 146 : x_end;
		x_end = x_end > 1135 ? 1135 : x_end;
		y_end = y_end < 30 ? 30 : y_end;
		y_end = y_end > 690 ? 690 : y_end;

		x_end = (x_end - 146) / (1135 - 146) * 3 - 1.5f;
		y_end = (y_end - 30) / (690 - 30) * 2 - 1.0f;

		float length = sqrt((x_end - x_start) * (x_end - x_start) + (y_end - y_start) * (y_end - y_start));
		float angle = atan2(y_end - y_start, x_end - x_start);

		float x_left = x_end - 0.1f * length * cos(angle + 3.1415f / 4.0f);
		float y_left = y_end - 0.1f * length * sin(angle + 3.1415f / 4.0f);

		float x_right = x_end - 0.1f * length * cos(angle - 3.1415f / 4.0f);
		float y_right = y_end - 0.1f * length * sin(angle - 3.1415f / 4.0f);

		mData[0].mVertex = glm::vec4(x_start, y_start, -2.0f, 1.0f);
		mData[1].mVertex = glm::vec4(x_end, y_end, -2.0f, 1.0f);
		mData[2].mVertex = glm::vec4(x_left, y_left, -2.0f, 1.0f);
		mData[3].mVertex = glm::vec4(x_end, y_end, -2.0f, 1.0f);
		mData[4].mVertex = glm::vec4(x_end, y_end, -2.0f, 1.0f);
		mData[5].mVertex = glm::vec4(x_right, y_right, -2.0f, 1.0f);
		float blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
		float red[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
		if (length < 1.0f)
			mMaterial->mBaseRenderPass->SetBool("U_Color", true);
		else
			mMaterial->mBaseRenderPass->SetBool("U_Color", false);

		mVBO->SubmitData(mData, sizeof(VertexDataFull) * 6);
		mDC->mVAO = mVAO;
		mDC->mVBO = mVBO;
		mDC->mMaterial = mMaterial;
		dc2 = mDC;
	}
	DrawCall* GetDrawCall() { return mDC; }
public:
	VertexDataFull* mData;
	VAO* mVAO;
	VBO* mVBO;
	Material* mMaterial;
	DrawCall* mDC;
	glm::mat4 mModelMatrix = glm::mat4(1.0f);
	float mXStart, mYStart, mXEnd, mYEnd, mXLeft, mYLeft, mXRight, mYRight;
	bool mbLineDraw = false;
	bool mbLineMove = false;
};