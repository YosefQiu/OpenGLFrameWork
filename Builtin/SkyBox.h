#pragma once
#include "../GL30/VAO.h"
#include "../GL30/VBO.h"
#include "../GL30/TextureCube.h"
#include "../Material.h"
#include "../VertexData.h"
class Camera;
class SkyBox
{
public:
	SkyBox();
	virtual ~SkyBox();
public:
	VAO* mVAO;
	VBO* mVBO;
	Material* mMaterial;
	VertexDataFull* mData;
	TextureCube* mCubeMap;
public:
	void Init(const char* name);
	void Render(Camera* camera);
};

