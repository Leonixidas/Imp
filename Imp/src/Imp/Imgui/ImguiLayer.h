#pragma once
#include "../Layer.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/WindowEvent.h"

namespace Imp
{
	class ImguiLayer :	public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void Update() override;
		virtual void OnEvent(Event& e) override;

	private:
		//Functions
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

		//Variables
		float m_Time = 0.0f;
	};
}


