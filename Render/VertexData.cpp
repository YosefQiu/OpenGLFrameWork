#include "VertexData.h"
VertexDataFull* GetTriangle()
{
	VertexDataFull* triangle = new VertexDataFull[3];
	triangle[0].mVertex[0] = -0.5f;
	triangle[0].mVertex[1] = -0.5f;
	triangle[0].mVertex[2] = -2.0f;
	triangle[0].mVertex[3] = 1.0f;
	triangle[1].mVertex[0] = 0.5f;
	triangle[1].mVertex[1] = -0.5f;
	triangle[1].mVertex[2] = -2.0f;
	triangle[1].mVertex[3] = 1.0f;
	triangle[2].mVertex[0] = 0.0f;
	triangle[2].mVertex[1] = 0.5f;
	triangle[2].mVertex[2] = -2.0f;
	triangle[2].mVertex[3] = 1.0f;
	return triangle;
}
