#include "Particle.h"
#include "HardCodedShader.h"
#include "../Camera.h"
Arrow::Arrow()
{

	mVAO = nullptr;
	mVBO = nullptr;
	mMaterial = nullptr;
}

Arrow::~Arrow()
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

void Arrow::Init()
{
	mVAO = new VAO;
	mVAO->Init();

	mVBO = new VBO;

	float radius = 0.05f;
	float height = 1.0f;
	int slices = 16;
	int stacks = 16;
	std::vector<float> arrowVertices;
	float PI = glm::pi<float>();
	int total_count = (slices + 1) * (stacks + 1) + (slices + 1);
	mData = new VertexDataFull[total_count];
	int count = 0;
	for (int i = 0; i <= stacks; i++)
	{
		float xy = radius * cos(i * PI / stacks);
		float z = height * i / stacks;
		for (int j = 0; j <= slices; j++)
		{
			float x = xy * cos(2 * j * PI / slices);
			float y = xy * sin(2 * j * PI / slices);
			mData[count].mVertex = glm::vec4(x, y, z, 1.0f);
			mData[count].mNormal = glm::vec4(1.0f);
		}
	}

	float coneRadius = 0.1f;
	float coneHeight = 0.2f;
	std::vector<float> coneVertices;
	for (int i = 0; i <= slices; i++)
	{
		float x = coneRadius * cos(2 * i * PI / slices);
		float y = coneRadius * sin(2 * i * PI / slices);
		coneVertices.push_back(x);
		coneVertices.push_back(y);
		coneVertices.push_back(0.0f);
		coneVertices.push_back(0.0f);
		coneVertices.push_back(0.0f);
		coneVertices.push_back(coneHeight);
	}


	
	mVAO->Bind();
	mVBO->Bind();
	mVBO->SetSize(0);
	mVBO->SubmitData(mData, sizeof(VertexDataFull) * 0);

	Shader* shader = new Shader;
	shader->InitBuiltShader(sSkyBoxVS, sSkyBoxFS);

	mMaterial = new Material;
	mMaterial->mBaseRenderPass = new RenderPass;
	mMaterial->mBaseRenderPass->SetShader(shader);



}

void Arrow::Render(Camera* camera)
{
	mVAO->Bind();
	mVBO->Bind();

	mMaterial->Bind(camera);

	glDrawArrays(GL_POINTS, 0, 0);
	mVBO->UnBind();
	mVAO->UnBind();
}
