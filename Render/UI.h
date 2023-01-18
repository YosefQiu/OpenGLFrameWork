#pragma once
#include "YosefGL.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "FileDialog/ImGuiFileDialog.h"
#include "Imguizmo/ImGuizmo.h"

class UI
{
public:
	UI(GLFWwindow* pWind)
	{
		this->pWind = pWind;
	};
	virtual ~UI() {};
public:
	void ImguiInit() {
		// Create and bind ImGui's CONTEXT
		const char* glsl_version = "#version 150";/*{{{*/
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.Fonts->AddFontFromFileTTF("Res/Fronts/data-latin.ttf", 16.0f);
		// Set imgui style
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(pWind, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
	}
	void ImguiCreateWindow() {
		// create imgui window
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImguiMenuBar();
		ImguiOpenDlg();
		//ImguiLightDlg();
		ImguiStatsDlg();
		ImguiVersionDlg();
	}
	void ImguiRender() {
		// Render imgui
		ImGui::Render();
		int display_w, display_h;
		glfwMakeContextCurrent(pWind);
		glfwGetFramebufferSize(pWind, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		auto& io = ImGui::GetIO();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
private:
	void ImguiMenuBar() {
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				ImGui::MenuItem("Light", NULL, &mbShowAppLight);
				ImGui::MenuItem("Stats", NULL, &mbShowAppStats);

				if (ImGui::MenuItem("Quit", "Alt+F4")) {
					glfwSetWindowShouldClose(pWind, true);
				}

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("File"))
			{
				ImGui::MenuItem("Open", NULL, &mbShowOpenDiag);
				ImGui::MenuItem("Save");
				if (mbShowOpenDiag)
				{
					ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", nullptr, ".");
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Help"))
			{
				
				// Dlg -> Print Version info
				ImGui::MenuItem("Version", NULL, &mbShowVersionInfo);
				

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}
	void ImguiOpenDlg() {
		if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
		{
			if (ImGuiFileDialog::Instance()->IsOk())
			{
				std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
				std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
				mFilePath = filePathName;
				std::string::size_type pos = 0;
				std::string sub_str = "\\";
				while ((pos = mFilePath.find(sub_str)) != std::string::npos)
				{
					mFilePath.replace(pos, sub_str.length(), "/");
				}
				mbFileChange = true;
			}
			ImGuiFileDialog::Instance()->Close();
		}
	}
	void ImguiLightDlg() {
		if (mbShowAppLight)
		{
			ImGui::SetNextWindowSize(ImVec2(345, 365), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(10, 275), ImGuiCond_FirstUseEver);

			
			ImGui::Begin("Light", &mbShowAppLight, ImGuiWindowFlags_None);
			
			if (ImGui::Button("LIGHT INFO...")) {
				mbLightInfo = !mbLightInfo;
			}

			// Theory Light
			if (ImGui::TreeNode("Theory Light..."))
			{
				if (ImGui::RadioButton("Enable D", mbDlight))
					mbDlight = !mbDlight;
				ImGui::SameLine();
				ImGui::ColorEdit3("DLight Color", (float*)&mDirColor);
				
				if (ImGui::RadioButton("Enable P", mbPlight))
					mbPlight = !mbPlight;
				ImGui::SameLine();
				ImGui::ColorEdit3("PLight Color", (float*)&mPointColor);
				
				if (ImGui::RadioButton("Enable S", mbSlight))
					mbSlight = !mbSlight;
				ImGui::SameLine();
				ImGui::ColorEdit3("SLight Color", (float*)&mSpotColor);

				ImGui::TreePop();
				ImGui::Separator();
			}
			
			// Area Light
			if (ImGui::TreeNode("Area Light..."))
			{
				ImGui::SetNextItemWidth(120);
				if (ImGui::RadioButton("Enable R", mbRectAreaLight))
					mbRectAreaLight = !mbRectAreaLight;
				ImGui::SameLine();
				ImGui::ColorEdit3("Rect Color", (float*)&mRectAreaColor);

				if (ImGui::RadioButton("Enable C", mbCylinderAreaLight)) {
					mbCylinderAreaLight = !mbCylinderAreaLight;
					std::cout << mbCylinderAreaLight << std::endl;
				}
					
				ImGui::SameLine();
				ImGui::ColorEdit3("Cylinder Color", (float*)&mCylinderAreaColor);

				if (ImGui::RadioButton("Enable S", mbSphereAreaLight))
					mbSphereAreaLight = !mbSphereAreaLight;
				ImGui::SameLine();
				ImGui::ColorEdit3("Sphere Color", (float*)&mSphereAreaColor);
				ImGui::TreePop();
				ImGui::Separator();
			}
			
			// Volumetric Light
			if (ImGui::TreeNode("Volumetric Light..."))
			{
				ImGui::SliderFloat("expousre", &mExpousre, 0.0f, 2.0f);
				ImGui::SliderFloat("decay", &mDecay, 0.95f, 1.05f);
				ImGui::SliderFloat("density", &mDensity, 0.0f, 2.0f);
				ImGui::SliderFloat("weight", &mWeight, 0.0f, 0.4f);
				ImGui::SliderInt("samples", &mSamplers, 0, 100);
				ImGui::TreePop();
				ImGui::Separator();
			}

			// IBL
			if (ImGui::TreeNode("Image Base on Light..."))
			{

				ImGui::TreePop();
				ImGui::Separator();
			}
			
			ImGui::End();
		}
	}
	void ImguiStatsDlg() {
		if (mbShowAppStats)
		{
			ImGuiIO& io = ImGui::GetIO();
			ImVec2 window_pos = ImVec2(3.0f, io.DisplaySize.y - 3.0f);
			ImVec2 window_pos_pivot = ImVec2(0.0f, 1.0f);
			ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

			if (ImGui::Begin("Example: Simple overlay", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs))
			{
				ImGui::Text("%.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
				ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);

				if (ImGui::IsMousePosValid())
				{
					mStatsMousePosX = io.MousePos.x;
					mStatsMousePosY = io.MousePos.y;
					ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
				}
				else {
					ImGui::Text("Mouse Position: <invalid>");
				}
			}
			ImGui::End();
		}
	}
	void ImguiVersionDlg() {
		if (mbShowVersionInfo)
		{
			ImGui::SetNextWindowSize(ImVec2(345, 365), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(10, 275), ImGuiCond_FirstUseEver);

			if (ImGui::Begin("Version Info", &mbShowVersionInfo, ImGuiWindowFlags_None))
			{
				
				ImGui::Text("Program Name: OpenGL Light");
				ImGui::Text("Author: Yosef Qiu");
				ImGui::Text("Version: 1.0");
			}
			ImGui::End();
		}
	}
public:
	//** ------------
	//** Imgui Window parameters
	//** ------------
	GLFWwindow* pWind;
	bool mbShowWindow;
	bool mbShowAppStats = true;
	bool mbShowAppLight = true;
	bool mbShowOpenDiag = true;
	bool mbShowVersionInfo = false;
public:
	//** ------------
	//** Imgui File Dlg parameters
	//** ------------
	bool mbFileChange = false;
	bool mbFileFirst = true;
	std::string mFilePath;
public:
	bool mbLightInfo = false;
	//** ------------
	//** Imgui Area Light parameters
	//** ------------
	bool mbRectAreaLight = false;
	bool mbCylinderAreaLight = false;
	bool mbSphereAreaLight = false;
	ImVec4 mRectAreaColor = ImVec4(0.0f, 0.34f, 0.57f, 1.0f);
	ImVec4 mCylinderAreaColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 mSphereAreaColor = ImVec4(0.2f, 0.4f, 0.3f, 1.0f);
	//** ------------
	//** Imgui Theory Light parameters
	//** ------------
	ImVec4 mDirColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 mPointColor = ImVec4(0.0f, 0.4f, 0.0f, 1.0f);
	ImVec4 mSpotColor = ImVec4(1.0f, 0.78f, 0.42f, 1.0f);
	bool mbDlight = false;
	bool mbSlight = true;
	bool mbPlight = false;
	//** ------------
	//** Imgui Volumetric Light parameters
	//** ------------
	float mExpousre = 0.344f;
	float mDecay = 0.968f;
	float mDensity = 0.158f;
	float mWeight = 0.081f;
	int mSamplers = 100;
public:
	//** ------------
	//** Stats parameters
	//** ------------
	float mStatsMousePosX = 0.0f;
	float mStatsMousePosY = 0.0f;
};

inline glm::vec3 IMVEC42VEC3(ImVec4 color) {
	return glm::vec3(color.x, color.y, color.z);
}

inline glm::vec4 IMVEC42VEC4(ImVec4 color) {
	return glm::vec4(color.x, color.y, color.z, color.w);
}