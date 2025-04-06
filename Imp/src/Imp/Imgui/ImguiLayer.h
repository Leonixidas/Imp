#pragma once
#include "Imp/Core/Layer.h"
#include "Imp/Events/KeyEvent.h"
#include "Imp/Events/MouseEvent.h"
#include "Imp/Events/ApplicationEvent.h"

namespace Imp
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		//Variables
		float m_Time = 0.0f;
	};
}


