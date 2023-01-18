#pragma once
#include "YosefGL.h"
#include "YosefPrefix.h"
#pragma once
#include "Camera.h"


class Camera
{
public:
    glm::vec3 mPosition;
    glm::vec3 mTarget;
    glm::vec3 mUp;
    glm::mat4 mViewMatrix = glm::mat4(1.0f);
    glm::mat4 mProjectionMatrix = glm::mat4(1.0f);
    float mMoveSpeed;
    bool mbForward, mbBackward, mbLeft, mbRight, mbMouseLeft = false;
public:
    Camera();
    virtual ~Camera() {}
public:
    void Init(glm::vec3 pos, glm::vec3 target, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
    void Update(float delta);
    void Pitch(float angle);
    void Yaw(float angle);
    void RotateView(float angle, float x, float y, float z);
    void SetMoveSpeed(float speed);
    void ChangePosition(glm::vec3 pos);
    void ChangeTarget(glm::vec3 target);
    glm::mat4& GetViewMatrix();
    glm::mat4& GetProjMatrix();
    glm::vec3& GetPosition();
    void SwitchTo2D(float width, float height);
    void SwitchTo3D(float width, float height);
};