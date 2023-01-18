#include "Shader.h"
#include "Utils/FileIO.h"
#include "Utils/FixedStr.h"
#include "VertexData.h"
std::unordered_map<std::string,Shader*> Shader::mCachedShaders;
Shader*Shader::LoadShader(const char *name, const char*vs, const char*fs)
{
	auto iter = mCachedShaders.find(name);
	if (iter!=mCachedShaders.end())
	{
		return iter->second;
	}
	Shader*shader = new Shader;
	shader->Init(vs, fs);
	mCachedShaders.insert(std::pair<std::string,Shader*>(name,shader));
	return shader;
}
//void Shader::Init(const char*vs, const char*fs) 
//{
//	mAttributes = nullptr;
//	mUniforms = nullptr;
//	int nFileSize = 0;
//	const char*vsCode = (char*)LoadFileContent(vs, nFileSize);
//	const char*fsCode = (char*)LoadFileContent(fs, nFileSize);
//	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, vsCode);
//	if (vsShader == 0) 
//	{
//		return;
//	}
//	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, fsCode);
//	if (fsShader == 0)
//	{
//		return;
//	}
//	mProgram = CreateProgram(vsShader, fsShader);
//	glDeleteShader(vsShader);
//	glDeleteShader(fsShader);
//	if (mProgram != 0)
//	{
//		InitAttributes();
//		InitUniforms();
//	}
//}

void Shader::Init(const char* vertex_shader_file, const char* fragment_shader_file, const char* geom_shader_file, const char* control_shader_file, const char* evalua_shader_file, bool bDebug)
{

	mAttributes = nullptr;
	mUniforms = nullptr;

	unsigned int vsShader = -1, fsShader = -1, gsShader = -1, csShader = -1, esShader = -1;
	std::string shaderCode = PrewProcess(std::string(vertex_shader_file));
	vsShader = CompileShader(GL_VERTEX_SHADER, shaderCode.c_str());
	shaderCode.clear();
	shaderCode = PrewProcess(std::string(fragment_shader_file), bDebug);
	fsShader = CompileShader(GL_FRAGMENT_SHADER, shaderCode.c_str());
	shaderCode.clear();
	if (geom_shader_file != nullptr) {
		shaderCode = PrewProcess(std::string(geom_shader_file));
		gsShader = CompileShader(GL_GEOMETRY_SHADER, shaderCode.c_str());
		shaderCode.clear();
	}
	if (control_shader_file != nullptr) {
		shaderCode = PrewProcess(std::string(control_shader_file));
		csShader = CompileShader(GL_TESS_CONTROL_SHADER, shaderCode.c_str());
		shaderCode.clear();
	}
	if (evalua_shader_file != nullptr) {
		shaderCode = PrewProcess(std::string(evalua_shader_file));
		csShader = CompileShader(GL_TESS_EVALUATION_SHADER, shaderCode.c_str());
		shaderCode.clear();
	}
	mProgram = CreateProgram(vsShader, fsShader, gsShader, csShader, esShader);
	glDeleteShader(vsShader);
	glDeleteShader(fsShader);
	if (geom_shader_file != nullptr) {
		glDeleteShader(gsShader);
	}
	if (control_shader_file != nullptr) {
		glDeleteShader(csShader);
	}
	if (evalua_shader_file != nullptr) {
		glDeleteShader(esShader);
	}

	if (mProgram != 0) {
		InitAttributes();
		InitUniforms();
	}
}

void Shader::InitBuiltShader(const char* vsCode, const char* fsCode)
{
	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, vsCode);
	if (vsShader == 0) 
	{
		return;
	}
	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, fsCode);
	if (fsShader == 0)
	{
		return;
	}
	mProgram = CreateProgram(vsShader, fsShader);
	glDeleteShader(vsShader);
	glDeleteShader(fsShader);
	if (mProgram != 0)
	{
		InitAttributes();
		InitUniforms();
	}
}
void Shader::InitAttributes() 
{
	GLint count = 0;
	glGetProgramiv(mProgram, GL_ACTIVE_ATTRIBUTES, &count);
	for (int i = 0; i < count; ++i) 
	{
		GLsizei len = 0;
		GLenum t = 0;
		GLint s = 0;
		char attribute_name[256] = { 0 };
		glGetActiveAttrib(mProgram, i, 256, &len, &s, &t, attribute_name);
		GLint loc = glGetAttribLocation(mProgram, attribute_name);
		int component_count = 0;
		int base_data_type = 0;
		if (t == GL_FLOAT_VEC4) 
		{
			component_count = 4;
			base_data_type = GL_FLOAT;
		}
		int data_offset = 0;
		if (strcmp(attribute_name, ATTR_POSITION.c_str()) == 0) 
		{
			data_offset = 0;
		}
		else if (strcmp(attribute_name, ATTR_TEXCOORD.c_str()) == 0)
		{
			data_offset = sizeof(float) * 4;
		}
		else if (strcmp(attribute_name, ATTR_NORMAL.c_str()) == 0)
		{
			data_offset = sizeof(float) * 8;
		}
		else if (strcmp(attribute_name, ATTR_TANGENT.c_str()) == 0)
		{
			data_offset = sizeof(float) * 12;
		}
		else if (strcmp(attribute_name, ATTR_TEXCOORD1.c_str()) == 0)
		{
			data_offset = sizeof(float) * 16;
		}
		Attribute*attribute = new Attribute(loc,
			component_count,
			base_data_type,
			GL_FALSE,
			sizeof(VertexDataFull),
			data_offset);
		if (mAttributes == nullptr)
		{
			mAttributes = attribute;
		}
		else
		{
			mAttributes->PushBack(attribute);
		}
	}
}

