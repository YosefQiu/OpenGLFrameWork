#include "VBO.h"
#include "../VertexData.h"

void VBO::SetSize(int vertexCount, GLenum hint) {
	mVertexCount = vertexCount;
	CreateBufferObject(GL_ARRAY_BUFFER, sizeof(VertexDataFull) * vertexCount, hint, nullptr);
}
void VBO::SubmitData(void* data, GLsizeiptr size) {
	UpdateData(GL_ARRAY_BUFFER, size, data);
}