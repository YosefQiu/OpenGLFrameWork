#include "model.h"
#include "VertexData.h"
#include "Utils/FileIO.h"
Model::Model() 
{
	mVAO = nullptr;
	mVBO = nullptr;
	mEBO = nullptr;
	mMaterial = nullptr;
	mDraw = nullptr;
}

Model::~Model()
{
	
}

void Model::Init(const char*modelPath) 
{
	struct FloatData {
		float v[3];
	};
	struct VertexDefine {
		int posIndex;
		int texcoordIndex;
		int normalIndex;
	};
	int nFileSize = 0;
	unsigned char*fileContent = LoadFileContent(modelPath, nFileSize);
	if (fileContent==nullptr){
		return;
	}
	std::vector<FloatData> positions, texcoords, normals;
	std::vector<VertexDefine> vertexes;
	std::stringstream ssFileContent((char*)fileContent);
	std::string temp;
	char szOneLine[256];
	while (!ssFileContent.eof()){
		memset(szOneLine, 0, 256);
		ssFileContent.getline(szOneLine, 256);
		if (strlen(szOneLine) > 0){
			if (szOneLine[0] == 'v'){
				std::stringstream ssOneLine(szOneLine);
				if (szOneLine[1] == 't') {
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					texcoords.push_back(floatData);
					//printf("texcoord : %f,%f\n", floatData.v[0], floatData.v[1]);
				}else if (szOneLine[1] == 'n') {
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					normals.push_back(floatData);
					//printf("normal : %f,%f,%f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}else {
					ssOneLine >> temp;
					FloatData floatData;
					ssOneLine >> floatData.v[0];
					ssOneLine >> floatData.v[1];
					ssOneLine >> floatData.v[2];
					positions.push_back(floatData);
					//printf("position : %f,%f,%f\n", floatData.v[0], floatData.v[1], floatData.v[2]);
				}
			}
			else if (szOneLine[0] == 'f') {
				std::stringstream ssOneLine(szOneLine);
				ssOneLine >> temp;
				std::string vertexStr;
				for (int i = 0; i < 3; i++) {
					ssOneLine >> vertexStr;
					size_t pos = vertexStr.find_first_of('/');
					std::string posIndexStr = vertexStr.substr(0, pos);
					size_t pos2 = vertexStr.find_first_of('/', pos + 1);
					std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - 1 - pos);
					std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - 1 - pos2);
					VertexDefine vd;
					vd.posIndex = atoi(posIndexStr.c_str());
					vd.texcoordIndex = atoi(texcoordIndexStr.c_str());
					vd.normalIndex = atoi(normalIndexStr.c_str());
					vertexes.push_back(vd);
				}
			}
		}
	}
	delete fileContent;
	int vertexCount = (int)vertexes.size();
	VertexDataFull * vertices = new VertexDataFull[vertexCount];
	for (int i = 0; i < vertexCount; ++i)
	{
		float *temp = positions[vertexes[i].posIndex - 1].v;
		vertices[i].mVertex[0] = temp[0];
		vertices[i].mVertex[1] = temp[1];
		vertices[i].mVertex[2] = temp[2];
		vertices[i].mVertex[3] = 1.0f;
		temp = normals[vertexes[i].normalIndex - 1].v;
		vertices[i].mNormal[0] = temp[0];
		vertices[i].mNormal[1] = temp[1];
		vertices[i].mNormal[2] = temp[2];
		vertices[i].mNormal[3] = 0.0f;
		temp = texcoords[vertexes[i].texcoordIndex - 1].v;
		vertices[i].mTexCoord0[0] = temp[0];
		vertices[i].mTexCoord0[1] = temp[1];
		vertices[i].mTexCoord0[2] = temp[2];
		vertices[i].mTexCoord0[3] = 0.0f;

		if (vertices[i].mVertex.x < mMin.x)
			mMin.x = vertices[i].mVertex.x;
		if (vertices[i].mVertex.y < mMin.y)
			mMin.y = vertices[i].mVertex.y;
		if (vertices[i].mVertex.z < mMin.z)
			mMin.z = vertices[i].mVertex.z;

		if (vertices[i].mVertex.x > mMax.x)
			mMax.x = vertices[i].mVertex.x;
		if (vertices[i].mVertex.y > mMax.y)
			mMax.y = vertices[i].mVertex.y;
		if (vertices[i].mVertex.z > mMax.z)
			mMax.z = vertices[i].mVertex.z;
	}
	mVertexCount = vertexCount;
	mData = vertices;
}

void Model::ModelProcess(Shader* shader)
{
	mVAO = new VAO;
	mVAO->Init();
	mVBO = new VBO;
	mVBO->SetSize(mVertexCount);
	mVBO->SubmitData(mData, sizeof(VertexDataFull) * mVertexCount);

	glm::vec3 max = glm::vec3(mMax.x, mMax.y, mMax.z);
	glm::vec3 min = glm::vec3(mMin.x, mMin.y, mMin.z);

	glm::vec3 center = (max + min) / 2.0f;
	float dist = (max - min).z * 2.0f;
	mCameraPos = glm::vec3(0, 0, dist);
	mTargetPos = glm::vec3(center - mCameraPos);


	mMaterial = new Material;
	mMaterial->mBaseRenderPass = new RenderPass;
	mMaterial->mBaseRenderPass->SetShader(shader);
	
	mDraw = new DrawCall;
	mDraw->mVAO = mVAO;
	mDraw->mVBO = mVBO;
	mDraw->mMaterial = mMaterial;
}
void Model::SetMatrix4(const char* uniform_name, float* mat4, bool baseFlag)
{
	if (baseFlag)
	{
		if (mMaterial != nullptr && mMaterial->mBaseRenderPass)
		{
			mMaterial->mBaseRenderPass->SetMatrix4(uniform_name, mat4);
		}
	}
	else
	{
		if (mMaterial != nullptr && mMaterial->mAdditiveRenderPass)
		{
			mMaterial->mAdditiveRenderPass->SetMatrix4(uniform_name, mat4);
		}
	}
	
}
void Model::SetVec4(const char* uniform_name, float* vec4, bool baseFlag)
{
	if (baseFlag)
	{
		if (mMaterial != nullptr && mMaterial->mBaseRenderPass)
		{
			mMaterial->mBaseRenderPass->SetVec4(uniform_name, vec4);
		}
	}
	else
	{
		if (mMaterial != nullptr && mMaterial->mAdditiveRenderPass)
		{
			mMaterial->mAdditiveRenderPass->SetVec4(uniform_name, vec4);
		}
	}
}