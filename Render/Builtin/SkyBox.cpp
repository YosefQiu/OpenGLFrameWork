#include "SkyBox.h"
#include "HardCodedShader.h"
#include "../Camera.h"
SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
	
}

void SkyBox::Init(const char* name)
{
	
	Model::Init((geomerty_path + "Cube.obj").c_str());
	mVAO = new VAO;
	mVAO->Init();
	mVBO = new VBO;
	mVBO->SetSize(mVertexCount);
	VertexDataFull* Data = new VertexDataFull[36];
	Data[0].mVertex = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);
	Data[1].mVertex = glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f);
	Data[2].mVertex = glm::vec4(1.0f, -1.0f, -1.0f, 1.0f);
	Data[3].mVertex = glm::vec4(1.0f, -1.0f, -1.0f, 1.0f);
	Data[4].mVertex = glm::vec4(1.0f, 1.0f, -1.0f, 1.0f);
	Data[5].mVertex = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);

	Data[6].mVertex = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f);
	Data[7].mVertex = glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f);
	Data[8].mVertex = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);
	Data[9].mVertex = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);
	Data[10].mVertex = glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f);
	Data[11].mVertex = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f);

	Data[12].mVertex = glm::vec4(1.0f, -1.0f, -1.0f, 1.0f);
	Data[13].mVertex = glm::vec4(1.0f, -1.0f, 1.0f, 1.0f);
	Data[14].mVertex = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Data[15].mVertex = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Data[16].mVertex = glm::vec4(1.0f, 1.0f, -1.0f, 1.0f);
	Data[17].mVertex = glm::vec4(1.0f, -1.0f, -1.0f, 1.0f);

	Data[18].mVertex = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f);
	Data[19].mVertex = glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f);
	Data[20].mVertex = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Data[21].mVertex = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Data[22].mVertex = glm::vec4(1.0f, -1.0f, 1.0f, 1.0f);
	Data[23].mVertex = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f);

	Data[24].mVertex = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);
	Data[25].mVertex = glm::vec4(1.0f, 1.0f, -1.0f, 1.0f);
	Data[26].mVertex = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Data[27].mVertex = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Data[28].mVertex = glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f);
	Data[29].mVertex = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);

	Data[30].mVertex = glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f);
	Data[31].mVertex = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f);
	Data[32].mVertex = glm::vec4(1.0f, -1.0f, -1.0f, 1.0f);
	Data[33].mVertex = glm::vec4(1.0f, -1.0f, -1.0f, 1.0f);
	Data[34].mVertex = glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f);
	Data[35].mVertex = glm::vec4(1.0f, -1.0f, 1.0f, 1.0f);
	mVBO->SubmitData(Data, VertexDataLength * mVertexCount);

	Shader* shader = new Shader;
	shader->InitBuiltShader(sSkyBoxVS, sSkyBoxFS);
	mMaterial = new Material;
	mMaterial->mBaseRenderPass = new RenderPass;
	mMaterial->mBaseRenderPass->SetShader(shader);
	mCubeMap = TextureCube::LoadTextureCube(name, name);
	mMaterial->mBaseRenderPass->SetSamplerCube("U_Texture", mCubeMap->mTextureID);

	mDraw = new DrawCall;
	mDraw->mVAO = mVAO;
	mDraw->mVBO = mVBO;
	mDraw->mMaterial = mMaterial;

}

void SkyBox::Render(Camera* camera)
{
	glDepthFunc(GL_LEQUAL);
	/*glm::mat4 m = glm::mat4(1.0f);
	mModelMatrix = glm::translate(m, camera->GetPosition());
	mDraw->mMaterial->SetMatrix4(ModelMatrix.c_str(), mModelMatrix);*/
	mDraw->Draw(camera);
	glDepthFunc(GL_LESS);
}
