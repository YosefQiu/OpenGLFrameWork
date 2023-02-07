#include "Sphere.h"
#include "../Utils/Tools.h"
#include "../Utils/GLMath.h"
PBA::Sphere2D::Sphere2D()
{
	mVAO = nullptr;
	mVBO = nullptr;
	mEBO = nullptr;
	mMaterial = nullptr;
	mDC = nullptr;
}

PBA::Sphere2D::Sphere2D(glm::vec2 center, float r):mCenter(center), mRadius(r)
{
	
	mMass = 0.0f;
	mVelocity = glm::vec2(0.0f);
	
}

void PBA::Sphere2D::Init()
{
	mDC = new DrawCall;
	mVAO = new VAO;
	mVAO->Init();
	mVBO = new VBO;
	int split = mSplit;
	mVertexCount = split * 3;
	mData = new VertexDataFull[split * 3];

	for (int i = 0; i < split * 3; i = i + 3)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(split);

		float x = mRadius * cosf(theta);
		float y = mRadius * sinf(theta);

		mData[i + 0].mVertex = glm::vec4(mCenter.x, mCenter.y, -2.0f, 1.0f);
		mData[i + 1].mVertex = glm::vec4(mCenter.x + x, mCenter.y + y, -2.0f, 1.0f);
		mData[i + 2].mVertex = glm::vec4(mCenter.x, mCenter.y, -2.0f, 1.0f);
	}



	mVBO->SetSize(mVertexCount);
	mVBO->SubmitData(mData, sizeof(VertexDataFull) * mVertexCount);

	mMaterial = new Material;
	mMaterial->mBaseRenderPass = new RenderPass;

	mDC->mVAO = mVAO;
	mDC->mVBO = mVBO;
	mDC->mMaterial = mMaterial;


	float m = 1;
	for (int i = 0; i < mVertexCount; i = i + 3)
	{
		mMass += m;
		float diag = m * GM::sqrMagnitude(mData[i].mVertex);
		mIRef[0][0] += diag;
		mIRef[1][1] += diag;
		mIRef[2][2] += diag;
		mIRef[0][0] -= m * mData[i].mVertex[0] * mData[i].mVertex[0];
		mIRef[0][1] -= m * mData[i].mVertex[0] * mData[i].mVertex[1];
		mIRef[0][2] -= m * mData[i].mVertex[0] * mData[i].mVertex[2];
		mIRef[1][0] -= m * mData[i].mVertex[1] * mData[i].mVertex[0];
		mIRef[1][1] -= m * mData[i].mVertex[1] * mData[i].mVertex[1];
		mIRef[1][2] -= m * mData[i].mVertex[1] * mData[i].mVertex[2];
		mIRef[2][0] -= m * mData[i].mVertex[2] * mData[i].mVertex[0];
		mIRef[2][1] -= m * mData[i].mVertex[2] * mData[i].mVertex[1];
		mIRef[2][2] -= m * mData[i].mVertex[2] * mData[i].mVertex[2];
	}
	mIRef[3][3] = 1.0f;
	mVelocity = glm::vec2(0.0f);
	//mGravity = glm::vec2(0, -mMass * mG);
}


glm::vec2 PBA::Sphere2D::Move(float dt, glm::vec2 force)
{
	if (!this->mbStuck && !this->mbExternalForce)
	{
		//** 一开始只有重力 F=-mg=ma => a = -g = -10.0f
		//** v = at + v0
		//** x = 1/2at^2 + v0t + x0
		// std::cout << "进入第一情况" << std::endl;
		/*glm::vec2 total = mGravity;
		glm::vec2 a = mGravity / mMass;
		glm::vec2 v0 = this->mVelocity;
		glm::vec2 x0 = this->mCenter;
		mTotalForce = mGravity;
		this->mVelocity = v0 + a * dt;
		this->mVelocity *= mLinear_decay;
		glm::vec2 tmp_pos = 0.5f * a * dt * dt + v0 * dt;
		this->mCenter = x0 + tmp_pos;*/
		glm::vec2 new_pos = glm::vec2(0.0f);
		glm::vec2 new_v = glm::vec2(0.0f);
		int collision_wall;
		float f = -1;

		float timestep_remain = dt;
		float timestep = timestep_remain;
		int t = 2;
		while (t--)
		{
			mAcceleration = mGravity - ((0.2f / mMass) * mVelocity);
		
			new_v = mVelocity + timestep_remain * mAcceleration;
			bool flat = false;
			new_pos = mCenter + timestep_remain * mVelocity;
			if (this->mCenter.y >= 0.75f)
			{
				this->mVelocity.y = -this->mVelocity.y;
				flat = true;
			}
			if (this->mCenter.y <= -0.75f)
			{
				this->mVelocity.y = -this->mVelocity.y; flat = true;
			}
			
			if (this->mCenter.x >= 1.25f)
			{
				this->mVelocity.x = -this->mVelocity.x; flat = true;
			}
			if (this->mCenter.x <= -1.25f)
			{
				this->mVelocity.x = -this->mVelocity.x; flat = true;
			}
			if (flat != true)
			{
				mCenter = new_pos;
				mVelocity = new_v;
				timestep_remain -= timestep;
			}
			
		}


		
	}
	//if (!this->mbStuck && this->mbExternalForce)
	//{
	//	//std::cout << "进入第二情况" << std::endl;
	//	//mbExternalForce = false;
	//	//** 考虑有外力的情况
	//	//** 1. 力的计算（根据箭头的长度和方向）mExternalForce

	//	mTotalForce = mTotalForce + mExternalForce;
	//	glm::vec2 v0 = this->mVelocity;
	//	glm::vec2 x0 = this->mCenter;
	//	glm::vec2 total_force = mTotalForce;
	//	glm::vec2 a = total_force / mMass;
	//	this->mVelocity = v0 + a * dt;
	//	glm::vec2 tmp_pos = 0.5f * a * dt * dt + v0 * dt;
	//	this->mCenter = x0 + tmp_pos;
	//	if (this->mCenter.y <= -0.75f)
	//	{
	//		this->mVelocity.y = -this->mVelocity.y;
	//		this->mTotalForce.y += 3600.0f;
	//	}
	//	if (this->mCenter.y >= 0.75f)
	//	{
	//		this->mVelocity.y = -this->mVelocity.y;
	//		this->mTotalForce.y -= 3600.0f;
	//	}
	//	if (this->mCenter.x >= 1.25f)
	//	{
	//		this->mVelocity.x = -this->mVelocity.x;
	//		this->mTotalForce.x += 3600.0f;
	//	}
	//	if (this->mCenter.x <= -1.25f)
	//	{
	//		this->mVelocity.x = -this->mVelocity.x;
	//		this->mTotalForce.x -= 3600.0f;
	//	}
	//}
	
	return this->mCenter;
}

void PBA::Sphere2D::Update()
{
	mVAO->Bind();
	mVBO->Bind();


	for (int i = 0; i < mSplit * 3; i = i + 3)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(mSplit);

		float x = mRadius * cosf(theta);
		float y = mRadius * sinf(theta);

		mData[i + 0].mVertex = glm::vec4(mCenter.x, mCenter.y, -2.0f, 1.0f);
		mData[i + 1].mVertex = glm::vec4(mCenter.x + x, mCenter.y + y, -2.0f, 1.0f);
		mData[i + 2].mVertex = glm::vec4(mCenter.x, mCenter.y, -2.0f, 1.0f);
	}

	mVBO->SubmitData(mData, sizeof(VertexDataFull) * mVertexCount);
	mDC->mVAO = mVAO;
	mDC->mVBO = mVBO;
}
