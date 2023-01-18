#include "Light.h"
Light*Light::mMainLight = nullptr;
std::unordered_set<Light*> Light::mLights;
Light::Light()
{
	mType = kLightTypeDirectional;
}
void Light::SetAmbientColor(float r, float g, float b, float a) {
	mAmbient[0] = r;
	mAmbient[1] = g;
	mAmbient[2] = b;
	mAmbient[3] = a;
}
void Light::SetDiffuseColor(float r, float g, float b, float a) {
	mDiffuse[0] = r;
	mDiffuse[1] = g;
	mDiffuse[2] = b;
	mDiffuse[3] = a;
}
void Light::SetSpecularColor(float r, float g, float b, float a) {
	mSpecular[0] = r;
	mSpecular[1] = g;
	mSpecular[2] = b;
	mSpecular[3] = a;
}
void Light::SetSetting0(float x, float y, float z, float w) {
	mSetting0[0] = x;
	mSetting0[1] = y;
	mSetting0[2] = z;
	mSetting0[3] = w;
}
void Light::SetSetting1(float x, float y, float z, float w) {
	mSetting1[0] = x;
	mSetting1[1] = y;
	mSetting1[2] = z;
	mSetting1[3] = w;
}