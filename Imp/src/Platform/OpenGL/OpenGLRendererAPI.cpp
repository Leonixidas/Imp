#include "ImpPCH.h"
#include "OpenGLRendererAPI.h"
#include "glad/glad.h"

void Imp::OpenGLRendererAPI::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Imp::OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void Imp::OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Imp::OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Imp::OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
{
	glDrawElements(GL_TRIANGLES, static_cast<int>(vertexArray->GetIndexBuffer()->GetCount()), GL_UNSIGNED_INT, nullptr);
}

void Imp::OpenGLRendererAPI::DrawInstanced(const Ref<VertexArray>& vertexArray, uint32_t instanceCount)
{
	glDrawElementsInstanced(GL_TRIANGLES, static_cast<int>(vertexArray->GetIndexBuffer()->GetCount()), GL_UNSIGNED_INT, nullptr, static_cast<int>(instanceCount));
}

uint32_t Imp::OpenGLRendererAPI::GetFrameId()
{
	glGenTextures(1, &m_FrameID);
	return m_FrameID;
}

