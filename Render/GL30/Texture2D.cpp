#include "Texture2D.h"


#include "stb/stb_image.h"

#include "../Builtin/LTC.h"
#include "../Utils/FileIO.h"
std::unordered_map<std::string, Texture2D*> Texture2D::mTextures;

int Texture2D::LoadTexture(const char* name, const char* path)
{
	auto iter = mTextures.find(name);
	if (iter != mTextures.end())
	{
		return iter->second->mTextureID;
	}

	Texture2D* TBO = new Texture2D;
	TBO->CreateTexture2DFromIMG(path);
	mTextures.insert(std::pair<std::string, Texture2D*>(name, TBO));
	return TBO->mTextureID;
}

Texture2D::Texture2D()
{
	mTextureType = GL_TEXTURE_2D;
	mWidth = 0;
	mHeight = 0;
	mTextureID = 0;
	mMinFilter = GL_LINEAR_MIPMAP_LINEAR;
	mMagFilter = GL_LINEAR;
	mFilterT = GL_REPEAT;
	mFilterS = GL_REPEAT;
	mFilterR = GL_REPEAT;
	mMaxLevel = 0;
	mInternalFormat = GL_RGBA;
	mScrFormat;
}

Texture2D::~Texture2D()
{
	std::unordered_map<std::string, Texture2D*>::iterator iter = mTextures.begin();
	if (iter != mTextures.end()) {
		mTextures.erase(iter);
	}
}

unsigned char* Texture2D::DecodeBMP(unsigned char* bmpfile, int& width, int& height)
{
	if (memcmp(bmpfile, "BM", 2) == 0)
	{
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

unsigned char* Texture2D::DecodeIMG(const char* imgfile, int& fileSize, int& width, int& height, int& channel, GLenum& format)
{
	stbi_set_flip_vertically_on_load(true);
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

unsigned int Texture2D::CreateTexture2D(unsigned char* pixelData, int width, int height, GLenum type)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(mTextureType, texture);
	glTexParameteri(mTextureType, GL_TEXTURE_MAG_FILTER, mMagFilter);
	glTexParameteri(mTextureType, GL_TEXTURE_MIN_FILTER, mMinFilter);
	glTexParameteri(mTextureType, GL_TEXTURE_WRAP_S, mFilterS);
	glTexParameteri(mTextureType, GL_TEXTURE_WRAP_T, mFilterT);
	glTexParameteri(mTextureType, GL_TEXTURE_MAX_LEVEL, mMaxLevel);
	glGenerateMipmap(mTextureType);
	for (auto i = 0; i < mMaxLevel + 1; i++)
		glTexImage2D(mTextureType, i, type, width, height, 0, type, GL_UNSIGNED_BYTE, pixelData);
	glBindTexture(mTextureType, 0);
	mTextureID = texture;
	return texture;
}

unsigned int Texture2D::CreateTexture2DFromBMP(const char* path)
{
	int fileSize = 0;
	unsigned char* fileContent = LoadFileContent(path, fileSize);
	if (fileContent == nullptr) {
		return 0;
	}
	int img_width, img_height;
	unsigned char* rgbData = DecodeBMP(fileContent, img_width, img_height);
	if (rgbData == nullptr) {
		delete[] fileContent;
		return 0;
	}
	glGenerateMipmap(mTextureType);
	unsigned int texture = CreateTexture2D(rgbData, img_width, img_height, GL_RGB);
	delete[] fileContent;
	mTextureID = texture;
	return texture;
}

unsigned int Texture2D::CreateTexture2DFromLTC(const float* LTC)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(mTextureType, texture);
	glTexImage2D(mTextureType, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_FLOAT, LTC);
	glTexParameteri(mTextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(mTextureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(mTextureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(mTextureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glBindTexture(mTextureType, 0);
	mTextureID = texture;
	return texture;
}

unsigned int Texture2D::CreateTexture2DFromIMG(const char* path)
{
	int fileSize = 0;
	unsigned char* fileContent = LoadFileContent(path, fileSize);
	if (fileContent == nullptr) {
		return 0;
	}
	int img_width = 0, img_height = 0, img_channels = 0;
	GLenum img_format = GL_RGB;
	unsigned char* img_data = DecodeIMG(path, fileSize, img_width, img_height, img_channels, img_format);
	unsigned int texture = CreateTexture2D(img_data, img_width, img_height, img_format);
	delete[] img_data;
	return texture;
}
