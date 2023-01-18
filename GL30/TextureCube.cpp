#include "TextureCube.h"
#include "../Utils/FileIO.h"
#include "../Debugger/Log.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "../RenderState.h" 

std::unordered_map<std::string, TextureCube*> TextureCube::mTextureCubes;


TextureCube::TextureCube()
{
	glGenTextures(1, &mTextureID);
	mTextureType = GL_TEXTURE_CUBE_MAP;
	mFrontRes = nullptr;
	mBackRes = nullptr;
	mLeftRes = nullptr;
	mRightRes = nullptr;
	mTopRes = nullptr;
	mBottomRes = nullptr;
}

TextureCube::~TextureCube()
{
	std::unordered_map<std::string, TextureCube*>::iterator iter = mTextureCubes.begin();
	if (iter != mTextureCubes.end())
	{
		mTextureCubes.erase(iter);
	}
}
TextureCube* TextureCube::LoadTextureCube(const char* name)
{
	if (name == nullptr || strlen(name) == 0)
	{
		return nullptr;
	}
	
	std::unordered_map<std::string, TextureCube*>::iterator iter = mTextureCubes.find(name);
	if (iter != mTextureCubes.end())
	{
		return iter->second;
	}
	
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	int nFileSize = 0, width = 0, height = 0;
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	char temp[256];
	memset(temp, 0, 256);
	strcpy_s(temp, 256, name);
	strcat_s(temp, 256, "/front.bmp");
	unsigned char* bmpFileContent = LoadFileContent(temp, nFileSize);
	unsigned char* pixelData = DecodeBMP(bmpFileContent, width, height);
	// front - negative z
	CubeTexturInfo* front = new CubeTexturInfo;
	front->mPixelData = pixelData;
	front->mHeight = height;
	front->mWidth = width;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, front->mWidth, front->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, front->mPixelData);
	delete bmpFileContent;
	
	memset(temp, 0, 256);
	strcpy_s(temp, 256, name);
	strcat_s(temp, 256, "/back.bmp");
	bmpFileContent = LoadFileContent(temp, nFileSize);
	pixelData = DecodeBMP(bmpFileContent, width, height);
	// back positive z
	CubeTexturInfo* back = new CubeTexturInfo;
	back->mPixelData = pixelData;
	back->mHeight = height;
	back->mWidth = width;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, back->mWidth, back->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, back->mPixelData);
	delete bmpFileContent;

	memset(temp, 0, 256);
	strcpy_s(temp, 256, name);
	strcat_s(temp, 256, "/left.bmp");
	bmpFileContent = LoadFileContent(temp, nFileSize);
	// left negative x
	CubeTexturInfo* left = new CubeTexturInfo;
	left->mPixelData = pixelData;
	left->mHeight = height;
	left->mWidth = width;
	pixelData = DecodeBMP(bmpFileContent, width, height);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, left->mWidth, left->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, left->mPixelData);
	delete bmpFileContent;

	memset(temp, 0, 256);
	strcpy_s(temp, 256, name);
	strcat_s(temp, 256, "/right.bmp");
	bmpFileContent = LoadFileContent(temp, nFileSize);
	pixelData = DecodeBMP(bmpFileContent, width, height);
	// right positive x
	CubeTexturInfo* right = new CubeTexturInfo;
	right->mPixelData = pixelData;
	right->mHeight = height;
	right->mWidth = width;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, right->mWidth, right->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, right->mPixelData);
	delete bmpFileContent;

	memset(temp, 0, 256);
	strcpy_s(temp, 256, name);
	strcat_s(temp, 256, "/top.bmp");
	bmpFileContent = LoadFileContent(temp, nFileSize);
	pixelData = DecodeBMP(bmpFileContent, width, height);
	// top positive y
	CubeTexturInfo* top = new CubeTexturInfo;
	top->mPixelData = pixelData;
	top->mHeight = height;
	top->mWidth = width;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, top->mWidth, top->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, top->mPixelData);
	delete bmpFileContent;

	memset(temp, 0, 256);
	strcpy_s(temp, 256, name);
	strcat_s(temp, 256, "/bottom.bmp");
	bmpFileContent = LoadFileContent(temp, nFileSize);
	pixelData = DecodeBMP(bmpFileContent, width, height);
	// top negative y
	CubeTexturInfo* bottom = new CubeTexturInfo;
	bottom->mPixelData = pixelData;
	bottom->mHeight = height;
	bottom->mWidth = width;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, bottom->mWidth, bottom->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bottom->mPixelData);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	delete bmpFileContent;
	TextureCube* textureCube = new TextureCube;
	textureCube->mFrontRes = front;
	textureCube->mBackRes = back;
	textureCube->mLeftRes = left;
	textureCube->mRightRes = right;
	textureCube->mTopRes = top;
	textureCube->mBottomRes = bottom;
	textureCube->mTextureID = texture;
	mTextureCubes.insert(std::pair<std::string, TextureCube*>(name, textureCube));
	return textureCube;
}



unsigned char* TextureCube::DecodeBMP(unsigned char* bmpfile, int& width, int& height)
{
	if (memcmp(bmpfile, "BM", 2) == 0) {
		int pixel_bgr_data_offset = *((int*)(bmpfile + 10));
		width = *((int*)(bmpfile + 18));
		height = *((int*)(bmpfile + 22));
		unsigned char* bgr_data = bmpfile + pixel_bgr_data_offset;
		for (int i = 0; i < width * height; i++) {
			int current_pixel_index = i * 3;
			unsigned char b = bgr_data[current_pixel_index + 0];
			unsigned char r = bgr_data[current_pixel_index + 2];
			bgr_data[current_pixel_index + 0] = r;
			bgr_data[current_pixel_index + 2] = b;
		}
		return bgr_data;
	}
	return nullptr;
}
