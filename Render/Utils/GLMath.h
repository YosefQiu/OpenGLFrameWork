#pragma once
#include "../YosefGL.h"

namespace GM
{
	typedef std::default_random_engine sampler;
    extern std::uniform_real_distribution<float> distribution;

	inline float sqrMagnitude(glm::vec2 v1)
	{
		return v1.x * v1.x + v1.y * v1.y;
	}
	inline float sqrMagnitude(glm::vec3 v1)
	{
		return v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
	}
	inline float sqrMagnitude(glm::vec4 v1)
	{
		return v1.x * v1.x + v1.y * v1.y + v1.z * v1.z + v1.w * v1.w;
	}
	inline float sqrMagnitude(glm::vec2 v1, glm::vec2 v2)
	{
		return (v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y);
	}
	inline float sqrMagnitude(glm::vec3 v1, glm::vec3 v2)
	{
		return (v2.x - v1.x)* (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y) + (v2.z - v1.z) * (v2.z - v1.z);
	}
	inline float sqrMagnitude(glm::vec4 v1, glm::vec4 v2)
	{
		return (v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y) + (v2.z - v1.z) * (v2.z - v1.z) + (v2.w - v1.w) * (v2.w - v1.w);
	}
	inline float randZeroOne()
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> dist(0.0, 1.0);
		return dist(mt);
	}
	inline float randMinusOne()
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> dist(-1.0, 1.0);
		return dist(mt);
	}
	inline float clamp(float val, float lower, float upper)
	{
		return val < lower ? lower : val > upper ? upper : val;
	}
	inline float mod(float x, float y)
	{
		return x - y * floor(x / y);
	}
	inline float GetUniform1D(sampler& state)
	{
		return distribution(state);
	}
	inline float signed_sqrt(float val)
	{
		if (val < 0) return -sqrt(val);
		else return sqrt(val);
	}
	inline glm::vec2 GetUniform2D(sampler& state)
	{
		return glm::vec2(distribution(state), distribution(state));
	}
	inline glm::vec2 GetUnitDiskSample(sampler& state)
	{
		float r1 = GetUniform1D(state);
		float r2 = GetUniform1D(state);
		float R = sqrt(r1);
		float theta = 2 * glm::pi<float>() * r2;

		glm::vec2 p = glm::vec2(R * cos(theta), R * sin(theta));
		return p;
	}
	inline glm::vec3 GetTriangleSample(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, sampler& state)
	{
		float e1 = GetUniform1D(state);
		float e2 = GetUniform1D(state);
		float beta = e2 * sqrt(1 - e1);
		float gamma = 1 - sqrt(1 - e1);

		glm::vec3 A = v0;
		glm::vec3 B = v1;
		glm::vec3 C = v2;
		glm::vec3 p = A + beta * (B - A) + gamma * (C - A);
		return p;
	}
	inline glm::vec3 GetHemisphereSample(const glm::vec3& N, sampler& state)
	{
		glm::vec3 u = glm::normalize(glm::cross(fabs(N.x) > 0.1 ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0), N));
		glm::vec3 v = cross(N, u);
		float phi = 2 * glm::pi<float>() * GetUniform1D(state); // pick random number on unit circle (radius = 1, circumference = 2*Pi) for azimuth
		float z = GetUniform1D(state);  // pick random number for elevation [0,1]
		float r = sqrt(std::max(1 - z * z, 0.f));

		glm::vec3 d = u * cos(phi) * r + v * sin(phi) * r + N * z;
		return glm::normalize(d);
	}
	inline glm::vec3 GetUniform3D(sampler& state)
	{
		return glm::vec3(distribution(state), distribution(state), distribution(state));
	}
	inline glm::vec3 triNormal(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2)
	{
		return glm::cross(v1 - v0, v2 - v0);
	}
	inline glm::vec3 GetSphereSample(const glm::vec3& N, sampler& state)
	{
		glm::vec3 u = glm::normalize(glm::cross(fabs(N.x) > 0.1 ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0), N));
		glm::vec3 v = cross(N, u);
		float phi = 2 * glm::pi<float>() * GetUniform1D(state); // pick random number on unit circle (radius = 1, circumference = 2*Pi) for azimuth
		float z = 1 - 2 * GetUniform1D(state);  // pick random number for elevation [-1,1]
		float r = sqrt(std::max(1 - z * z, 0.f));

		glm::vec3 d = u * cos(phi) * r + v * sin(phi) * r + N * z;
		return glm::normalize(d);
	}
	inline glm::mat3 FromToMatrix3(glm::vec3 from, glm::vec3 to)
	{
		glm::mat3 mtx = glm::mat4(1.0f);
		float e, h;
		glm::vec3 v = glm::cross(from, to);
		e = glm::dot(from, to);
		if (e > 1.0 - glm::epsilon<float>())
		{
			mtx[0][0] = 1.0; mtx[0][1] = 0.0; mtx[0][2] = 0.0;
			mtx[1][0] = 0.0; mtx[1][1] = 1.0; mtx[1][2] = 0.0;
			mtx[2][0] = 0.0; mtx[2][1] = 0.0; mtx[2][2] = 1.0;
		}
		else if (e < -1.0 + glm::epsilon<float>())
		{
			glm::vec3 up = glm::vec3(0.0f);
			glm::vec3 left = glm::vec3(0.0f);
			float invlen;
			float fxx, fyy, fzz, fxy, fxz, fyz;
			float uxx, uyy, uzz, uxy, uxz, uyz;
			float lxx, lyy, lzz, lxy, lxz, lyz;
			left[0] = 0.0; left[1] = from[2]; left[2] = -from[1];
			if (glm::dot(left, left) < glm::epsilon<float>())
			{
				left[0] = -from[2]; left[1] = 0.0; left[2] = from[0];
			}
			invlen = 1.0f / sqrt(glm::dot(left, left));
			left[0] *= invlen;
			left[1] *= invlen;
			left[2] *= invlen;
			up = glm::cross(left, from);
			fxx = -from[0] * from[0]; fyy = -from[1] * from[1]; fzz = -from[2] * from[2];
			fxy = -from[0] * from[1]; fxz = -from[0] * from[2]; fyz = -from[1] * from[2];
			uxx = up[0] * up[0]; uyy = up[1] * up[1]; uzz = up[2] * up[2];
			uxy = up[0] * up[1]; uxz = up[0] * up[2]; uyz = up[1] * up[2];
			lxx = -left[0] * left[0]; lyy = -left[1] * left[1]; lzz = -left[2] * left[2];
			lxy = -left[0] * left[1]; lxz = -left[0] * left[2]; lyz = -left[1] * left[2];
			mtx[0][0] = fxx + uxx + lxx; mtx[0][1] = fxy + uxy + lxy; mtx[0][2] = fxz + uxz + lxz;
			mtx[1][0] = mtx[0][1];   mtx[1][1] = fyy + uyy + lyy; mtx[1][2] = fyz + uyz + lyz;
			mtx[2][0] = mtx[0][2];   mtx[2][1] = mtx[1][2];   mtx[2][2] = fzz + uzz + lzz;
		}
		else
		{
			float hvx, hvz, hvxy, hvxz, hvyz;
			h = (1.0f - e) / glm::dot(v, v);
			hvx = h * v[0];
			hvz = h * v[2];
			hvxy = hvx * v[1];
			hvxz = hvx * v[2];
			hvyz = hvz * v[1];
			mtx[0][0] = e + hvx * v[0]; mtx[0][1] = hvxy - v[2];     mtx[0][2] = hvxz + v[1];
			mtx[1][0] = hvxy + v[2];  mtx[1][1] = e + h * v[1] * v[1]; mtx[1][2] = hvyz - v[0];
			mtx[2][0] = hvxz - v[1];  mtx[2][1] = hvyz + v[0];     mtx[2][2] = e + hvz * v[2];
		}
		return mtx;
	}
	inline glm::mat4 FromToMatrix4(glm::vec3 from, glm::vec3 to)
	{
		glm::mat3 mtx = FromToMatrix3(from, to);
		glm::mat4 rotateMat;

		rotateMat[0][0] = mtx[0][0];	rotateMat[0][1] = mtx[0][1];	rotateMat[0][2] = mtx[0][2];	rotateMat[0][3] = 0.0f;
		rotateMat[1][0] = mtx[1][0];	rotateMat[1][1] = mtx[1][1];	rotateMat[1][2] = mtx[1][2];	rotateMat[1][3] = 0.0f;
		rotateMat[2][0] = mtx[2][0];	rotateMat[2][1] = mtx[2][1];	rotateMat[2][2] = mtx[2][2];	rotateMat[2][3] = 0.0f;
		rotateMat[3][0] = 0.0f;			rotateMat[3][1] = 0.0f;			rotateMat[3][2] = 0.0f;			rotateMat[3][3] = 1.0f;
		return rotateMat;
	}
	inline void CoordinateSystem(const glm::vec3& v1, glm::vec3* v2, glm::vec3* v3)
	{
		if (std::abs(v1.x) > std::abs(v1.y))
			*v2 = glm::vec3(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
		else
			*v2 = glm::vec3(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
		*v3 = glm::cross(v1, *v2);
	}
	inline char sgn(float val)
	{
		return val >= 0 ? 0 : 1;
	}

}
