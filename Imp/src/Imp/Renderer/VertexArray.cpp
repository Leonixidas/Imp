#include "ImpPCH.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Imp/Log.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

Imp::VertexArray* Imp::VertexArray::Create()
{
	switch (Renderer::GetAPI())
	{
	case RenderAPI::NONE: IMP_ERROR("NONE as API is not supported"); return nullptr;
	case RenderAPI::OPENGL: return new OpenGLVertexArray();
	}

	IMP_ERROR("Unknown Render API");

	return nullptr;
}