void Shader::InitUniforms() 
{
	GLint count = 0;
	glGetProgramiv(mProgram, GL_ACTIVE_UNIFORMS, &count);
	for (int i = 0; i < count; ++i) 
	{
		GLsizei len = 0;
		GLenum t = 0;
		GLint s = 0;
		char uniform_name[256] = { 0 };
		glGetActiveUniform(mProgram, i, 256, &len, &s, &t, uniform_name);
		GLint loc = glGetUniformLocation(mProgram, uniform_name);
		if (t == GL_FLOAT_MAT4)
		{
			OnDetectUniformMatrix4(loc, uniform_name);
		}
		else if (t == GL_FLOAT_MAT3)
		{
			OnDetectUniformMatrix3(loc, uniform_name);
		}
		else if (t == GL_FLOAT_MAT2)
		{
			OnDetectUniformMatrix2(loc, uniform_name);
		}
		else if (t == GL_FLOAT_VEC4) 
		{
			OnDetectUniformVec4(loc, uniform_name);
		}
		else if (t == GL_FLOAT_VEC3)
		{
			OnDetectUniformVec3(loc, uniform_name);
		}
		else if (t == GL_FLOAT_VEC2)
		{
			OnDetectUniformVec2(loc, uniform_name);
		}
		else if (t == GL_FLOAT)
		{
			OnDetectUniformFloat(loc, uniform_name);
		}
		else if (t == GL_INT)
		{
			OnDetectUniformInt(loc, uniform_name);
		}
		else if (t == GL_BOOL)
		{
			OnDetectUniformBool(loc, uniform_name);
		}
		else if (t == GL_SAMPLER_2D)
		{
			OnDetectUniformSampler2D(loc, uniform_name);
		}
		else if (t == GL_SAMPLER_CUBE)
		{
			OnDetectUniformSamplerCube(loc, uniform_name);
		}
	}
}
void Shader::OnDetectUniformMatrix4(GLint loc, const char* uniform_name) 
{
	MaterialPropertyMatrix4*prop = nullptr;
	MaterialUniformPropertyType uniform_type = kMaterialUniformPropertyTypeMatrix4;
	UpdateUniformFunction  update_function = UniformUpdater::UpdateMatrix4;
	if (strcmp(uniform_name, ProjMatrix.c_str()) == 0)
	{
		uniform_type = kMaterialUniformPropertyTypeCameraProjectionMatrix;
		update_function = UniformUpdater::UpdateProjectionMatrix4;
	}
	else if (strcmp(uniform_name, ViewMatrix.c_str()) == 0) 
	{
		uniform_type = kMaterialUniformPropertyTypeCameraViewMatrix;
		update_function = UniformUpdater::UpdateViewMatrix4;
	}
	else 
	{
		prop = new MaterialPropertyMatrix4(uniform_name);
		prop->mType = uniform_type;
		mProperties.insert(std::pair<std::string, MaterialProperty*>(uniform_name, prop));
	}
	AppendUniformUpdater(new UniformUpdater(loc, update_function, prop));
}

void Shader::OnDetectUniformMatrix3(GLint loc, const char* uniform_name)
{
	MaterialPropertyMatrix3* prop = nullptr;
	MaterialUniformPropertyType uniform_type = kMaterialUniformPropertyTypeMatrix3;
	UpdateUniformFunction  update_function = UniformUpdater::UpdateMatrix3;
	prop = new MaterialPropertyMatrix3(uniform_name);
	prop->mType = uniform_type;
	mProperties.insert(std::pair<std::string, MaterialProperty*>(uniform_name, prop));
	AppendUniformUpdater(new UniformUpdater(loc, update_function, prop));
}

