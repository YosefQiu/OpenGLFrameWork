#include "DefaultAllocator.h"
#include "tlsf/tlsf.h"
#include "Profiler.h"
#define USE_POOL 1

//1024 1KB
//1024x1024 1MB 1048576
//1024x1024x1024 1GB 1073741824
static unsigned long sReservedTotalMemory = 209715200;//200MB
static unsigned int mReservedSize = 209715200;//200MB
static tlsf_t sTLSF = nullptr;
static bool sbAppQuited = false;
void InitMemory() {
#if USE_POOL
	if (sTLSF == nullptr) {
		void*buffer = malloc(mReservedSize);
		sTLSF = tlsf_create_with_pool(buffer, mReservedSize);
	}
#endif
}
void QuitMemory()
{
	sbAppQuited = true;
}
extern "C" void OnQuitMemory() {
	sbAppQuited = true;
}
static void*GetMemory(size_t size) {
	if (sTLSF==nullptr){
		InitMemory();
	}
	void * ptrMemory = tlsf_malloc(sTLSF, size);
	while (ptrMemory == nullptr) {
		void*add_pool = malloc(104857600);//100MB
		tlsf_add_pool(sTLSF, add_pool, 104857600);
		ptrMemory = tlsf_malloc(sTLSF, size);
	}
	return ptrMemory;
}
static void Recycle(void*ptr) {
	if (sbAppQuited) {
		return;
	}
#if USE_POOL
	if (Profiler::OnFreeObject(ptr)) {
		tlsf_free(sTLSF, ptr);
	}
	else {
		free(ptr);
	}
#else
	free(ptr);
#endif
}

void*operator new(std::size_t size) {
//#if USE_POOL
//	void*ptr = GetMemory(size);
//	Profiler::OnNewObject(ptr, kMemDefaultId,tlsf_block_size(ptr));
//	return ptr;
//#else
	void* ptr = malloc(size);
	return ptr;
//#endif
}

void*operator new(std::size_t size, MemoryLabel memID) {
#if USE_POOL
	void*ptr = GetMemory(size); 
	Profiler::OnNewObject(ptr, memID, tlsf_block_size(ptr));
	return ptr;
#else
	void* ptr = malloc(size);
	return ptr;
#endif
}

void*operator new[](std::size_t size, MemoryLabel memID) {
#if USE_POOL
	void*ptr = GetMemory(size);
	Profiler::OnNewObject(ptr, memID, tlsf_block_size(ptr));
	return ptr;
#else
	void* ptr = malloc(size);
	return ptr;
#endif
}

void operator delete(void*ptr,MemoryLabel memID){
	Recycle(ptr);
}

void operator delete[](void*ptr, MemoryLabel memID){
	Recycle(ptr);
}
void operator delete(void*ptr){
	Recycle(ptr);
}

void operator delete [](void*ptr){
	Recycle(ptr);
}