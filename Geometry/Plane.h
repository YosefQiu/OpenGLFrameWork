#pragma once
#include "../YosefGL.h"
#include "../YosefPrefix.h"

class Plane {
public:
	glm::vec3 normal;
	float distance;
	const float& a()const { return normal.x; }
	const float& b()const { return normal.y; }
	const float& c()const { return normal.z; }
	const float& d() const { return distance; }
	float& d() { return distance; }
	const glm::vec3& getNormal()const { return normal; }
	Plane() { }
	Plane(float a, float b, float c, float d) { normal.x = a; normal.y = b; normal.z = c; distance = d; }
	Plane& operator *= (float scale);
	bool operator == (const Plane& p) { return normal == p.normal && distance == p.distance; }
	bool operator != (const Plane& p) { return normal != p.normal || distance != p.distance; }
	void setInvalid() { normal = glm::vec3(0, 0, 0); distance = 0.0F; }

	void setABCD(const float a, const float b, const float c, const float d);
	void Normalize();
	void setNormalAndPosition(const glm::vec3& inNormal, const glm::vec3& inPoint);
	float getDistanceToPoint(const glm::vec3& inPt) const;
	bool getSide(const glm::vec3& inPt) const;
};
inline float Plane::getDistanceToPoint(const glm::vec3& inPt)const {
	return glm::dot(normal, inPt) + distance;
}

inline bool Plane::getSide(const glm::vec3& inPt) const
{
	return glm::dot(normal, inPt) + distance > 0.0F;
}

inline void Plane::setNormalAndPosition(const glm::vec3& inNormal, const glm::vec3& inPoint)
{
	normal = inNormal;
	distance = -glm::dot(inNormal, inPoint);
}
inline Plane& Plane::operator *= (float scale)
{
	normal *= scale;
	distance *= scale;
	return *this;
}
inline void Plane::setABCD(float a, float b, float c, float d) {
	normal = glm::vec3(a, b, c);
	distance = d;
}
inline void Plane::Normalize()
{
	float invMag = 1.0f / glm::length(normal);
	normal *= invMag;
	distance *= invMag;
}