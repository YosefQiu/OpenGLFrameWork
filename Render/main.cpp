#include "YosefGL.h"
#include "Window.h"
#include "UI.h"
#include "MemoryPool/MemoryLabel.h"
#include "MemoryPool/DefaultAllocator.h"

#include "Scene.h"

#ifdef  _WIN32 || _WIN64
//#pragma comment (lib, "assimp-vc142-mt.lib")
extern "C"
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif

Scene* pScene = nullptr;
GLWindow* pWnd = nullptr;
UI* pUi = nullptr;

#define WND_WIDTH 1280
#define WND_HEIGHT 720
const char* WND_NAME = "OpenGL_Window";



void GL_Interaction() 
{
	glfwSetFramebufferSizeCallback(pWnd->GetWnd(), framebuffer_size_callback);
	glfwSetKeyCallback(pWnd->GetWnd(), key_callback);
	glfwSetMouseButtonCallback(pWnd->GetWnd(), mouse_button_callback);
	glfwSetCursorPosCallback(pWnd->GetWnd(), mouse_callback);
	glfwSetScrollCallback(pWnd->GetWnd(), scroll_callback);
}



int main()
{
	InitMemory();
	pWnd = new GLWindow(WND_WIDTH, WND_HEIGHT, WND_NAME);
	pWnd->Init();
	pWnd->InitInteraction(GL_Interaction);

	pUi = new UI(pWnd->GetWnd());
	pUi->ImguiInit();
	


	pScene = new Scene(WND_WIDTH, WND_HEIGHT, pUi);
	pScene->Init(pWnd->GetWnd());
	pScene->SetViewPortSize(WND_WIDTH, WND_HEIGHT);

	while (!pWnd->IsClose())
	{
		pUi->ImguiCreateWindow();
		pWnd->Update(0.0f, 0.34f, 0.57f);
		pScene->Render();
		pUi->ImguiRender();
		pWnd->SwapBuffer();
		pWnd->PollEvents();
	}
	
	pWnd->Close();
	QuitMemory();
	return 0;
}





