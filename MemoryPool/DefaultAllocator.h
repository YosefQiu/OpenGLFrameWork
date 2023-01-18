#pragma once
#include <new>
#include "MemoryLabel.h"
#define ALICE_ALIGN 4
#define ALICE_ADJUST_MEMORY_SIZE(size) ((size + (ALICE_ALIGN - 1)) & ~(ALICE_ALIGN - 1))
void*operator new(std::size_t size);
void*operator new(std::size_t size, MemoryLabel memID);
void*operator new[](std::size_t size, MemoryLabel memID);
void InitMemory();
void QuitMemory();
void operator delete[](void*ptr);
void operator delete(void*ptr);
void operator delete(void*ptr, MemoryLabel memID);
void operator delete[](void*ptr, MemoryLabel memID);