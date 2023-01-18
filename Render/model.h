#pragma once
#include "YosefGL.h"
#include "YosefPrefix.h"
class Model {
public:
	void * mData;
	int mVertexCount;

public:
	Model();
	void Init(const char*modelPath);
};