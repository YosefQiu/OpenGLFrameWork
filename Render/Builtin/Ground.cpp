#include "Ground.h"
#include "HardCodedShader.h"
#include "../Camera.h"
Ground::Ground()
{

	mVAO = nullptr;
	mVBO = nullptr;
	mMaterial = nullptr;
}

Ground::~Ground()
{
	if (mVAO)
	{
		delete mVAO;
		mVAO = nullptr;
	}
	if (mVBO)
	{
		delete mVBO;
		mVBO = nullptr;
	}
	if (mMaterial)
	{
		delete mVAO;
		mMaterial = nullptr;
	}
}

void Ground::Init()
{
	mVAO = new VAO;
	mVAO->Init();

	mVBO = new VBO;
	mData = new VertexDataFull[1600];

	for (int z = 0; z < 20; z++)
	{
		float zStart = -100.0f + z * 10.0f;
		for (int x = 0; x < 20; x++)
		{
			int offset = (x + z * 20) * 4;
			float xStart = -100.0f + x * 10.0f;

			mData[offset + 0].mVertex = glm::vec4(xStart,			-1.0f, zStart,			1.0f);
			mData[offset + 1].mVertex = glm::vec4(xStart + 10.0f,	-1.0f, zStart,			1.0f);
			mData[offset + 2].mVertex = glm::vec4(xStart,			-1.0f, zStart - 10.0f, 1.0f);
			mData[offset + 3].mVertex = glm::vec4(xStart + 10.0f,	-1.0f, zStart - 10.0f, 1.0f);

			mData[offset + 0].mNormal = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
			mData[offset + 1].mNormal = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
			mData[offset + 2].mNormal = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
			mData[offset + 3].mNormal = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

			if ((z % 2) ^ (x % 2)) 
			{
				mData[offset + 0].mNormal = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
				mData[offset + 1].mNormal = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
				mData[offset + 2].mNormal = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
				mData[offset + 3].mNormal = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
			}
			else 
			{
				mData[offset + 0].mNormal = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
				mData[offset + 1].mNormal = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
				mData[offset + 2].mNormal = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
				mData[offset + 3].mNormal = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
			}
		}
	}

	mVAO->Bind();
	mVBO->Bind();
	mVBO->SetSize(1600);
	mVBO->SubmitData(mData, sizeof(VertexDataFull) * 1600);

	Shader* shader = new Shader;
	shader->InitBuiltShader(sGroundVS, sGroundFS);

	mMaterial = new Material;
	mMaterial->mBaseRenderPass = new RenderPass;
	mMaterial->mBaseRenderPass->SetShader(shader);
}

void Ground::Render(Camera* camera)
{
	mVAO->Bind();
	mVBO->Bind();
	glUseProgram(mMaterial->mBaseRenderPass->mShader->mProgram);
	
	glm::mat4 m = glm::mat4(1.0f);
	glm::mat4 scale = glm::mat4(1.0f);
	scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 rotate = glm::mat4(1.0f);
	rotate = glm::rotate(rotate, glm::degrees(-310.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	m = rotate * scale * m;
	mMaterial->mBaseRenderPass->SetMatrix4(ModelMatrix.c_str(), glm::value_ptr(m));
	mMaterial->Bind(camera);

	for (int i = 0; i < 400; i++)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
	}
	mVBO->UnBind();
	mVAO->UnBind();
}
