#include "FullScreenQuad.h"
#include "HardCodedShader.h"
FullScreenQuad::~FullScreenQuad()
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
	if (mEBO)
	{
		delete mEBO;
		mEBO = nullptr;
	}
	if (mShader)
	{
		delete mVAO;
		mShader = nullptr;
	}
	if (mMaterial)
	{
		delete mMaterial;
		mMaterial = nullptr;
	}
}

void FullScreenQuad::InitWithBuiltShader()
{
	mVAO = new VAO;
	mVAO->Init();

	mVBO = new VBO();
	mData = new VertexDataFull[4];

	mData[0].mTexCoord0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	mData[1].mTexCoord0 = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	mData[2].mTexCoord0 = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	mData[3].mTexCoord0 = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);


	mShader = new Shader;
	mShader->InitBuiltShader(sQuadDebugVS, sQuadDebugFS);

	mMaterial = new Material;
	mMaterial->mBaseRenderPass = new RenderPass;
	mMaterial->mBaseRenderPass->SetShader(mShader);
}

void FullScreenQuad::Init(const char* vsPath, const char* fsPath)
{
	mVAO = new VAO;
	mVAO->Init();

	mVBO = new VBO();
	mData = new VertexDataFull[4];

	mData[0].mTexCoord0 = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	mData[1].mTexCoord0 = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	mData[2].mTexCoord0 = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	mData[3].mTexCoord0 = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);


	mShader = new Shader;
	mShader->Init(vsPath, fsPath);
	mMaterial = new Material;
	mMaterial->mBaseRenderPass = new RenderPass;
	mMaterial->mBaseRenderPass->SetShader(mShader);
}
void FullScreenQuad::Render(bool bflag)
{
	mVAO->Bind();
	mVBO->Bind();

	if (bflag)
	{
		bRenderDepthBuffer = bflag;
		mMaterial->mBaseRenderPass->SetBool("bDepth", bRenderDepthBuffer);
	}
		

	mMaterial->mBaseRenderPass->Bind(nullptr); 


	if (mEBO == nullptr)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 0, mVBO->mVertexCount);
	}

}

void FullScreenQuad::Bind(QuadType type)
{
	switch (type)
	{
	case QuadType::kFullScreen:
		{
			mData[0].mVertex = glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f);
			mData[1].mVertex = glm::vec4( 1.0f, -1.0f, 0.0f, 1.0f);
			mData[2].mVertex = glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f);
			mData[3].mVertex = glm::vec4( 1.0f, 1.0f, 0.0f, 1.0f);

			mVAO->Bind();
			mVBO->Bind();
			mVBO->SetSize(4);
			mVBO->SubmitData(mData, sizeof(VertexDataFull) * 4);
		}
		break;
	case QuadType::kLetfTop:
	{
		mData[0].mVertex = glm::vec4(-1.0f, 0.0f, -1.0f, 1.0f);
		mData[1].mVertex = glm::vec4( 0.0f, 0.0f, -1.0f, 1.0f);
		mData[2].mVertex = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);
		mData[3].mVertex = glm::vec4( 0.0f, 1.0f, -1.0f, 1.0f);

		mVAO->Bind();
		mVBO->Bind();
		mVBO->SetSize(4);
		mVBO->SubmitData(mData, sizeof(VertexDataFull) * 4);
	}
	break;
	case QuadType::kLeftBottom:
	{
		mData[0].mVertex = glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f);
		mData[1].mVertex = glm::vec4(0.0f, -1.0f, -1.0f, 1.0f);
		mData[2].mVertex = glm::vec4(-1.0f, 0.0f, -1.0f, 1.0f);
		mData[3].mVertex = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);

		

		mVAO->Bind();
		mVBO->Bind();
		mVBO->SetSize(4);
		mVBO->SubmitData(mData, sizeof(VertexDataFull) * 4);
	}
	break;
	case QuadType::kRightTop:
	{
		mData[0].mVertex = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
		mData[1].mVertex = glm::vec4(1.0f, 0.0f, -1.0f, 1.0f);
		mData[2].mVertex = glm::vec4(0.0f, 1.0f, -1.0f, 1.0f);
		mData[3].mVertex = glm::vec4(1.0f, 1.0f, -1.0f, 1.0f);

		mVAO->Bind();
		mVBO->Bind();
		mVBO->SetSize(4);
		mVBO->SubmitData(mData, sizeof(VertexDataFull) * 4);
	}
	break;
	case QuadType::kRightBottom:
	{
		mData[0].mVertex = glm::vec4(0.0f, -1.0f, -1.0f, 1.0f);
		mData[1].mVertex = glm::vec4(1.0f, -1.0f, -1.0f, 1.0f);
		mData[2].mVertex = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
		mData[3].mVertex = glm::vec4(1.0f, 0.0f, -1.0f, 1.0f);

		mVAO->Bind();
		mVBO->Bind();
		mVBO->SetSize(4);
		mVBO->SubmitData(mData, sizeof(VertexDataFull) * 4);
	}
	break;
	}
}
	

