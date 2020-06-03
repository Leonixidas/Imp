#include "ImpPCH.h"
#include "ImguiLayer.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Imp/Application.h"
#include "Imp/Log.h"

//temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

Imp::ImguiLayer::ImguiLayer()
	: Layer("ImGuiLayer")
{

}

Imp::ImguiLayer::~ImguiLayer()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}

void Imp::ImguiLayer::OnAttach()
{
	ImGui::SetCurrentContext(ImGui::CreateContext());
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();

	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	//TEMPORARY WILL USE KEY IMP KEY CODES
	io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
	io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
	io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	ImGui_ImplOpenGL3_Init("#version 430");
}

void Imp::ImguiLayer::OnDetach()
{

}

void Imp::ImguiLayer::Update()
{

	ImGuiIO& io = ImGui::GetIO();
	Application& app = Application::GetInstance();
	io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

	float time = float(glfwGetTime());
	io.DeltaTime = m_Time > 0.f ? (time - m_Time) : 1.f / 60.f;
	m_Time = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	static bool show = true;
	ImGui::ShowDemoWindow(&show);


	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Imp::ImguiLayer::OnEvent(Event& e)
{
	EventDispatcher dispatcher{ e };
	dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNC(ImguiLayer::OnMouseButtonPressedEvent));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUNC(ImguiLayer::OnMouseButtonReleasedEvent));
	dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FUNC(ImguiLayer::OnMouseMovedEvent));
	dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUNC(ImguiLayer::OnMouseScrolledEvent));
	dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(ImguiLayer::OnKeyPressedEvent));
	dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FUNC(ImguiLayer::OnKeyReleasedEvent));
	dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FUNC(ImguiLayer::OnKeyTypedEvent));
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(ImguiLayer::OnWindowResizeEvent));
}

bool Imp::ImguiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[e.GetMouseButton()] = true;
	
	return false;
}

bool Imp::ImguiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[e.GetMouseButton()] = false;

	return false;
}

bool Imp::ImguiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2(e.GetX(), e.GetY());

	return false;
}

bool Imp::ImguiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += e.GetX();
	io.MouseWheel += e.GetY();

	return false;
}

bool Imp::ImguiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[e.GetKeyCode()] = true;

	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	return false;
}

bool Imp::ImguiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[e.GetKeyCode()] = false;

	return false;
}

bool Imp::ImguiLayer::OnKeyTypedEvent(KeyTypedEvent& e) 
{
	ImGuiIO& io = ImGui::GetIO();
	int keyCode = e.GetKeyCode();
	if(keyCode > 0 && keyCode < 0x10000)
		io.AddInputCharacter((unsigned short)keyCode);

	return false;
}

bool Imp::ImguiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(e.GetX(), e.GetY());
	io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
	glViewport(0, 0, (int)e.GetX(), (int)e.GetY());

	return false;
}
