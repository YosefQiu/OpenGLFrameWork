#pragma once

#include "YosefGL.h"
#include "YosefPrefix.h"
enum LightType
{
	kLightTypeDirectional,
	kLightTypePoint,
	kLightTypeSpot,
	kLightTypeCount
};
// : gameobject position -> light position
class Light
{
public:
	LightType mType;
	unsigned int mCullingMask;
	float mAmbient[4], mDiffuse[4], mSpecular[4];
	float mSetting0[4], mSetting1[4];// different setting parameters of different lights
	Light();
public:
	void SetAmbientColor(float r, float g, float b, float a);
	void SetDiffuseColor(float r, float g, float b, float a);
	void SetSpecularColor(float r, float g, float b, float a);
	void SetSetting0(float x, float y, float z, float w);
	void SetSetting1(float x, float y, float z, float w);
	static Light* mMainLight;
	static std::unordered_set<Light*> mLights;//light culling  2D / 3D
};