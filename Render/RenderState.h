#pragma once
#include "YosefGL.h"
#include "YosefPrefix.h"

struct RenderState 
{
	bool mbEnableBlend;
	bool mbEnableDepthTest;
	bool mbEnableAlphaTest;
	bool mbWriteR,mbWriteG,mbWriteB,mbWriteA;
	bool mbWriteDepthBuffer;
	unsigned int mSrcBlendFunc, mDstBlendFunc;
	unsigned int mAlphaTestFunction;
	unsigned int mDepthTestFunction;
	float mAlphaTestAlphaValue;
	unsigned int mDrawFace;
	unsigned int mPolygonMode;
	unsigned int mCurrentProgram;
	RenderState();
};
class GlobalRenderState 
{
protected:
	static RenderState mRenderState;
public:
	static void Init();
	static void SetBlendState(bool enable);
	static void SetBlendFunc(unsigned int src, unsigned int dst);
	static void SetDepthTestState(bool enable);
	static void SetAlphaTestState(bool enable);
	static void SetColorMask(bool r, bool g, bool b, bool a);
	static void SetDepthMask(bool enable);
	static void SetDepthFunc(unsigned int depth_func);
	static void SetCurrentProgram(unsigned int program);
	static void SetPolygonMode(unsigned int face, unsigned int mode);
	static void SetAlphaTest(unsigned int func, float ref_value);
};