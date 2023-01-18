#include "MaterialProperty.h"
MaterialProperty::MaterialProperty(MaterialUniformPropertyType t, const char* name) {
	mType = t;
	memset(mName, 0, 64);
	strcpy(mName, name);
}
MaterialPropertyMatrix4::MaterialPropertyMatrix4(const char* name) :MaterialProperty(kMaterialUniformPropertyTypeMatrix4, name)
{
	mPropertyValue = nullptr;
}
MaterialPropertyMatrix3::MaterialPropertyMatrix3(const char* name) : MaterialProperty(kMaterialUniformPropertyTypeMatrix3, name) 
{
	mPropertyValue = nullptr;
}
MaterialPropertyMatrix2::MaterialPropertyMatrix2(const char* name) : MaterialProperty(kMaterialUniformPropertyTypeMatrix2, name)
{
	mPropertyValue = nullptr;
}
MaterialPropertyVec4::MaterialPropertyVec4(const char* name) : MaterialProperty(kMaterialUniformPropertyTypeVec4, name)
{
	mPropertyValue = nullptr;
}
MaterialPropertyVec3::MaterialPropertyVec3(const char* name) : MaterialProperty(kMaterialUniformPropertyTypeVec3, name)
{
	mPropertyValue = nullptr;
}
MaterialPropertyVec2::MaterialPropertyVec2(const char* name) : MaterialProperty(kMaterialUniformPropertyTypeVec2, name)
{
	mPropertyValue = nullptr;
}
MaterialPropertyFloat::MaterialPropertyFloat(const char* name) : MaterialProperty(kMaterialUniformPropertyTypeFloat, name)
{
	mPropertyValue = -1.0f;
}
MaterialPropertyInt::MaterialPropertyInt(const char* name) : MaterialProperty(kMaterialUniformPropertyTypeInt, name)
{
	mPropertyValue = -1;
}
MaterialPropertyBool::MaterialPropertyBool(const char* name) : MaterialProperty(kMaterialUniformPropertyTypeBool, name)
{
	mPropertyValue = false;
}

MaterialPropertySampler2D::MaterialPropertySampler2D(const char* name) : MaterialProperty(kMaterialUniformPropertyTypeSampler2D, name) 
{
	mTextureName = 0;
}

MaterialPropertySamplerCube::MaterialPropertySamplerCube(const char* name) : MaterialProperty(kMaterialUniformPropertyTypeSampler2D, name)
{
	mTextureName = 0;
}

MaterialProperty* MaterialPropertyMatrix4::Clone() 
{
	MaterialPropertyMatrix4* ret = new MaterialPropertyMatrix4(mName);
	ret->mPropertyValue = mPropertyValue;
	return ret;
}
MaterialProperty* MaterialPropertyMatrix3::Clone() 
{
	MaterialPropertyMatrix3* ret = new MaterialPropertyMatrix3(mName);
	ret->mPropertyValue = mPropertyValue;
	return ret;
}
MaterialProperty* MaterialPropertyMatrix2::Clone()
{
	MaterialPropertyMatrix2* ret = new MaterialPropertyMatrix2(mName);
	ret->mPropertyValue = mPropertyValue;
	return ret;
}
MaterialProperty* MaterialPropertyVec4::Clone() 
{
	MaterialPropertyVec4* ret = new MaterialPropertyVec4(mName);
	ret->mPropertyValue = mPropertyValue;
	return ret;
}
MaterialProperty* MaterialPropertyVec3::Clone()
{
	MaterialPropertyVec3* ret = new MaterialPropertyVec3(mName);
	ret->mPropertyValue = mPropertyValue;
	return ret;
}
MaterialProperty* MaterialPropertyVec2::Clone()
{
	MaterialPropertyVec2* ret = new MaterialPropertyVec2(mName);
	ret->mPropertyValue = mPropertyValue;
	return ret;
}
MaterialProperty* MaterialPropertyFloat::Clone()
{
	MaterialPropertyFloat* ret = new MaterialPropertyFloat(mName);
	ret->mPropertyValue = mPropertyValue;
	return ret;
}
MaterialProperty* MaterialPropertyInt::Clone()
{
	MaterialPropertyInt* ret = new MaterialPropertyInt(mName);
	ret->mPropertyValue = mPropertyValue;
	return ret;
}
MaterialProperty* MaterialPropertyBool::Clone()
{
	MaterialPropertyBool* ret = new MaterialPropertyBool(mName);
	ret->mPropertyValue = mPropertyValue;
	return ret;
}

MaterialProperty* MaterialPropertySampler2D::Clone() 
{
	MaterialPropertySampler2D* ret = new MaterialPropertySampler2D(mName);
	ret->mTextureName = mTextureName;
	return ret;
}

MaterialProperty* MaterialPropertySamplerCube::Clone()
{
	MaterialPropertySamplerCube* ret = new MaterialPropertySamplerCube(mName);
	ret->mTextureName = mTextureName;
	return ret;
}