void Shader::OnDetectUniformMatrix2(GLint loc, const char* uniform_name)
{
	MaterialPropertyMatrix2* prop = nullptr;
	MaterialUniformPropertyType uniform_type = kMaterialUniformPropertyTypeMatrix2;
	UpdateUniformFunction  update_function = UniformUpdater::UpdateMatrix2;
	prop = new MaterialPropertyMatrix2(uniform_name);
	prop->mType = uniform_type;
	mProperties.insert(std::pair<std::string, MaterialProperty*>(uniform_name, prop));
	AppendUniformUpdater(new UniformUpdater(loc, update_function, prop));
}

void Shader::OnDetectUniformVec4(GLint loc, const char * uniform_name) 
{
	MaterialPropertyVec4*prop = new MaterialPropertyVec4(uniform_name);
	prop->mType = kMaterialUniformPropertyTypeVec4;
	mProperties.insert(std::pair<std::string, MaterialProperty*>(uniform_name, prop));
	AppendUniformUpdater(new UniformUpdater(loc, UniformUpdater::UpdateVec4, prop));
}
void Shader::OnDetectUniformVec3(GLint loc, const char* uniform_name)
{
	MaterialPropertyVec3* prop = new MaterialPropertyVec3(uniform_name);
	prop->mType = kMaterialUniformPropertyTypeVec3;
	mProperties.insert(std::pair<std::string, MaterialProperty*>(uniform_name, prop));
	AppendUniformUpdater(new UniformUpdater(loc, UniformUpdater::UpdateVec3, prop));
}
void Shader::OnDetectUniformVec2(GLint loc, const char* uniform_name)
{
	MaterialPropertyVec2* prop = new MaterialPropertyVec2(uniform_name);
	prop->mType = kMaterialUniformPropertyTypeVec2;
	mProperties.insert(std::pair<std::string, MaterialProperty*>(uniform_name, prop));
	AppendUniformUpdater(new UniformUpdater(loc, UniformUpdater::UpdateVec2, prop));
}
void Shader::OnDetectUniformFloat(GLint loc, const char* uniform_name)
{
	MaterialPropertyFloat* prop = new MaterialPropertyFloat(uniform_name);
	prop->mType = kMaterialUniformPropertyTypeFloat;
	mProperties.insert(std::pair<std::string, MaterialProperty*>(uniform_name, prop));
	AppendUniformUpdater(new UniformUpdater(loc, UniformUpdater::UpdateFloat, prop));
}
void Shader::OnDetectUniformInt(GLint loc, const char* uniform_name)
{
	MaterialPropertyInt* prop = new MaterialPropertyInt(uniform_name);
	prop->mType = kMaterialUniformPropertyTypeInt;
	mProperties.insert(std::pair<std::string, MaterialProperty*>(uniform_name, prop));
	AppendUniformUpdater(new UniformUpdater(loc, UniformUpdater::UpdateInt, prop));
}
void Shader::OnDetectUniformBool(GLint loc, const char* uniform_name)
{
	MaterialPropertyBool* prop = new MaterialPropertyBool(uniform_name);
	prop->mType = kMaterialUniformPropertyTypeBool;
	mProperties.insert(std::pair<std::string, MaterialProperty*>(uniform_name, prop));
	AppendUniformUpdater(new UniformUpdater(loc, UniformUpdater::UpdateBool, prop));
}
void Shader::OnDetectUniformSampler2D(GLint loc, const char* uniform_name) 
{
	MaterialPropertySampler2D* prop = new MaterialPropertySampler2D(uniform_name);
	prop->mType = kMaterialUniformPropertyTypeSampler2D;
	mProperties.insert(std::pair<std::string, MaterialProperty*>(uniform_name, prop));
	AppendUniformUpdater(new UniformUpdater(loc, UniformUpdater::UpdateSampler2D, prop));
}
void Shader::OnDetectUniformSamplerCube(GLint loc, const char* uniform_name) 
{
	MaterialPropertySamplerCube* prop = new MaterialPropertySamplerCube(uniform_name);
	prop->mType = kMaterialUniformPropertyTypeSamplerCube;
	mProperties.insert(std::pair<std::string, MaterialProperty*>(uniform_name, prop));
	AppendUniformUpdater(new UniformUpdater(loc, UniformUpdater::UpdateSamplerCube, prop));
}
void Shader::AppendUniformUpdater(UniformUpdater*uniform_updater) 
{
	if (mUniforms == nullptr) {
		mUniforms = uniform_updater;
	}
	else {
		mUniforms->PushBack(uniform_updater);
	}
}

