#pragma once
#include "../GL30/VAO.h"
#include "../GL30/VBO.h"
#include "../GL30/TextureCube.h"
#include "../Material.h"
#include "../VertexData.h"
class Camera;
class Ground
{
public:
	Ground();
	virtual ~Ground();
public:
	VAO* mVAO;
	VBO* mVBO;
	Material* mMaterial;
	VertexDataFull* mData;
public:
	void Init();
	void Render(Camera* camera);
};

