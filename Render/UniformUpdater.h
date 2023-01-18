#pragma once
#include "YosefGL.h"
#include "YosefPrefix.h"
#include "Utils/LinkedList.h"
#include "MaterialProperty.h"


typedef void(*UpdateUniformFunction)(GLint location, void* camera, void* property_value);

class UniformUpdater : public LinkedList 
{
public:
	GLint mLocation;
	UpdateUniformFunction mUpdateFunction;
	MaterialProperty* mTargetProperty;
	UniformUpdater(GLint location, UpdateUniformFunction f, MaterialProperty* target_property);
	UniformUpdater* Clone();
	static void UpdateProjectionMatrix4(GLint location, void* camera, void* property_value);
	static void UpdateViewMatrix4(GLint location, void* camera, void* property_value);
	static void UpdateMatrix4(GLint location, void* camera, void* property_value);
	static void UpdateMatrix3(GLint location, void* camera, void* property_value);
	static void UpdateMatrix2(GLint location, void* camera, void* property_value);
	static void UpdateVec4(GLint location, void* camera, void* property_value);
	static void UpdateVec3(GLint location, void* camera, void* property_value);
	static void UpdateVec2(GLint location, void* camera, void* property_value);
	static void UpdateFloat(GLint location, void* camera, void* property_value);
	static void UpdateInt(GLint location, void* camera, void* property_value);
	static void UpdateBool(GLint location, void* camera, void* property_value);
	static void UpdateSampler2D(GLint location, void* camera, void* property_value);
	static void UpdateSamplerCube(GLint location, void* camera, void* property_value);
};