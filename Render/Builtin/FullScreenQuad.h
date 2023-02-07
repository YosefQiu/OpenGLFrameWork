#pragma once
#include "../GL30/VAO.h"
#include "../GL30/VBO.h"
#include "../GL30/EBO.h"
#include "../Material.h"
#include "../VertexData.h"

enum class QuadType : int
{
	kFullScreen,
	kLetfTop,
	kRightTop,
	kLeftBottom,
	kRightBottom,
	kQuadTypeCount
};

class FullScreenQuad
{
public:
	VAO* mVAO;
	VBO* mVBO;
	EBO* mEBO;
	VertexDataFull* mData;
	Shader* mShader;
	Material* mMaterial;
	bool bRenderDepthBuffer = false;
public:
	FullScreenQuad() : mVAO(nullptr), mVBO(nullptr), mEBO(nullptr), mShader(nullptr), mMaterial(nullptr) {}
	virtual ~FullScreenQuad();
public:
	void InitWithBuiltShader();
	void Init(const char* vsPath, const char* fsPath);
	void Render(bool bRenderDepthBuffer = false);
	void Bind(QuadType type = QuadType::kFullScreen);
};

