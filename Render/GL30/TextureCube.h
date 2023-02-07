#pragma once
#include "TextureUnit.h"

struct CubeTexturInfo
{
	unsigned char* mPixelData;
	int mWidth;
	int mHeight;
	int mChannels;
	GLenum mFormat;
	CubeTexturInfo()
	{
		mPixelData = nullptr;
		mWidth = -1;
		mHeight = -1;
		mChannels = -1;
		mFormat = GL_RGB;
	}
};

class TextureCube : public TextureUnit
{
public:
	TextureCube();
	virtual ~TextureCube();
public:
	std::string mName;
	GLenum mMinFilter;
	GLenum mMagFilter;
	GLenum mFilterT;
	GLenum mFilterS;
	GLenum mInternalFormat;
	GLenum mSrcFormat;
	GLuint mWidth;
	GLuint mHeight;
	CubeTexturInfo *mLeftRes, *mRightRes, *mFrontRes, *mBackRes, *mTopRes, *mBottomRes;
public:
	static TextureCube* LoadTextureCube(const char* name, const char* path);
	static std::unordered_map<std::string, TextureCube*> mTextureCubes;
	void InitTextureCube();
private:
	static unsigned char* DecodeBMP(unsigned char* bmpfile, int& width, int& height);
	unsigned int CreateTextureCUBEFromIMG(const char* path, const char* type = "jpg");
	unsigned char* DecodeIMG(const char* imgfile, int& fileSize, int& width, int& height, int& channel, GLenum& format);
	unsigned int CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type);
};