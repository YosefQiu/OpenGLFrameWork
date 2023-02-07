#include "Scene.h"
#include "MemoryPool/MemoryLabel.h"
#include "MemoryPool/DefaultAllocator.h"
#include "Utils/Tools.h"
#include "RenderState.h"
#include "UI.h"
#include "Camera.h"




Camera* camera;
UI* pUI = nullptr;


glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 targetPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float lastX, lastY;

void Scene::Init(GLFWwindow* wnd)
{
    GlobalRenderState::Init();
    camera = new Camera;
    camera->Init(cameraPos, targetPos, cameraUp);
    pUI = mUI;
}

void Scene::SetViewPortSize(float width, float height)
{
    camera->SwitchTo3D(width, height);
}

void Scene::Render()
{
    camera->Update(GetFrameTime());
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
        QuitMemory();
    }

#pragma region camera interaction
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        camera->mbLeft = true;
    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
        camera->mbLeft = false;
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        camera->mbRight = true;
    if (key == GLFW_KEY_D && action == GLFW_RELEASE)
        camera->mbRight = false;
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        camera->mbForward = true;
    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
        camera->mbForward = false;
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        camera->mbBackward = true;
    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
        camera->mbBackward = false;
#pragma endregion camera interaction

}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    auto& io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        camera->mbMouseLeft = true;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        camera->mbMouseLeft = false;
    }
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    auto& io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return;
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    float angleX = xoffset / 500.0f;
    float angleY = yoffset / 500.0f;
    if (camera->mbMouseLeft) {
        camera->Yaw(glm::radians(-angleX));
        camera->Pitch(glm::radians(-angleY));
    }
    
}
void scroll_callback(GLFWwindow* window, double xpos, double ypos)
{
    auto& io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return;
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    float angleX = xoffset / 500.0f;
    float angleY = yoffset / 500.0f;
}
