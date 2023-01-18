#include "DrawCall.h"
#include "Light.h"
DrawCall::DrawCall() 
{
	mVAO = nullptr;
	mVBO = nullptr;
	mEBO = nullptr;
	mMaterial = nullptr;
}
void DrawCall::Draw(Camera* camera)
{
	mVAO->Bind();
	mVBO->Bind();
	// set main light
	// material->base->bind(camera)
	// vbo->draw
	mMaterial->mBaseRenderPass->Bind(camera); // program ->bind
	// lightmaps ->bind()
	// ambient , emissive
	// shadow map

	// Light::mMainLight ->bind()
	
	if (mEBO == nullptr) 
	{
		glDrawArrays(GL_TRIANGLES, 0, mVBO->mVertexCount);
	}
	//for light in lights
	//   set light state
	//   material->add->bind(camera)
	//   vbo->draw

	if (mMaterial->mAdditiveRenderPass != nullptr)
	{
		
		// fo light in lights
		for (auto iter = Light::mLights.begin(); iter != Light::mLights.end(); iter++)
		{
			// light->bind()
			if (mEBO == nullptr)
			{
				glDrawArrays(GL_TRIANGLES, 0, mVBO->mVertexCount);
			}
		}
	}
	
	// deffered

	mVBO->UnBind();
	if (mNext != nullptr)
	{
		Next<DrawCall>()->Draw(camera);
	}
	
	
}