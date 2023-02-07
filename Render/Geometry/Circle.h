#pragma once
#include "../YosefGL.h"
#include "../YosefPrefix.h"
#include "../VertexData.h"
#include "../GL30/VAO.h"
#include "../GL30/VBO.h"
#include "../GL30/EBO.h"
#include "../Material.h"
#include "../DrawCall.h"
#include "../model.h"
class Circle2D : public Object
{
public:
	Circle2D(){}
	Circle2D(glm::vec2 center, float r)
	{
		mCenter = center;
		mRadius = r;

		mDC = new DrawCall;
		mVAO = new VAO;
		mVAO->Init();
		mVBO = new VBO;
		int split = mSplit;
		mVertexCount = split * 1;
		mData = new VertexDataFull[split * 1];

		for (int i = 0; i < split * 1; i++)
		{
			float theta = 2.0f * 3.1415926f * float(i) / float(split);

			float x = mRadius * cosf(theta);
			float y = mRadius * sinf(theta);
			mData[i].mVertex = glm::vec4(mCenter.x + x, mCenter.y + y, -2.0f, 1.0f);
		}

		mVBO->SetSize(mVertexCount);
		mVBO->SubmitData(mData, sizeof(VertexDataFull) * mVertexCount);

		mMaterial = new Material;
		mMaterial->mBaseRenderPass = new RenderPass;

		mDC->mVAO = mVAO;
		mDC->mVBO = mVBO;
		mDC->mMaterial = mMaterial;
	}
	~Circle2D()
	{
		delete[] mData;

	}
public:
	glm::vec2 mCenter;
	float mRadius;
	int mSplit = 360;
	glm::vec4 mColor = glm::vec4(1.0f);
};