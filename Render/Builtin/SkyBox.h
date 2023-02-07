#pragma once
#include "../GL30/TextureCube.h"
#include "../model.h"
class Camera;
class SkyBox : public Model
{
public:
	SkyBox();
	virtual ~SkyBox();
public:
	TextureCube* mCubeMap;
public:
	void Init(const char* name);
	void Render(Camera* camera);
};

