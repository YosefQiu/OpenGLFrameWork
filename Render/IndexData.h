#pragma once
#include "YosefPrefix.h"
#include "YosefGL.h"

class IndexData
{
public:
	IndexData() {}
	IndexData(YosefUInt16 size = 0);
	virtual ~IndexData();
public:
	YosefSInt32		mSize;
	YosefSInt32		mBufferSize;
	YosefUInt16*	mIndexes;
public:
	void Init(YosefUInt16 size);
};

