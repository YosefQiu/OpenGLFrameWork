#pragma once
#include "BufferObject.h"

class EBO :public BufferObject {
public:
	void SetSize(int indexCount, GLenum hint = GL_STATIC_DRAW);
};