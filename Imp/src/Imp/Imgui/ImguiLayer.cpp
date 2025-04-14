#include "ImpPCH.h"
#include "ImguiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Imp/Core/Application.h"

//temporary
#include <GLFW/glfw3.h>

Imp::ImGuiLayer::ImGuiLayer()
	: Layer("ImGuiLayer")
{

}

Imp::ImGuiLayer::~ImGuiLayer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Imp::ImGuiLayer::OnAttach()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.f;
		style.Colors[ImGuiCol_WindowBg].w = 1.f;
	}

	Application& app = Application::Get();
	GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void Imp::ImGuiLayer::OnDetach()
{
	IMP_PROFILE_FUNCTION();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Imp::ImGuiLayer::OnImGuiRender()
{
}

void Imp::ImGuiLayer::Begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Imp::ImGuiLayer::End()
{
	ImGuiIO& io = ImGui::GetIO();
	Application& app = Application::Get();
	io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}
