#include "BufferObject.h"
#include "../Debugger/Debugger.h"
#include "../Debugger/Log.h"
BufferObject::BufferObject() {
	mName = 0;
	mType = GL_ARRAY_BUFFER;
}
BufferObject::~BufferObject() {
	if (mName != 0) {
		glDeleteBuffers(1, &mName);
	}
}
GLuint BufferObject::CreateBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void* data /* = nullptr */) {
	mType = bufferType;
	glGenBuffers(1, &mName);
	glBindBuffer(bufferType, mName);
	glBufferData(bufferType, size, data, usage);
	glBindBuffer(bufferType, 0);
	return mName;
}
void BufferObject::UpdateData(GLenum bufferType, GLsizeiptr size, void* data /* = nullptr */) {
	glBindBuffer(bufferType, mName);
	glBufferSubData(bufferType, 0, size, data);
	glBindBuffer(bufferType, 0);
}
void BufferObject::Bind() {
	glBindBuffer(mType, mName);
}
void BufferObject::UnBind() {
	glBindBuffer(mType, 0);
}