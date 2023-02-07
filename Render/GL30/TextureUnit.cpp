#include "TextureUnit.h"

TextureUnit::TextureUnit()
{
	mTextureID = 0;
	mTextureType = GL_NONE;
}

TextureUnit::~TextureUnit()
{
	if (mTextureID != 0)
		glDeleteTextures(1, &mTextureID);
}
