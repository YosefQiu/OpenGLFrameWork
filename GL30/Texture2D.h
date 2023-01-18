#pragma once
#include "TextureUnit.h"

class Texture2D : public TextureUnit
{
public:
	GLenum mMinFilter;
	GLenum mMagFilter;
	GLenum mFilterT;
	GLenum mFilterS;
	GLenum mFilterR;
	GLenum mInternalFormat;
	GLenum mScrFormat;
	GLuint mWidth;
	GLuint mHeight;
	static std::unordered_map<std::string, Texture2D*> mTextures;
public:
	Texture2D();
	virtual ~Texture2D();
public:
	unsigned char* DecodeBMP(unsigned char* bmpfile, int& width, int& height);
	unsigned char* DecodeIMG(unsigned char* imgfile, int& fileSize, int& width, int& height, int& channel, GLenum& format);
	unsigned int CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type);
	unsigned int CreateTexture2DFromBMP(const char* path);
	unsigned int CreateTexture2DFromLTC(const float* LTC);
	unsigned int CreateTexture2DFromIMG(const char* path);
};
