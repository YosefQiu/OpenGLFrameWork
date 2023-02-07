#pragma once
#include "YosefGL.h"
#include "YosefPrefix.h"

enum class VertexDataType : int {
	kVertexDataTypeFull,
	kVertexDataTypeES20Full,
	kVertexDataTypeES30Full,
	kVertexDataTypeCount
};



struct VertexDataFull
{
	// ** the memory size of each one member is 16 bytes
	// ** total 80 bytes
	// ** default vertex data format
	glm::vec4 mVertex = glm::vec4(1.0f);
	glm::vec4 mTexCoord0 = glm::vec4(1.0f);
	glm::vec4 mNormal = glm::vec4(1.0f);
	glm::vec4 mTangent = glm::vec4(1.0f);
	glm::vec4 mTexCoord1 = glm::vec4(1.0f);
};

struct VertexDataES20_Full
{
	// ** the memory size of each one member is 16 bytes
	// ** total 128 bytes
	// ** opengl es 2.0 max attribute count 8
	glm::vec4 mVertex;
	glm::vec4 mTexCoord0;
	glm::vec4 mNormal;
	glm::vec4 mTangent;
	glm::vec4 mTexCoord1;
	glm::vec4 mTexCoord2;
	glm::vec4 mTexCoord3;
	glm::vec4 mTexCoord4;
};

struct VertexDataES30_Full
{
	// ** the memory size of each one member is 16 bytes
	// ** total 256 bytes
	// ** opengl es 3.0 max attribute count 16
	glm::vec4 mVertex;
	glm::vec4 mTexCoord0;
	glm::vec4 mNormal;
	glm::vec4 mTangent;
	glm::vec4 mTexCoord1;
	glm::vec4 mTexCoord2;
	glm::vec4 mTexCoord3;
	glm::vec4 mTexCoord4;
	glm::vec4 mTexCoord5;
	glm::vec4 mTexCoord6;
	glm::vec4 mTexCoord7;
	glm::vec4 mTexCoord8;
	glm::vec4 mTexCoord9;
	glm::vec4 mTexCoord10;
	glm::vec4 mTexCoord11;
	glm::vec4 mTexCoord12;
};

VertexDataFull* GetTriangle();

#define VertexDataLength	sizeof(VertexDataFull)
#define VertexData20Length  sizeof(VertexDataFull)
#define VertexData30Length  sizeof(VertexDataFull)