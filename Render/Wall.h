#pragma once
#include "model.h"

enum class WallType : int {kTOP,kBOTTOM, kLEFT, kRIGHT, kFRONT, kBACK};
template <typename T>
class Wall : public Model
{
public:
	T mNormal;
	T mStartPoint;
	T mEndPoint;
	WallType mType;
	float mC;
public:
	Wall() {}
	Wall(glm::vec2 normal, glm::vec2 startPoint, glm::vec2 endPoint);
	Wall(glm::vec3 normal, glm::vec3 startPoint, glm::vec3 endPoint);
	virtual~Wall() {  }
	void Init(glm::vec2 startPoint, glm::vec2 endPoint);
	void Init();
	void SetShader(Shader* shader);
	
};

#include "VertexData.h"

template<typename T>
Wall<T>::Wall(glm::vec2 normal, glm::vec2 startPoint, glm::vec2 endPoint)
{
	mVAO = nullptr;
	mVBO = nullptr;
	mEBO = nullptr;
	mMaterial = nullptr;
	mDraw = nullptr;
	mNormal = glm::normalize(normal);
	mStartPoint = startPoint;
	mEndPoint = endPoint;
	mC = -glm::dot(mNormal, (mStartPoint + mEndPoint) / 2.0f);
}

template<typename T>
Wall<T>::Wall(glm::vec3 normal, glm::vec3 startPoint, glm::vec3 endPoint)
{
	mVAO = nullptr;
	mVBO = nullptr;
	mEBO = nullptr;
	mMaterial = nullptr;
	mDraw = nullptr;
	mNormal = glm::normalize(normal);
	mStartPoint = startPoint;
	mEndPoint = endPoint;
	mC = -glm::dot(mNormal, (mStartPoint + mEndPoint) / 2.0f);
}

template<typename T>
void Wall<T>::Init(glm::vec2 startPoint, glm::vec2 endPoint)
{
	mDraw = new DrawCall;
	mVAO = new VAO;
	mVAO->Init();
	mVBO = new VBO;
	VertexDataFull* vertices = new VertexDataFull[2];
	vertices[0].mVertex = glm::vec4(startPoint, -2.0f, 1.0f);
	vertices[0].mNormal = glm::vec4(mNormal, 0.0f, 1.0f);
	vertices[1].mVertex = glm::vec4(endPoint, -2.0f, 1.0f);
	vertices[1].mNormal = glm::vec4(mNormal, 0.0f, 1.0f);
	mData = vertices;
	mVertexCount = 2;
	mVBO->SetSize(2);
	mVBO->SubmitData(mData, sizeof(VertexDataFull) * mVertexCount);

	mMaterial = new Material;
	mMaterial->mBaseRenderPass = new RenderPass;

	mDraw->mVAO = mVAO;
	mDraw->mVBO = mVBO;
	mDraw->mMaterial = mMaterial;
}

template<typename T>
inline void Wall<T>::Init()
{
	mDraw = new DrawCall;
	mVAO = new VAO;
	mVAO->Init();
	mVBO = new VBO;

	
	VertexDataFull* vertices = new VertexDataFull[6];
	if (mNormal.y != 0)
	{ 
		vertices[0].mVertex = glm::vec4(mStartPoint.x, mEndPoint.y, mEndPoint.z, 1.0f);
		vertices[1].mVertex = glm::vec4(mEndPoint.x, mStartPoint.y, mStartPoint.z, 1.0f);
		vertices[2].mVertex = glm::vec4(mStartPoint, 1.0f);

		vertices[3].mVertex = glm::vec4(mStartPoint.x, mEndPoint.y, mEndPoint.z, 1.0f);
		vertices[4].mVertex = glm::vec4(mEndPoint, 1.0f);
		vertices[5].mVertex = glm::vec4(mEndPoint.x, mStartPoint.y, mStartPoint.z, 1.0f);

		vertices[0].mNormal = glm::vec4(mNormal,1.0f);
		vertices[1].mNormal = glm::vec4(mNormal,1.0f);
		vertices[2].mNormal = glm::vec4(mNormal,1.0f);
		vertices[3].mNormal = glm::vec4(mNormal,1.0f);
		vertices[4].mNormal = glm::vec4(mNormal,1.0f);
		vertices[5].mNormal = glm::vec4(mNormal,1.0f);
	}
	else if (mNormal.x != 0)
	{
		vertices[0].mVertex = glm::vec4(mEndPoint.x, mStartPoint.y, mEndPoint.z, 1.0f);
		vertices[1].mVertex = glm::vec4(mEndPoint,1.0f);
		vertices[2].mVertex = glm::vec4(mStartPoint, 1.0f);

		vertices[3].mVertex = glm::vec4(mEndPoint, 1.0f);
		vertices[4].mVertex = glm::vec4(mStartPoint.x, mEndPoint.y, mStartPoint.z,1.0f);
		vertices[5].mVertex = glm::vec4(mStartPoint, 1.0f);
		vertices[0].mNormal = glm::vec4(mNormal, 1.0f);
		vertices[1].mNormal = glm::vec4(mNormal, 1.0f);
		vertices[2].mNormal = glm::vec4(mNormal, 1.0f);
		vertices[3].mNormal = glm::vec4(mNormal, 1.0f);
		vertices[4].mNormal = glm::vec4(mNormal, 1.0f);
		vertices[5].mNormal = glm::vec4(mNormal, 1.0f);
	}
	else if (mNormal.z != 0)
	{
		vertices[0].mVertex = glm::vec4(mStartPoint.x, mEndPoint.y, mEndPoint.z, 1.0f);
		vertices[1].mVertex = glm::vec4(mEndPoint.x, mStartPoint.y, mEndPoint.z,1.0f);
		vertices[2].mVertex = glm::vec4(mStartPoint, 1.0f);

		vertices[3].mVertex = glm::vec4(mStartPoint.x, mEndPoint.y, mEndPoint.z, 1.0f);
		vertices[4].mVertex = glm::vec4(mEndPoint, 1.0f);
		vertices[5].mVertex = glm::vec4(mEndPoint.x, mStartPoint.y, mEndPoint.z, 1.0f);
		vertices[0].mNormal = glm::vec4(mNormal, 1.0f);
		vertices[1].mNormal = glm::vec4(mNormal, 1.0f);
		vertices[2].mNormal = glm::vec4(mNormal, 1.0f);
		vertices[3].mNormal = glm::vec4(mNormal, 1.0f);
		vertices[4].mNormal = glm::vec4(mNormal, 1.0f);
		vertices[5].mNormal = glm::vec4(mNormal, 1.0f);
	}
	
	vertices[0].mTexCoord0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	vertices[1].mTexCoord0 = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);
	vertices[2].mTexCoord0 = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	vertices[3].mTexCoord0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	vertices[4].mTexCoord0 = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	vertices[5].mTexCoord0 = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);

	mData = vertices;
	mVertexCount = 6;
	mVBO->SetSize(mVertexCount);
	mVBO->SubmitData(mData, sizeof(VertexDataFull) * mVertexCount);

	mMaterial = new Material;
	mMaterial->mBaseRenderPass = new RenderPass;

	mDraw->mVAO = mVAO;
	mDraw->mVBO = mVBO;
	mDraw->mMaterial = mMaterial;
}

template<typename T>
void Wall<T>::SetShader(Shader* shader)
{
	mMaterial->mBaseRenderPass->SetShader(shader);
}