GLuint Shader::CompileShader(GLenum shaderType, const char* shaderCode) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);
	GLint compileResult = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		char szLog[1024] = { 0 };
		GLsizei logLen = 0;
		glGetShaderInfoLog(shader, 1024, &logLen, szLog);
		printf("Compile Shader fail error log : %s \nshader code :\n%s\n", szLog, shaderCode);
		glDeleteShader(shader);
		shader = 0;
	}
	return shader;
}
//GLuint Shader::CreateProgram(GLuint vsShader, GLuint fsShader) {
//	GLuint program = glCreateProgram();
//	glAttachShader(program, vsShader);
//	glAttachShader(program, fsShader);
//	glLinkProgram(program);
//	glDetachShader(program, vsShader);
//	glDetachShader(program, fsShader);
//	GLint nResult;
//	glGetProgramiv(program, GL_LINK_STATUS, &nResult);
//	if (nResult == GL_FALSE) {
//		char log[1024] = { 0 };
//		GLsizei writed = 0;
//		glGetProgramInfoLog(program, 1024, &writed, log);
//		printf("create gpu program fail,link error : %s\n", log);
//		glDeleteProgram(program);
//		program = 0;
//	}
//	return program;
//}

GLuint Shader::CreateProgram(unsigned int vsShader, unsigned int fsShader, unsigned int gShader, unsigned int cShader, unsigned int eShader) 
{
	unsigned int program = glCreateProgram();
	glAttachShader(program, vsShader);
	glAttachShader(program, fsShader);
	if (gShader != -1) {
		glAttachShader(program, gShader);
	}
	if (cShader != -1) {
		glAttachShader(program, cShader);
	}
	if (eShader != -1) {
		glAttachShader(program, eShader);
	}
	glLinkProgram(program);
	glDetachShader(program, vsShader);
	glDetachShader(program, fsShader);
	if (gShader != -1) {
		glDetachShader(program, gShader);
	}
	if (cShader != -1) {
		glDetachShader(program, cShader);
	}
	if (eShader != -1) {
		glDetachShader(program, eShader);
	}
	if (CheckError(program, GL_LINK_STATUS) == -1) {
		glDeleteProgram(program);
		program = 0;
	}
	return program;
}

GLuint Shader::CheckError(unsigned int candidate, GLenum pname) {
	int err = 0;
	int szlogLen = 0;
	char* szLog = new char[1024];
	memset(szLog, 0, 1024);
	switch (pname) {
	case GL_COMPILE_STATUS:
	{
		err = GL_TRUE;
		glGetShaderiv(candidate, GL_COMPILE_STATUS, &err);
		if (err == GL_FALSE) {
			glGetShaderInfoLog(candidate, 1024, &szlogLen, szLog);
			std::cout << "ERROR::Compile Shader fail-->error log : " << szLog << std::endl;
			return -1;
		}
	}
	break;
	case GL_LINK_STATUS:
	{
		err = GL_TRUE;
		glGetProgramiv(candidate, GL_LINK_STATUS, &err);
		if (err == GL_FALSE) {
			glGetProgramInfoLog(candidate, 1024, &szlogLen, szLog);
			std::cout << "[ERROR] Create gpu program fail-->error log : " << szLog << std::endl;
			return -1;
		}
	}
	break;
	}
	return 0;
}

std::string Shader::PrewProcess(const std::string& path, bool bDebug) 
{
	CFILE shaderFile(path, CFILE::Mode::READ);
	std::vector<std::string> contents = shaderFile.ReadAllLines();

	std::string root = DelTailAfter(path, '/') + "/";
	std::string name = TailAfter(path, '/');

	std::string rst;

	for (const auto& line : contents) {
		if (IsBeginWith(line, "#include")) {
			std::string incPath = Between(line, '"', '"');
			std::string inc = PrewProcess(root + incPath);
			if (inc.empty()) {
				std::cout << "[WARNING] #include is empty or failed" << "\n"
					<< "\t" << "code: " << line.c_str()
					<< "\t" << "path: " << incPath.c_str() << std::endl;
				continue;
			}
			rst += inc;
		}
		else
			rst += line;
	}
	if (bDebug) {
		CFILE debugShadeFile(root + "_DEBUG_" + name, CFILE::Mode::WRITE);
		debugShadeFile.Printf("%s", rst.c_str());
		debugShadeFile.Close();
	}

	return rst;
}