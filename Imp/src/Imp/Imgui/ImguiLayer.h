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
	~ImguiLayer() override;

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


