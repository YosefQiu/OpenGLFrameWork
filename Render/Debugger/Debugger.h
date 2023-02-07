#pragma once
#include "../YosefGL.h"


void CheckLastOpenGLError(const char* file, long line, const char* operation);
#if _DEBUG
#define OGL_CALL(op) do { op; CheckLastOpenGLError(__FILE__, __LINE__,#op); } while(0)
#else
#define OGL_CALL(op) op;
#endif
void DumpStr(const char* src);
void DumpByte(const char* src, int len);
