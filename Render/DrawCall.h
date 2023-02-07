#pragma once
#include "YosefGL.h"
#include "YosefPrefix.h"
#include "Utils/LinkedList.h"
#include "Material.h"
#include "GL30/VBO.h"
#include "GL30/EBO.h"
#include "GL30/VAO.h"
#include "Camera.h"
class DrawCall :public LinkedList
{
public:
	Material* mMaterial;
	VAO* mVAO;
	VBO* mVBO;
	EBO* mEBO;
	DrawCall();
	void Draw(Camera* camera, GLenum polygon = GL_TRIANGLES);
};