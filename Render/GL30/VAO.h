#pragma once
#include "../YosefGL.h"
#include "../YosefPrefix.h"

// ** VAO is required after GL 3.0
// ** VAO is not required in GL 2.0
// ** This program is based on OpenGL 3.0 by default

class VAO
{
public:
	GLuint mIdentifier;
public:
	VAO();
	virtual ~VAO();
public:
	void Init();
	bool Active();
	bool Restore();
	void Bind();
	void UnBind();
};