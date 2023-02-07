#pragma once

#include "YosefPrefix.h"
#include "YosefGL.h"
#include "UI.h"
class Scene
{
public:
	Scene() {}
	Scene(int w, int h, UI* ui) : mW(w), mH(h), mUI(ui) {}
	virtual ~Scene() {}
public:
	void Init(GLFWwindow* window);
	void Init(int w, int h) {}
	void SetViewPortSize(float width, float height);
	void Render();
public:
	UI* mUI = nullptr;
	int mW, mH;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);