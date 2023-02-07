#include "RBO.h"
#include "../Debugger/Debugger.h"
#include "../Debugger/Log.h"
RBO::RBO() 
{
	OGL_CALL(glGenRenderbuffers(1, &mRenderBufferObject));
}

RBO::~RBO()
{
	OGL_CALL(glDeleteRenderbuffers(1, &mRenderBufferObject));
}

void RBO::Init(int width, int height)
{
	OGL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, mRenderBufferObject));
	OGL_CALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
	OGL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}
void RBO::Resize(int width, int height)
{
	OGL_CALL(glDeleteRenderbuffers(1, &mRenderBufferObject));
	Init(width, height);
}