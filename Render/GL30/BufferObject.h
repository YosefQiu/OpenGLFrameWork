#pragma once

#include "../YosefPrefix.h"
#include "../YosefGL.h"
class BufferObject {
public:
	GLuint mName;
	GLenum mType;
	BufferObject();
	virtual ~BufferObject();
	GLuint CreateBufferObject(GLenum bufferType, GLsizeiptr size, GLenum usage, void* data = nullptr);
	void UpdateData(GLenum bufferType, GLsizeiptr size, void* data = nullptr);
	void Bind();
	void UnBind();
};