#pragma once
#include "../YosefGL.h"
#include "../YosefPrefix.h"

class TextureUnit
{
public:
	GLuint mTextureID;
	GLenum mTextureType;
public:
	TextureUnit();
	virtual ~TextureUnit();
};