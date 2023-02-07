#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <memory>
#include <algorithm>
#include <functional>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#ifdef _WIN32 || _WIN64
#include <windows.h>
#pragma comment( lib,"winmm.lib" )
#endif

#define DWORD unsigned int

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifdef  _WIN32 || _WIN64
#ifndef _CMAKE
const std::string geomerty_path = "Res/Geometry/";
const std::string front_path = "Res/Fronts/";
const std::string hdr_path = "Res/HDR/"; 
const std::string models_path = "Res/Models/"; 
const std::string pic_path = "Res/Pics/"; 
const std::string shader_path = "Res/Shaders/"; 
#endif
#ifdef  _CMAKE
const std::string geomerty_path = "../Res/Geometry/";
const std::string front_path = "../Res/Fronts/";
const std::string hdr_path = "../Res/HDR/";
const std::string models_path = "../Res/Models/";
const std::string pic_path = "../Res/Pics/";
const std::string shader_path = "../Res/Shaders/";
#endif //  _CMAKE
#endif 

#ifdef __GNUC__
const std::string geomerty_path = "../Res/Geometry/";
const std::string front_path = "../Res/Fronts/";
const std::string hdr_path = "../Res/HDR/";
const std::string models_path = "../Res/Models/";
const std::string pic_path = "../Res/Pics/";
const std::string shader_path = "../Res/Shaders/";
#endif // DEBUG

const std::string ViewMatrix = "V";
const std::string ProjMatrix = "P";
const std::string ModelMatrix = "M";

const std::string ATTR_POSITION = "position";
const std::string ATTR_TEXCOORD = "texcoord1";
const std::string ATTR_NORMAL = "normal";
const std::string ATTR_TANGENT = "tangent";
const std::string ATTR_TEXCOORD1 = "texcoord1";

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef _WIN64
//define something for Windows (64-bit only)
#define PLATFORMS "WIN64"
#else
#define PLATFORMS "WIN32"
#endif
#endif

#if __GNUC__
#if __x86_64__ || __ppc64__
#define PLATFORMS "ENVIRONMENT64"
#else
#define PLATFORMS "ENVIRONMENT32"
#endif

#define COMPILE "_clang__" 
#if defined __clang_patchlevel__
#define COMPILE_VERSION __clang_version__     
#endif
#define COMPILE_PLATFORMS PLATFORMS
#endif

#ifdef _MSC_VER
#define COMPILE "MSVC" 
#define COMPILE_PLATFORMS PLATFORMS
#define COMPILE_VERSION _MSC_VER
#endif
#ifdef __INTEL_LLVM_COMPILER
#define COMPILE "Intel C++" 
#define COMPILE_VERSION __INTEL_LLVM_COMPILER
#endif // __INTEL_LLVM_COMPILER