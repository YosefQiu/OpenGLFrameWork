#pragma once

#include "../YosefPrefix.h"
#include "../YosefGL.h"

#include "../GL30/VAO.h"
#include "../GL30/VBO.h"
#include "../GL30/EBO.h"
#include "../GL30/FBO.h"
#include "../GL30/Texture2D.h"
#include "../VertexData.h"
#include "../RenderState.h"
#include "../model.h"
#include "../Material.h"
#include "../DrawCall.h"
#include "../model.h"
namespace PBA
{
	class GameObject : public Object
	{
	public:
		// object state
		glm::vec2   Position, Size, Velocity;
		glm::vec3   Color;
		float       Rotation;
		bool        IsSolid;
		bool        Destroyed;
	};

	class Sphere2D : public GameObject
	{
	public:
		int mSplit = 360;
		float mMass;
		float mRadius;
		float mLinear_decay = 1.0f;
		float mAngular_decay = 0.98f;
		float mRestitution = 0.5f;
		bool mbStuck = false;
		bool mbExternalForce = false;
		glm::vec2 mCenter;
		glm::vec2 mVelocity;
		glm::vec2 mAcceleration;
		glm::vec2 mG = glm::vec2(0.0f, -9.8f);
		glm::vec2 mExternalForce = glm::vec2(0.0f);
		glm::vec2 mTotalForce = glm::vec2(0.0f);
		glm::vec2 mGravity;
		glm::mat4 mIRef = glm::mat4(1.0f);
	public:
		Sphere2D();
		Sphere2D(glm::vec2 center, float r);
		void Init();
		glm::vec2 Move(float dt, glm::vec2 force = glm::vec2(0.0f));
		void Update();
		void Reset(glm::vec2 center, float r, glm::vec2 velocity);
	};
}

