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
		io.Fonts->AddFontFromFileTTF((front_path + "data-latin.ttf").c_str(), 16.0f);
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
		ImguiConfigtDlg();
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
				ImGui::MenuItem("Config", NULL, &mbShowAppConfig);
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
	void ImguiConfigtDlg() {
		if (mbShowAppConfig)
		{
			ImGui::SetNextWindowSize(ImVec2(345, 365), ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(10, 275), ImGuiCond_FirstUseEver);

			
			ImGui::Begin("Config", &mbShowAppConfig, ImGuiWindowFlags_None);
			
			ImGui::Text("YELLOS ARROW: The direction of the total force");
			ImGui::Text("GREEN ARROW: The direction of the velocity");
			ImGui::Text("BLUE/RED ARROW: The size and direction of user exercion");
			ImGui::Text(mCollisionINFO.c_str());

			// 2D Scene
			if (ImGui::TreeNode("Particle System 2D Scene..."))
			{
				if (ImGui::Button("Rest"))
					mbSceneRest = true;
				ImGui::SameLine();
				if (ImGui::Button("Concentric Circles"))
					mbConcentricCircles = !mbConcentricCircles;
				ImGui::SameLine();
				if (ImGui::Button("Show Arrows"))
					mbShowArrow = !mbShowArrow;
				if (ImGui::RadioButton("Enable Gravity", mbGravity))
					mbGravity = !mbGravity;
				if (ImGui::RadioButton("Enable Air restitution", mbAirResistance))
					mbAirResistance = !mbAirResistance;
				ImGui::SliderFloat("OUTER CIRCLE", &m_outerCircle, 0.5, 0.90);
				ImGui::SliderFloat("INNER CIRCLE", &m_innerCircle, 0.05, 0.65);
				ImGui::SliderFloat("COEFFICIENT OF FRICTION", &m_coffOfFriction, 0.0, 1.0f);
				ImGui::SliderFloat("COEFFICIENT OF RESTITUTION", &m_coffOfRestitution, 0.0, 1.0f);
				ImGui::SliderFloat("COEFFICIENT OF AIR RESTITUTION", &m_coffOFAirResistance, 0.0, 1.0f);
				ImGui::TreePop();
				ImGui::Separator();
			}
			
			// 3D Scene
			if (ImGui::TreeNode("Particle System 3D Scene..."))
			{
				if (ImGui::Button("3D Scene"))
					mbShow3DScene = !mbShow3DScene;
				ImGui::TreePop();
				ImGui::Separator();
			}
			
			// Camera info
			if (ImGui::TreeNode("Camera INFO..."))
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
	bool mbShowAppConfig = true;
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
	//** ------------
	//** Imgui Scene Config parameters
	//** ------------
	bool mbSceneRest = false;
	bool mbConcentricCircles = false;
	bool mbGravity = true;
	bool mbAirResistance = true;
	bool mbShowArrow = true;
	bool mbShow3DScene = false;
	float m_outerCircle = 0.9f;
	float m_innerCircle = 0.55f;
	float m_coffOfFriction = 0.1f;
	float m_coffOfRestitution = 0.2f;
	float m_coffOFAirResistance = 0.3f;
	std::string mCollisionINFO = "There is no collision";

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