#include "tlsf/tlsf.h"
#include "DefaultAllocator.h"
#include "Profiler.h"
#include <map>


	//all the objects that use memory pool
	static std::map<MemoryLabel, int> sUsedMemorySize;
	std::unordered_map<void*, MemoryLabel> Profiler::mObjects;//pointer to memory label
	std::unordered_map<void*, size_t> Profiler::mObjectsSize;//memory size
	static int sTotalUsedMemorySize = 0;

	void Profiler::OnNewObject(void*ptr, MemoryLabel label, size_t size) {
		mObjects.insert(std::pair<void*,MemoryLabel>(ptr,label));
		mObjectsSize.insert(std::pair<void*,size_t>(ptr,size));
		sTotalUsedMemorySize += size;
		if (sUsedMemorySize.find(label) != sUsedMemorySize.end()) {
			sUsedMemorySize[label] += size;
		}
		else {
			sUsedMemorySize[label] = size;
		}
	}

	bool Profiler::OnFreeObject(void*ptr){
		std::unordered_map<void*, MemoryLabel>::iterator iter = mObjects.find(ptr);
		if (iter!=mObjects.end()){
			auto memorySizeIter = mObjectsSize.find(ptr);
			int size = memorySizeIter->second;
			sUsedMemorySize[iter->second] -= size;
			sTotalUsedMemorySize -= size;
			mObjectsSize.erase(memorySizeIter);
			mObjects.erase(iter);
			return true;
		}
		return false;
	}

	int Profiler::GetTotalUsedMemorySize()
	{
		return sTotalUsedMemorySize;
	}
