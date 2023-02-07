#pragma once

#include "../YosefPrefix.h"
#include "../YosefGL.h"
class FBO
{
public:
	GLuint mFrameBufferObject;
	GLint mPrevFrameBuffer;
	std::map<std::string, GLuint> mBuffers;
	std::vector<GLenum> mDrawBuffers;
	int* mViewport;
public:
	FBO();
	void AttachColorBuffer(const char* bufferName, GLenum attachment, int width, int height);
	void AttachDepthBuffer(const char* bufferName, int width, int height);
	void Finish();
	void Bind();
	void Unbind();
	GLuint GetBuffer(const char* bufferName);
};