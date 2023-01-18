#include "YosefGL.h"
#include "Window.h"
#include "UI.h"
#include <assimp/Importer.hpp>      
#include <assimp/scene.h>           
#include <assimp/postprocess.h>   

#include "MemoryPool/MemoryLabel.h"
#include "MemoryPool/DefaultAllocator.h"

#include "GL30/BufferObject.h"
#include "Scene.h"
#pragma comment (lib, "assimp-vc142-mt.lib")

Scene* pScene = nullptr;
GLWindow* pWnd = nullptr;
UI* pUi = nullptr;

#define WND_WIDTH 1280
#define WND_HEIGHT 720
const char* WND_NAME = "OpenGL_Window";





void GL_Interaction() {
	glfwSetFramebufferSizeCallback(pWnd->GetWnd(), framebuffer_size_callback);
	glfwSetKeyCallback(pWnd->GetWnd(), key_callback);
	glfwSetMouseButtonCallback(pWnd->GetWnd(), mouse_button_callback);
	glfwSetCursorPosCallback(pWnd->GetWnd(), mouse_callback);
	glfwSetScrollCallback(pWnd->GetWnd(), scroll_callback);
}

extern "C" {
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}

void PrintPath(bool bshow = true)
{
	if (bshow) {
		std::cout << "front: " << front_path << std::endl;
		std::cout << "geomerty: " << geomerty_path << std::endl;
		std::cout << "hdr: " << hdr_path << std::endl;
		std::cout << "models: " << models_path << std::endl;
		std::cout << "pics: " << pic_path << std::endl;
		std::cout << "shaders: " << shader_path << std::endl;
	}
}
void LoadFinish(const aiScene* scene)
{
	std::cout << "LoadFinish ! NumVertices : " << (*(scene->mMeshes))->mNumVertices << std::endl;
}
bool LoadModelTest(const std::string& pFile)
{
	// Create an instance of the Importer class
	Assimp::Importer importer;

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// probably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene)
	{
		std::cout << importer.GetErrorString() << std::endl;
		return false;
	}

	// Now we can access the file's contents.
	LoadFinish(scene);

	// We're done. Everything will be cleaned up by the importer destructor
	std::cout << "load success" << std::endl;
	return true;
}

int main()
{
	InitMemory();
	pWnd = new GLWindow(WND_WIDTH, WND_HEIGHT, WND_NAME);
	pWnd->Init();
	pWnd->InitInteraction(GL_Interaction);

	pUi = new UI(pWnd->GetWnd());
	pUi->ImguiInit();
	

	pScene = new Scene(WND_WIDTH, WND_HEIGHT);
	pScene->Init();
	pScene->SetViewPortSize(WND_WIDTH, WND_HEIGHT);
	std::cout << "Rendering------------" << std::endl << std::endl;

	
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





