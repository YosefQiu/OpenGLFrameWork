#pragma once

#include "../YosefPrefix.h"
#include "../YosefGL.h"

class RBO
{
public:
	GLuint mRenderBufferObject;
	RBO();
	~RBO();
	void Init(int width, int height);
	void Resize(int width, int height);
};