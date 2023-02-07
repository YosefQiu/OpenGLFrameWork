#include "EBO.h"
#include "../IndexData.h"

void EBO::SetSize(int indexCount, GLenum hint /* = GL_STATIC_DRAW */) {
	CreateBufferObject(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * indexCount, hint, nullptr);
}