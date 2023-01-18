
#include "VAO.h"
#include "../Debugger/Debugger.h"
#include "../Debugger/Log.h"
VAO::VAO()
{
	mIdentifier = 0;
}

VAO::~VAO()
{
	if (mIdentifier != 0)
		OGL_CALL(glDeleteBuffers(1, &mIdentifier));
}

void VAO::Init()
{
	if (mIdentifier != 0)
		OGL_CALL(glDeleteBuffers(1, &mIdentifier));
	
	glGenVertexArrays(1, &mIdentifier);
	glBindVertexArray(mIdentifier);
}

bool VAO::Active()
{
	if (mIdentifier == 0)return false;
	glBindVertexArray(mIdentifier);
	return true;
}

bool VAO::Restore()
{
	if (mIdentifier == 0)return false;
	glBindVertexArray(0);
	return true;
}

void VAO::Bind()
{
	Active();
	//glBindVertexArray(mIdentifier);
}

void VAO::UnBind()
{
	Restore();
	glBindVertexArray(0);
}
