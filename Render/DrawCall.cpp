#include "DrawCall.h"
#include "Light.h"
DrawCall::DrawCall() 
{
	mVAO = nullptr;
	mVBO = nullptr;
	mEBO = nullptr;
	mMaterial = nullptr;
}
void DrawCall::Draw(Camera* camera, GLenum polygon)
{
	mVAO->Bind();
	mVBO->Bind();
	
	mMaterial->mBaseRenderPass->Bind(camera); // program ->bind
	
	
	if (mEBO == nullptr) 
	{
		glDrawArrays(polygon, 0, mVBO->mVertexCount);
	}
	

	if (mMaterial->mAdditiveRenderPass != nullptr)
	{
		
		
		for (auto iter = Light::mLights.begin(); iter != Light::mLights.end(); iter++)
		{
			// light->bind()
			if (mEBO == nullptr)
			{
				glDrawArrays(polygon, 0, mVBO->mVertexCount);
			}
		}
	}
	
	// deffered

	mVBO->UnBind();
	if (mNext != nullptr)
	{
		Next<DrawCall>()->Draw(camera, polygon);
	}
	
	
}