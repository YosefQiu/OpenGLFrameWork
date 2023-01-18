#include "Debugger.h"
#include "Log.h"
#include "../External/freeglut/include/GL/freeglut.h"
#pragma comment(lib,"glu32.lib")
void CheckLastOpenGLError(const char* file, long line, const char* operation)
{
	GLenum glerr;
	while ((glerr = glGetError()) != GL_NO_ERROR) 
	{
		switch (glerr) {
		case GL_INVALID_VALUE:
			Debug("%s GL_INVALID_VALUE", operation);
			break;
		case GL_INVALID_ENUM:
			Debug("%s GL_INVALID_ENUM", operation); 
			break;
		case GL_INVALID_OPERATION: 
			Debug("%s GL_INVALID_OPERATION", operation);
			break;
		case GL_STACK_OVERFLOW:               
			Debug("%s GL_STACK_OVERFLOW", operation);
			break;
		case GL_STACK_UNDERFLOW:
			Debug("%s GL_STACK_UNDERFLOW", operation);
			break;
		case GL_OUT_OF_MEMORY:
			Debug("%s GL_OUT_OF_MEMORY", operation);
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			Debug("%s GL_INVALID_FRAMEBUFFER_OPERATION", operation);
			break;
		default:
			Debug("gl error  0x%x", (int)glerr);
			break;
		}
#if _DEBUG
		std::string str = file;
		const int kMaxErrors = 10;
		int counter = 0;
		int pos = str.find_last_of('\\');
		printf("%s:%ld :", str.substr(pos + 1, str.length() - pos).c_str(), line);
		const char* gluMsg = (const char*)(gluErrorString(glerr));
		if (gluMsg) 
		{
			Error("%s %s", operation, gluMsg);
		}
		else {
			Error("%s 0x%x", operation, glerr);
		}
		++counter;
		if (counter > kMaxErrors) {
			Debug("[ERROR] OnpenGL ERROR count exceeds %i, stop reporting errors\n", kMaxErrors);
			return;
		}
#endif
	}
}

void DumpStr(const char* src)
{
	int nLen = strlen(src);
	Debug("dump str len %d", nLen);
	int i = 0;

	while (i < nLen) {
		printf("%d%d%d%d%d%d%d%d\n", ((*src) & 0x80) >> 7, ((*src) & 0x40) >> 6, ((*src) & 0x20) >> 5, ((*src) & 0x10) >> 4, ((*src) & 0x08) >> 3, ((*src) & 0x04) >> 2, ((*src) & 0x02) >> 1, (*src) & 0x01);
		src++;
		i++;
	}
}
void DumpByte(const char* src, int len) 
{
	int i = 0;
	while (i < len)
	{
		printf("%d%d%d%d%d%d%d%d\n", ((*src) & 0x80) >> 7, ((*src) & 0x40) >> 6, ((*src) & 0x20) >> 5, ((*src) & 0x10) >> 4, ((*src) & 0x08) >> 3, ((*src) & 0x04) >> 2, ((*src) & 0x02) >> 1, (*src) & 0x01);
		src++;
		i++;
	}
}