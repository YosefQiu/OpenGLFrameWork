#pragma once
#include "YosefGL.h"
#include "YosefPrefix.h"
#include "Utils/LinkedList.h"
class Attribute : public LinkedList 
{
public:
	int mLocation;
	int mComponentCount;
	int mDataStride;
	int mDataOffset;
	bool mbNormalize;
	unsigned int mBasicDataType;
public:
	Attribute() {}
	Attribute(int location,
			int componentCount,
			unsigned int basicDataType,
			bool normalize,
			int dataStride,
			int dataOffset);
	virtual ~Attribute() {}
public:
	void Active();
};