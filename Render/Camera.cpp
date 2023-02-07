#include "Camera.h"

Camera::Camera() 
{
    mPosition = glm::vec3(0.0f, 4.0f, 0.0f);
    mTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    mUp = glm::vec3(0.0f, 1.0f, 0.0f);
    mMoveSpeed = 0.1f;
 }

void Camera::Init(glm::vec3 pos, glm::vec3 target, glm::vec3 up)
{
    mPosition = pos;
    mTarget = target;
    mUp = up;
 }
void Camera::Update(float delta) 
{
    glm::vec3 viewDir = mTarget - mPosition;
    glm::normalize(viewDir);
    glm::vec3 rightDir = glm::cross(viewDir, mUp);
    glm::normalize(rightDir);
    float factor = mMoveSpeed * delta;
    if (mbForward)
    {
        glm::vec3 distance = viewDir * factor;
        mPosition = mPosition + distance;
        mTarget = mTarget + distance;
    }
    if (mbBackward)
    {
        glm::vec3 distance = viewDir * factor;
        mPosition = mPosition - distance;
        mTarget = mTarget - distance;
    }
    if (mbLeft)
    {
        glm::vec3 distance = rightDir * factor;
        mPosition = mPosition + distance;
        mTarget = mTarget + distance;
    }
    if (mbRight) 
    {
        glm::vec3 distance = rightDir * factor;
        mPosition = mPosition - distance;
        mTarget = mTarget - distance;
    }
    mViewMatrix = glm::lookAt(mPosition, mTarget, mUp);
}
void Camera::Pitch(float angle)
{
    glm::vec3 viewDir = mTarget - mPosition;
    glm::normalize(viewDir);
    glm::vec3 rightDir = glm::cross(viewDir, mUp);
    glm::normalize(rightDir);
    RotateView(angle, rightDir.x, rightDir.y, rightDir.z);
}
void Camera::Yaw(float angle) 
{
    RotateView(angle, mUp.x, mUp.y, mUp.z);
}
void Camera::RotateView(float angle, float x, float y, float z)
{
    glm::vec3 viewDir = mTarget - mPosition;
    glm::normalize(viewDir);
    glm::vec3 newDir = glm::vec3(0.0f, 0.0f, 0.0f);
    float C = cosf(angle);
    float S = sinf(angle);
    glm::vec3 tmpX = glm::vec3(C + x * x * (1 - C), x * y * (1 - C) - z * S, x * z * (1 - C) + y * S);
    glm::vec3 tmpY = glm::vec3(x * y * (1 - C) + z * S, C + y * y * (1 - C), y * z * (1 - C) - x * S);
    glm::vec3 tmpZ = glm::vec3(x * z * (1 - C) - y * S, y * z * (1 - C) + x * S, C + z * z * (1 - C));
    newDir.x = glm::dot(tmpX, viewDir);
    newDir.y = glm::dot(tmpY, viewDir);
    newDir.z = glm::dot(tmpZ, viewDir);
    mTarget = mPosition + newDir;
}
void Camera::SetMoveSpeed(float speed)
{
    mMoveSpeed = speed;
}
void Camera::ChangePosition(glm::vec3 pos)
{
    Init(pos, mTarget);
}
void Camera::ChangeTarget(glm::vec3 target) 
{
    Init(mPosition, target);
}
glm::mat4& Camera::GetViewMatrix()
{
    return mViewMatrix;
}
glm::mat4& Camera::GetProjMatrix()
{
    return mProjectionMatrix;
}
glm::vec3& Camera::GetPosition()
{
    return mPosition;
}
void Camera::SwitchTo2D(float width, float height)
{
    mProjectionMatrix = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, -1000.0f, 1000.0f);
}
void Camera::SwitchTo3D(float width, float height)
{
    mProjectionMatrix = glm::perspective(glm::radians(40.0f), (float)width / (float)height, 0.1f, 1000.0f);
}
