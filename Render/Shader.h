#pragma once
#include "YosefGL.h"
#include "YosefPrefix.h"
#include "Attribute.h"
#include "UniformUpdater.h"
#include "MaterialProperty.h"

class Shader
{
public:
	GLuint mProgram;
	Attribute* mAttributes;
	UniformUpdater* mUniforms;
	std::unordered_map<std::string, MaterialProperty*> mProperties;
	static std::unordered_map<std::string, Shader*> mCachedShaders;
	static std::unordered_map<std::string, Shader*> mBuiltShaders;
	static Shader* LoadShader(const char* name, const char* vs, const char* fs, const char* gs = nullptr, const char* tcs = nullptr, const char* tes = nullptr);
	void Init(const char* vertex_shader_file, const char* fragment_shader_file,
		const char* geom_shader_file = nullptr,
		const char* control_shader_file = nullptr, const char* evalua_shader_file = nullptr, bool bDebug = false);
	void InitBuiltShader(const char* vsCode, const char* fsCode);
protected:
	void InitAttributes();
	void InitUniforms();
	void OnDetectUniformMatrix4(GLint loc, const char* uniform_name);
	void OnDetectUniformMatrix3(GLint loc, const char* uniform_name);
	void OnDetectUniformMatrix2(GLint loc, const char* uniform_name);
	void OnDetectUniformVec4(GLint loc, const char* uniform_name);
	void OnDetectUniformVec3(GLint loc, const char* uniform_name);
	void OnDetectUniformVec2(GLint loc, const char* uniform_name);
	void OnDetectUniformFloat(GLint loc, const char* uniform_name);
	void OnDetectUniformInt(GLint loc, const char* uniform_name);
	void OnDetectUniformBool(GLint loc, const char* uniform_name);
	void OnDetectUniformSampler2D(GLint loc, const char* uniform_name);
	void OnDetectUniformSamplerCube(GLint loc, const char* uniform_name);
	void AppendUniformUpdater(UniformUpdater* uniform_updater);
private:
	GLuint CompileShader(GLenum shaderType, const char* shaderCode);
	//GLuint CreateProgram(GLuint vsShader, GLuint fsShader);
	GLuint CreateProgram(unsigned int vsShader, unsigned int fsShader, unsigned int gShader = -1, unsigned int cShader = -1, unsigned int eShader = -1);
	GLuint CheckError(unsigned int candidate, GLenum pname);
	std::string PrewProcess(const std::string& path, bool bDebug = false);
};