#pragma once

#pragma once

namespace VertexAttributes
{
#define DEF_VERTEX_ATTRI(n) \
static const char * n##NameInShader="A_"#n
	DEF_VERTEX_ATTRI(VertexPos);
	DEF_VERTEX_ATTRI(TexCoord);
	DEF_VERTEX_ATTRI(Normal);
	DEF_VERTEX_ATTRI(Tangent);
	DEF_VERTEX_ATTRI(TexCoord1);
#undef DEF_VERTEX_ATTRI
}

namespace UniformDefines {
#define DEF_UNIFORM_TYPE(n,id)\
static const int Uniform_Type_##n=id
	DEF_UNIFORM_TYPE(Mat4, 1);
	DEF_UNIFORM_TYPE(Vec4, 2);
	DEF_UNIFORM_TYPE(Vec4Array, 3);
	DEF_UNIFORM_TYPE(IntArray, 4);
	DEF_UNIFORM_TYPE(Sampler2D, 5);
	DEF_UNIFORM_TYPE(SamplerCube, 6);
#define DEF_BUILTIN_UNIFORM_MATRIX(n) \
static const char * Matrix_##n##_NameInShader = "Yosef_Matrix_"#n
#define DEF_BUILTIN_UNIFORM_VEC4(n) \
static const char * Vec4_##n##_NameInShader = "Yosef_"#n
#define DEF_BUILTIN_UNIFORM_VEC4_ARRAY(n) \
static const char * Vec4Array_##n##_NameInShader = "Yosef_"#n"[0]"
#define DEF_BUILTIN_UNIFORM_INT(n) \
static const char * Int_##n##_NameInShader = "Yosef_"#n
#define DEF_BUILTIN_UNIFORM_INT_ARRAY(n) \
static const char * IntArray_##n##_NameInShader = "Yosef_"#n"[0]"
#define DEF_BUILTIN_UNIFORM_SAMPLER(n) \
static const char * Sampler_##n##_NameInShader = "Yosef_"#n
	DEF_BUILTIN_UNIFORM_MATRIX(M);
	DEF_BUILTIN_UNIFORM_MATRIX(V);
	DEF_BUILTIN_UNIFORM_MATRIX(P);
	DEF_BUILTIN_UNIFORM_MATRIX(IT_M);
	DEF_BUILTIN_UNIFORM_MATRIX(MainLightProjection);
	DEF_BUILTIN_UNIFORM_MATRIX(MainLightView);
	DEF_BUILTIN_UNIFORM_VEC4(MainLightPosition);
	DEF_BUILTIN_UNIFORM_VEC4(Time);
	DEF_BUILTIN_UNIFORM_VEC4(SinTime);
	DEF_BUILTIN_UNIFORM_VEC4(CosTime);
	DEF_BUILTIN_UNIFORM_VEC4(CameraWorldPos);
	DEF_BUILTIN_UNIFORM_VEC4(AmbientMaterial);
	DEF_BUILTIN_UNIFORM_VEC4(DiffuseMaterial);
	DEF_BUILTIN_UNIFORM_VEC4(SpecularMaterial);
	DEF_BUILTIN_UNIFORM_VEC4(ColorScale);
	DEF_BUILTIN_UNIFORM_VEC4(MaterialMask);
	DEF_BUILTIN_UNIFORM_VEC4(LightFlag);
	DEF_BUILTIN_UNIFORM_VEC4(FragMixSetting);
	DEF_BUILTIN_UNIFORM_VEC4(LightPos);
	DEF_BUILTIN_UNIFORM_VEC4(LightAmbient);
	DEF_BUILTIN_UNIFORM_VEC4(LightDiffuse);
	DEF_BUILTIN_UNIFORM_VEC4(LightSpecular);
	DEF_BUILTIN_UNIFORM_VEC4(LightSetting);
	DEF_BUILTIN_UNIFORM_VEC4(LightSetting1);
	DEF_BUILTIN_UNIFORM_VEC4_ARRAY(LightPos);
	DEF_BUILTIN_UNIFORM_VEC4_ARRAY(LightAmbient);
	DEF_BUILTIN_UNIFORM_VEC4_ARRAY(LightDiffuse);
	DEF_BUILTIN_UNIFORM_VEC4_ARRAY(LightSpecular);
	DEF_BUILTIN_UNIFORM_VEC4_ARRAY(LightSetting);
	DEF_BUILTIN_UNIFORM_VEC4_ARRAY(LightSetting1);
	DEF_BUILTIN_UNIFORM_SAMPLER(AmbientTexture);
	DEF_BUILTIN_UNIFORM_SAMPLER(DiffuseTexture);
	DEF_BUILTIN_UNIFORM_SAMPLER(SpecularTexture);
	DEF_BUILTIN_UNIFORM_SAMPLER(AlphaTexture);
	DEF_BUILTIN_UNIFORM_SAMPLER(NormalTexture);
	DEF_BUILTIN_UNIFORM_SAMPLER(DepthMap);
	DEF_BUILTIN_UNIFORM_SAMPLER(SkyBox);
	DEF_BUILTIN_UNIFORM_INT_ARRAY(LightEnabled);
#undef DEF_BUILTIN_UNIFORM_INT_ARRAY
#undef DEF_BUILTIN_UNIFORM_INT
#undef DEF_BUILTIN_UNIFORM_SAMPLER
#undef DEF_BUILTIN_UNIFORM_VEC4_ARRAY
#undef DEF_BUILTIN_UNIFORM_VEC4
#undef DEF_BUILTIN_UNIFORM_MATRIX
}