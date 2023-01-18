#include "SkyBox.h"
#include "HardCodedShader.h"
#include "../Camera.h"
SkyBox::SkyBox()
{

	mVAO = nullptr;
	mVBO = nullptr;
	mMaterial = nullptr;
}

SkyBox::~SkyBox()
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

void SkyBox::Init(const char* name)
{
	mVAO = new VAO;
	mVAO->Init();

	mVBO = new VBO;
	mData = new VertexDataFull[36];

	// Positions
	//front
	mData[0].mVertex = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);
	mData[1].mVertex = glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f);
	mData[2].mVertex = glm::vec4(1.0f, -1.0f, -1.0f,  1.0f);
	mData[3].mVertex = glm::vec4(1.0f, -1.0f, -1.0f, 1.0f);
	mData[4].mVertex = glm::vec4(1.0f, 1.0f, -1.0f, 1.0f);
	mData[5].mVertex = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);

	mData[6].mVertex = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f);
	mData[7].mVertex = glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f);
	mData[8].mVertex = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);
	mData[9].mVertex = glm::vec4(-1.0f, 1.0f, -1.0f,1.0f);
	mData[10].mVertex = glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f);
	mData[11].mVertex = glm::vec4(-1.0f, -1.0f, 1.0f,1.0f);

	mData[12].mVertex = glm::vec4(1.0f, -1.0f, -1.0f,1.0f);
	mData[13].mVertex = glm::vec4(1.0f, -1.0f, 1.0f, 1.0f);
	mData[14].mVertex = glm::vec4(1.0f, 1.0f, 1.0f,  1.0f);
	mData[15].mVertex = glm::vec4(1.0f, 1.0f, 1.0f,  1.0f);
	mData[16].mVertex = glm::vec4(1.0f, 1.0f, -1.0f, 1.0f);
	mData[17].mVertex = glm::vec4(1.0f, -1.0f, -1.0f,1.0f);

	mData[18].mVertex = glm::vec4(-1.0f, -1.0f, 1.0f,1.0f);
	mData[19].mVertex = glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f);
	mData[20].mVertex = glm::vec4(1.0f, 1.0f, 1.0f,  1.0f);
	mData[21].mVertex = glm::vec4(1.0f, 1.0f, 1.0f,  1.0f);
	mData[22].mVertex = glm::vec4(1.0f, -1.0f, 1.0f, 1.0f);
	mData[23].mVertex = glm::vec4(-1.0f, -1.0f, 1.0f,1.0f);

	mData[24].mVertex = glm::vec4(-1.0f, 1.0f, -1.0f,1.0f);
	mData[25].mVertex = glm::vec4(1.0f, 1.0f, -1.0f, 1.0f);
	mData[26].mVertex = glm::vec4(1.0f, 1.0f, 1.0f,  1.0f);
	mData[27].mVertex = glm::vec4(1.0f, 1.0f, 1.0f,  1.0f);
	mData[28].mVertex = glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f);
	mData[29].mVertex = glm::vec4(-1.0f, 1.0f, -1.0f,1.0f);

	mData[30].mVertex = glm::vec4(-1.0f, -1.0f, -1.0f,1.0f);
	mData[31].mVertex = glm::vec4(-1.0f, -1.0f, 1.0f,	1.0f);
	mData[32].mVertex = glm::vec4(1.0f, -1.0f, -1.0f,	1.0f);
	mData[33].mVertex = glm::vec4(1.0f, -1.0f, -1.0f,	1.0f);
	mData[34].mVertex = glm::vec4(-1.0f, -1.0f, 1.0f,	1.0f);
	mData[35].mVertex = glm::vec4(1.0f, -1.0f, 1.0f,	1.0f);

	mVAO->Bind();
	mVBO->Bind();
	mVBO->SetSize(36);
	mVBO->SubmitData(mData, sizeof(VertexDataFull) * 36);

	Shader* shader = new Shader;
	shader->InitBuiltShader(sSkyBoxVS, sSkyBoxFS);

	mMaterial = new Material;
	mMaterial->mBaseRenderPass = new RenderPass;
	mMaterial->mBaseRenderPass->SetShader(shader);
	

	
	mCubeMap = TextureCube::LoadTextureCube(name);
}

void SkyBox::Render(Camera* camera)
{
	mVAO->Bind();
	mVBO->Bind();
	glUseProgram(mMaterial->mBaseRenderPass->mShader->mProgram);
	GlobalRenderState::SetDepthTestState(false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glm::mat4 m = glm::mat4(1.0f);
	m = glm::translate(m, camera->mPosition);
	//m = glm::rotate(m, glm::degrees(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	mMaterial->mBaseRenderPass->SetMatrix4(ModelMatrix.c_str(), glm::value_ptr(m));
	mMaterial->Bind(camera);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mCubeMap->mTextureID);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	mVBO->UnBind();
	mVAO->UnBind();
}
