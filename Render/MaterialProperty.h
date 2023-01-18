#pragma once
#include "YosefGL.h"
#include "YosefPrefix.h"
#include "Utils/LinkedList.h"
enum MaterialUniformPropertyType 
{
	kMaterialUniformPropertyTypeCameraProjectionMatrix,
	kMaterialUniformPropertyTypeCameraViewMatrix,
	kMaterialUniformPropertyTypeMatrix4,
	kMaterialUniformPropertyTypeMatrix3,
	kMaterialUniformPropertyTypeMatrix2,
	kMaterialUniformPropertyTypeVec4,
	kMaterialUniformPropertyTypeVec3,
	kMaterialUniformPropertyTypeVec2,
	kMaterialUniformPropertyTypeFloat,
	kMaterialUniformPropertyTypeBool,
	kMaterialUniformPropertyTypeInt,
	kMaterialUniformPropertyTypeSampler2D,
	kMaterialUniformPropertyTypeSamplerCube,
	kMaterialUniformPropertyTypeCount
};

class MaterialProperty 
{
public:
	MaterialUniformPropertyType mType;//uniform float U_Factor;
	char mName[64];
	MaterialProperty(MaterialUniformPropertyType t, const char* name);
	virtual MaterialProperty* Clone() = 0;
};

class MaterialPropertyMatrix4 :public MaterialProperty
{
public:
	MaterialPropertyMatrix4(const char* name);
	float* mPropertyValue;
	MaterialProperty* Clone();
};

class MaterialPropertyMatrix3 :public MaterialProperty
{
public:
	MaterialPropertyMatrix3(const char* name);
	float* mPropertyValue;
	MaterialProperty* Clone();
};

class MaterialPropertyMatrix2 :public MaterialProperty
{
public:
	MaterialPropertyMatrix2(const char* name);
	float* mPropertyValue;
	MaterialProperty* Clone();
};

class MaterialPropertyVec4 :public MaterialProperty
{
public:
	MaterialPropertyVec4(const char* name);
	float* mPropertyValue;
	MaterialProperty* Clone();
};

class MaterialPropertyVec3 :public MaterialProperty
{
public:
	MaterialPropertyVec3(const char* name);
	float* mPropertyValue;
	MaterialProperty* Clone();
};

class MaterialPropertyVec2 :public MaterialProperty
{
public:
	MaterialPropertyVec2(const char* name);
	float* mPropertyValue;
	MaterialProperty* Clone();
};

class MaterialPropertyFloat :public MaterialProperty
{
public:
	MaterialPropertyFloat(const char* name);
	float mPropertyValue;
	MaterialProperty* Clone();
};

class MaterialPropertyInt :public MaterialProperty
{
public:
	MaterialPropertyInt(const char* name);
	int mPropertyValue;
	MaterialProperty* Clone();
};

class MaterialPropertyBool :public MaterialProperty
{
public:
	MaterialPropertyBool(const char* name);
	bool mPropertyValue;
	MaterialProperty* Clone();
};

class MaterialPropertySampler2D :public MaterialProperty
{
public:
	MaterialPropertySampler2D(const char* name);
	GLuint mTextureName;//TextureUnit
	MaterialProperty* Clone();
};

class MaterialPropertySamplerCube :public MaterialProperty {
public:
	MaterialPropertySamplerCube(const char* name);
	GLuint mTextureName;
	MaterialProperty* Clone();
};