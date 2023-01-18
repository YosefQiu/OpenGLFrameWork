#include "UniformUpdater.h"
#include "Camera.h"
UniformUpdater::UniformUpdater(GLint location, UpdateUniformFunction f, MaterialProperty* target_property)
{
	mLocation = location;
	mUpdateFunction = f;
	mTargetProperty = target_property;
}
void UniformUpdater::UpdateProjectionMatrix4(GLint location, void* camera, void* property_value)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(((Camera*)camera)->mProjectionMatrix));
}
void UniformUpdater::UpdateViewMatrix4(GLint location, void* camera, void* property_value)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(((Camera*)camera)->mViewMatrix));
}
void UniformUpdater::UpdateMatrix4(GLint location, void* camera, void* property_value) 
{
	MaterialPropertyMatrix4* prop = (MaterialPropertyMatrix4*)property_value;
	glUniformMatrix4fv(location, 1, GL_FALSE, prop->mPropertyValue);
}
void UniformUpdater::UpdateMatrix3(GLint location, void* camera, void* property_value)
{
	MaterialPropertyMatrix3* prop = (MaterialPropertyMatrix3*)property_value;
	glUniformMatrix3fv(location, 1, GL_FALSE, prop->mPropertyValue);
}
void UniformUpdater::UpdateMatrix2(GLint location, void* camera, void* property_value) 
{
	MaterialPropertyMatrix2* prop = (MaterialPropertyMatrix2*)property_value;
	glUniformMatrix2fv(location, 1, GL_FALSE, prop->mPropertyValue);
}
void UniformUpdater::UpdateVec4(GLint location, void* camera, void* property_value) 
{
	MaterialPropertyVec4* prop = (MaterialPropertyVec4*)property_value;
	glUniform4fv(location, 1, prop->mPropertyValue);
}
void UniformUpdater::UpdateVec3(GLint location, void* camera, void* property_value) 
{
	MaterialPropertyVec3* prop = (MaterialPropertyVec3*)property_value;
	glUniform3fv(location, 1, prop->mPropertyValue);
}
void UniformUpdater::UpdateVec2(GLint location, void* camera, void* property_value) 
{
	MaterialPropertyVec2* prop = (MaterialPropertyVec2*)property_value;
	glUniform2fv(location, 1, prop->mPropertyValue);
}
void UniformUpdater::UpdateFloat(GLint location, void* camera, void* property_value)
{
	MaterialPropertyFloat* prop = (MaterialPropertyFloat*)property_value;
	glUniform1f(location, prop->mPropertyValue);
}
void UniformUpdater::UpdateInt(GLint location, void* camera, void* property_value)
{
	MaterialPropertyInt* prop = (MaterialPropertyInt*)property_value;
	glUniform1i(location, prop->mPropertyValue);
}
void UniformUpdater::UpdateBool(GLint location, void* camera, void* property_value)
{
	MaterialPropertyBool* prop = (MaterialPropertyBool*)property_value;
	glUniform1i(location, prop->mPropertyValue);
}
void UniformUpdater::UpdateSampler2D(GLint location, void* camera, void* property_value)
{
	MaterialPropertySampler2D* prop = (MaterialPropertySampler2D*)property_value;
	glUniform1i(location, prop->mTextureName);
}
void UniformUpdater::UpdateSamplerCube(GLint location, void* camera, void* property_value)
{
	MaterialPropertySamplerCube* prop = (MaterialPropertySamplerCube*)property_value;
	glUniform1i(location, prop->mTextureName);
}
UniformUpdater* UniformUpdater::Clone() 
{
	return new UniformUpdater(mLocation, mUpdateFunction, mTargetProperty == nullptr ? mTargetProperty : mTargetProperty->Clone());
}