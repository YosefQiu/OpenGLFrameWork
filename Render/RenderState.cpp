#include "RenderState.h"

#define UpdateBlendState(enable) \
do{\
enable?glEnable(GL_BLEND):glDisable(GL_BLEND); \
}while(0)
#define UpdateDepthTestState(enable) \
do{\
enable?glEnable(GL_DEPTH_TEST):glDisable(GL_DEPTH_TEST); \
}while(0)
#define UpdateAlphaTestState(enable) \
do{\
enable?glEnable(GL_ALPHA_TEST):glDisable(GL_ALPHA_TEST); \
}while(0)
RenderState::RenderState() {
	mbEnableBlend =false;
	mbEnableDepthTest=true;
	mbEnableAlphaTest=false;
	mbWriteR = true;
	mbWriteG = true;
	mbWriteB = true;
	mbWriteA = true;
	mbWriteDepthBuffer = true;
	mSrcBlendFunc = GL_SRC_ALPHA;
	mDstBlendFunc = GL_ONE_MINUS_SRC_ALPHA;
	mAlphaTestFunction=GL_GREATER;
	mDepthTestFunction=GL_LEQUAL;
	mAlphaTestAlphaValue=0.1f;
	mDrawFace = GL_FRONT_AND_BACK;
	mPolygonMode=GL_FILL;
	mCurrentProgram = 0;
	mTextureIndex = 0;
	mPolygon = GL_TRIANGLES;
}
RenderState GlobalRenderState::mRenderState;
void GlobalRenderState::Init() {
	UpdateBlendState(mRenderState.mbEnableBlend);
	UpdateDepthTestState(mRenderState.mbEnableDepthTest);
	UpdateAlphaTestState(mRenderState.mbEnableAlphaTest);
	glBlendFunc(mRenderState.mSrcBlendFunc, mRenderState.mDstBlendFunc);
	glColorMask(mRenderState.mbWriteR, mRenderState.mbWriteG, mRenderState.mbWriteB, mRenderState.mbWriteA);
	glDepthMask(mRenderState.mbWriteDepthBuffer);
	glDepthFunc(mRenderState.mDepthTestFunction);
	glUseProgram(mRenderState.mCurrentProgram);
	glPolygonMode(mRenderState.mDrawFace, mRenderState.mPolygonMode);
	glAlphaFunc(mRenderState.mAlphaTestFunction, mRenderState.mAlphaTestAlphaValue);
}
void GlobalRenderState::SetBlendState(bool enable) {
	if (mRenderState.mbEnableBlend!=enable){
		mRenderState.mbEnableBlend = enable;
		UpdateBlendState(mRenderState.mbEnableBlend);
	}
}
void GlobalRenderState::SetBlendFunc(unsigned int src, unsigned int dst) {
	if (mRenderState.mSrcBlendFunc!=src || mRenderState.mDstBlendFunc!=dst){
		mRenderState.mSrcBlendFunc = src;
		mRenderState.mDstBlendFunc = dst;
		glBlendFunc(mRenderState.mSrcBlendFunc, mRenderState.mDstBlendFunc);
	}
}
void GlobalRenderState::SetDepthTestState(bool enable) {
	/*if (mRenderState.mbEnableDepthTest != enable) {
		mRenderState.mbEnableDepthTest = enable;
		UpdateDepthTestState(mRenderState.mbEnableDepthTest);
	}*/

	mRenderState.mbEnableDepthTest = enable;
	if (enable == true)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}
void GlobalRenderState::SetAlphaTestState(bool enable) {
	if (mRenderState.mbEnableAlphaTest != enable) {
		mRenderState.mbEnableAlphaTest = enable;
		UpdateAlphaTestState(mRenderState.mbEnableAlphaTest);
	}
}
void GlobalRenderState::SetColorMask(bool r, bool g, bool b, bool a) {
	if (mRenderState.mbWriteR != r || mRenderState.mbWriteG != g || mRenderState.mbWriteB != b || mRenderState.mbWriteA != a) {
		mRenderState.mbWriteR = r;
		mRenderState.mbWriteG = g;
		mRenderState.mbWriteB = b;
		mRenderState.mbWriteA = a;
		glColorMask(mRenderState.mbWriteR, mRenderState.mbWriteG, mRenderState.mbWriteB, mRenderState.mbWriteA);
	}
}
void GlobalRenderState::SetDepthMask(bool enable) {
	if (mRenderState.mbWriteDepthBuffer!=enable){
		mRenderState.mbWriteDepthBuffer = enable;
		glDepthMask(mRenderState.mbWriteDepthBuffer);
	}
}
void GlobalRenderState::SetDepthFunc(unsigned int depth_func) {
	if (mRenderState.mDepthTestFunction!=depth_func){
		mRenderState.mDepthTestFunction = depth_func;
		glDepthFunc(mRenderState.mDepthTestFunction);
	}
}
void GlobalRenderState::SetCurrentProgram(unsigned int program) {
	if (mRenderState.mCurrentProgram!=program){
		mRenderState.mCurrentProgram = program;
		glUseProgram(mRenderState.mCurrentProgram);
	}
}
void GlobalRenderState::SetPolygonMode(unsigned int face, unsigned int mode) {
	if (mRenderState.mDrawFace!=face||mRenderState.mPolygonMode!=mode){
		mRenderState.mDrawFace = face;
		mRenderState.mPolygonMode = mode;
		glPolygonMode(mRenderState.mDrawFace, mRenderState.mPolygonMode);
	}
}
void GlobalRenderState::SetAlphaTest(unsigned int func, float ref_value) {
	if (mRenderState.mAlphaTestFunction!=func||mRenderState.mAlphaTestAlphaValue!=ref_value){
		mRenderState.mAlphaTestFunction = func;
		mRenderState.mAlphaTestAlphaValue = ref_value;
		glAlphaFunc(mRenderState.mAlphaTestFunction, mRenderState.mAlphaTestAlphaValue);
	}
}

void GlobalRenderState::SetPolygon(GLenum polygon)
{
	mRenderState.mPolygon = polygon;
}
void GlobalRenderState::EnableTextureUnit()
{
	if (mRenderState.mTextureIndex >= 15)
		mRenderState.mTextureIndex = 0;
	glActiveTexture(GL_TEXTURE0 + mRenderState.mTextureIndex++);
}

int GlobalRenderState::GetTextureUnit()
{
	int index = mRenderState.mTextureIndex;
	index--;
	return index;
}