#include "Scene.h"
#include "MemoryPool/MemoryLabel.h"
#include "MemoryPool/DefaultAllocator.h"
#include "GL30/VAO.h"
#include "GL30/VBO.h"
#include "GL30/EBO.h"
#include "GL30/FBO.h"
#include "GL30/Texture2D.h"
#include "VertexData.h"
#include "RenderState.h"
#include "model.h"
#include "Material.h"
#include "DrawCall.h"
#include "Light.h"
#include "Camera.h"
#include "Builtin/SkyBox.h"
#include "Builtin/FullScreenQuad.h"
#include "Builtin/Ground.h"
#include "Utils/Tools.h"
#include "UI.h"
Material* material = nullptr; 

float lastX = 1280.0f / 2.0f;
float lastY = 720.0f / 2.0;
VAO* vao = nullptr;
VBO* vbo = nullptr;
FBO* fsqfbo = nullptr;
FullScreenQuad* fsq = nullptr;
FullScreenQuad* test_Texture = nullptr;
Texture2D* test_Texture_img = nullptr;
glm::mat4 m = glm::mat4(1.0f);
SkyBox* skybox = nullptr;
Ground* ground = nullptr;
Camera* camera = nullptr;
DrawCall dc;


glm::vec3 cameraPos = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 targetPos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

void Scene::Init()
{
	GlobalRenderState::Init();
	
	

	Model model;
	model.Init("Res/Sphere.obj");
	vao = new VAO;
	vao->Init();
	vbo = new VBO();
	vbo->SetSize(model.mVertexCount);
	vbo->SubmitData(model.mData, sizeof(VertexDataFull) * model.mVertexCount);
	
	
	
	m = glm::translate(m, glm::vec3(0.0f, 0.0f, -3.0f));

	camera = new Camera;
	camera->Init(cameraPos, targetPos, cameraUp);

	Light* light = new Light;
	Light::mMainLight = light;
	light->SetDiffuseColor(0.0f, 1.0f, 0.0f, 1.0f);
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	material = new Material;
	material->mBaseRenderPass = new RenderPass;
	material->mBaseRenderPass->SetShader(Shader::LoadShader("Res/deffer_light", "Res/test_light.vs", "Res/DefferedPosition.fs"));
	material->mBaseRenderPass->SetMatrix4(ModelMatrix.c_str(), glm::value_ptr(m));
	material->mBaseRenderPass->SetVec4("U_Color", color);
	dc.mVAO = vao;
	dc.mVBO = vbo;
	dc.mMaterial = material;

	
	fsq = new FullScreenQuad;
	fsq->Init("Res/FullScreen.vs", "Res/texture.fs");
	fsq->Bind(QuadType::kLeftBottom);
	skybox = new SkyBox;
	skybox->Init("Res/Pics/skybox");

	test_Texture = new FullScreenQuad;
	test_Texture->InitWithBuiltShader();
	test_Texture->Bind(QuadType::kRightTop);
	test_Texture_img = new Texture2D;
	test_Texture_img->CreateTexture2DFromBMP("Res/Pics/test.bmp");

	ground = new Ground;
	ground->Init();
}

void Scene::Init(int w, int h)
{
}

void Scene::SetViewPortSize(float width, float height)
{
	camera->SwitchTo3D(width, height);
	fsqfbo = new FBO;
	fsqfbo->AttachColorBuffer("color", GL_COLOR_ATTACHMENT0, width, height);
	fsqfbo->AttachColorBuffer("position", GL_COLOR_ATTACHMENT1, width, height);
	fsqfbo->AttachColorBuffer("normal", GL_COLOR_ATTACHMENT2, width, height);
	fsqfbo->AttachDepthBuffer("depth", width, height);
	fsqfbo->Finish();
}

void Scene::Render()
{
	camera->SwitchTo3D(1280.0f, 720.0f);
	camera->Update(GetFrameTime());
	skybox->Render(camera);
	
	GlobalRenderState::SetDepthTestState(true);
	GlobalRenderState::SetDepthMask(true);
	GlobalRenderState::SetBlendState(true);
	GlobalRenderState::SetBlendFunc(GL_ONE, GL_ONE);
	//fsqfbo->Bind();
	dc.Draw(camera);
	//fsqfbo->Unbind();

	//ground->Render(camera);

	camera->SwitchTo2D(1280.0f, 720.0f);
	
	fsq->mVAO->Bind();
	fsq->mVBO->Bind();
	glUseProgram(fsq->mShader->mProgram);
	fsq->mShader->mAttributes->Active();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fsqfbo->GetBuffer("position"));
	glUniform1i(glGetUniformLocation(fsq->mShader->mProgram, "U_PositionTexture"),0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, fsqfbo->GetBuffer("normal"));
	glUniform1i(glGetUniformLocation(fsq->mShader->mProgram, "U_NormalTexture"), 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, fsqfbo->GetBuffer("color"));
	glUniform1i(glGetUniformLocation(fsq->mShader->mProgram, "U_ColorTexture"), 2);
	
	fsq->Render();


	test_Texture->mVAO->Bind();
	test_Texture->mVBO->Bind();
	glUseProgram(test_Texture->mShader->mProgram);
	test_Texture->mShader->mAttributes->Active();

	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, test_Texture_img->mTextureID);
	glUniform1i(glGetUniformLocation(test_Texture->mShader->mProgram, "U_Texture"), 6);

	test_Texture->Render();

	
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
		camera->mbMouseLeft = true;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		camera->mbMouseLeft = false;
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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}