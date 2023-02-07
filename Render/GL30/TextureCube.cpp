#include "TextureCube.h"
#include "../Utils/FileIO.h"
#include "../Debugger/Log.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "../RenderState.h" 

std::unordered_map<std::string, TextureCube*> TextureCube::mTextureCubes;


TextureCube::TextureCube()
{
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
TextureCube* TextureCube::LoadTextureCube(const char* name, const char* path)
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
	TextureCube* TCBO = new TextureCube;
	TCBO->CreateTextureCUBEFromIMG(path);
	mTextureCubes.insert(std::pair<std::string, TextureCube*>(name, TCBO));
	return TCBO;
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

unsigned int TextureCube::CreateTextureCUBEFromIMG(const char* path, const char* type)
{
	int fileSize = 0;
	
	int img_width = 0, img_height = 0, img_channels = 0;
	GLenum img_format = GL_RGB;

	// get the full path
	unsigned char* img_data;
	std::string full_path = std::string(path) + "/front." + type;
	img_data = DecodeIMG(full_path.c_str(), fileSize, img_width, img_height, img_channels, img_format);
	CubeTexturInfo* front = new CubeTexturInfo;
	front->mPixelData = img_data;
	front->mHeight = img_width;
	front->mWidth = img_height;
	front->mFormat = img_format;
	full_path.clear();
	
	full_path = std::string(path) + "/back." + type;
	img_data = DecodeIMG(full_path.c_str(), fileSize, img_width, img_height, img_channels, img_format);
	CubeTexturInfo* back = new CubeTexturInfo;
	back->mPixelData = img_data;
	back->mHeight = img_width;
	back->mWidth = img_height;
	back->mFormat = img_format;
	full_path.clear();
	
	full_path = std::string(path) + "/left." + type;
	img_data = DecodeIMG(full_path.c_str(), fileSize, img_width, img_height, img_channels, img_format);
	CubeTexturInfo* left = new CubeTexturInfo;
	left->mPixelData = img_data;
	left->mHeight = img_width;
	left->mWidth = img_height;
	left->mFormat = img_format;
	full_path.clear();

	full_path = std::string(path) + "/right." + type;
	img_data = DecodeIMG(full_path.c_str(), fileSize, img_width, img_height, img_channels, img_format);
	CubeTexturInfo* right = new CubeTexturInfo;
	right->mPixelData = img_data;
	right->mHeight = img_width;
	right->mWidth = img_height;
	right->mFormat = img_format;
	full_path.clear();

	full_path = std::string(path) + "/top." + type;
	img_data = DecodeIMG(full_path.c_str(), fileSize, img_width, img_height, img_channels, img_format);
	CubeTexturInfo* top = new CubeTexturInfo;
	top->mPixelData = img_data;
	top->mHeight = img_width;
	top->mWidth = img_height;
	top->mFormat = img_format;
	full_path.clear();

	full_path = std::string(path) + "/bottom." + type;
	img_data = DecodeIMG(full_path.c_str(), fileSize, img_width, img_height, img_channels, img_format);
	CubeTexturInfo* bottom = new CubeTexturInfo;
	bottom->mPixelData = img_data;
	bottom->mHeight = img_width;
	bottom->mWidth = img_height;
	bottom->mFormat = img_format;
	full_path.clear();
	
	mFrontRes = front;
	mBackRes = back;
	mLeftRes = left;
	mRightRes = right;
	mTopRes = top;
	mBottomRes = bottom;

	unsigned int texture = CreateTexture2D(img_data, img_width, img_height, img_format);
	delete[] img_data;
	return 0;
}

unsigned char* TextureCube::DecodeIMG(const char* imgfile, int& fileSize, int& width, int& height, int& channel, GLenum& format)
{
	stbi_set_flip_vertically_on_load(false);
	unsigned char* img_data = stbi_load(imgfile, &width, &height, &channel, 0);
	if (img_data)
	{
		if (channel == 1)
			format = GL_RED;
		else if (channel == 3)
			format = GL_RGB;
		else if (channel == 4)
			format = GL_RGBA;
	}
	else
		std::cout << "[ERROR] Load Image " << stbi_failure_reason() << std::endl;
	return img_data;
}

unsigned int TextureCube::CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type)
{
		/*
		** GL_TEXTURE_CUBE_MAP_POSITIVE_X	Right
		** GL_TEXTURE_CUBE_MAP_NEGATIVE_X	Left
		** GL_TEXTURE_CUBE_MAP_POSITIVE_Y	Top
		** GL_TEXTURE_CUBE_MAP_NEGATIVE_Y	Bottom
		** GL_TEXTURE_CUBE_MAP_POSITIVE_Z	Back
		** GL_TEXTURE_CUBE_MAP_NEGATIVE_Z	Front
		*/
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(mTextureType, texture);
	glTexParameteri(mTextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(mTextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(mTextureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(mTextureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(mTextureType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, mFrontRes->mFormat, mFrontRes->mWidth, mFrontRes->mHeight, 0, mFrontRes->mFormat, GL_UNSIGNED_BYTE, mFrontRes->mPixelData);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, mBackRes->mFormat, mBackRes->mWidth, mBackRes->mHeight, 0, mBackRes->mFormat, GL_UNSIGNED_BYTE, mBackRes->mPixelData);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, mLeftRes->mFormat, mLeftRes->mWidth, mLeftRes->mHeight, 0, mLeftRes->mFormat, GL_UNSIGNED_BYTE, mLeftRes->mPixelData);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, mRightRes->mFormat, mRightRes->mWidth, mRightRes->mHeight, 0, mRightRes->mFormat, GL_UNSIGNED_BYTE, mRightRes->mPixelData);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, mTopRes->mFormat, mTopRes->mWidth, mTopRes->mHeight, 0, mTopRes->mFormat, GL_UNSIGNED_BYTE, mTopRes->mPixelData);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, mBottomRes->mFormat, mBottomRes->mWidth, mBottomRes->mHeight, 0, mBottomRes->mFormat, GL_UNSIGNED_BYTE, mBottomRes->mPixelData);
	glBindTexture(mTextureType, 0);
	mTextureID = texture;
	return texture;
}
