#pragma once
#include "TextureUnit.h"

struct CubeTexturInfo
{
	unsigned char* mPixelData;
	int mWidth;
	int mHeight;
	int mChannels;
	CubeTexturInfo()
	{
		mPixelData = nullptr;
		mWidth = -1;
		mHeight = -1;
		mChannels = -1;
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
	static TextureCube* LoadTextureCube(const char* name);
	static std::unordered_map<std::string, TextureCube*> mTextureCubes;
	void InitTextureCube();
private:
	static unsigned char* DecodeBMP(unsigned char* bmpfile, int& width, int& height);
};