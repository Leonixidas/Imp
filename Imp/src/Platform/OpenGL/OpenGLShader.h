#pragma once

#include "glad/glad.h"
#include "Imp/Renderer/Shader.h"
#include <unordered_map>

namespace Imp
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& vertexSrc, const std::string& pixelSrc);
		virtual ~OpenGLShader();
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void LoadFloat(const std::string& name, float value) override;
		virtual void LoadFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void LoadFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void LoadFloat4(const std::string& name, const glm::vec4& value) override;
						  
		virtual void LoadMat3(const std::string& name, const glm::mat3& matrix) override;
		virtual void LoadMat4(const std::string& name, const glm::mat4& matrix) override;
						  
		virtual void LoadInt(const std::string& name, int value) override;
		virtual void LoadInt2(const std::string& name, const glm::ivec2& value) override;
		virtual void LoadInt3(const std::string& name, const glm::ivec3& value) override;
		virtual void LoadInt4(const std::string& name, const glm::ivec4& value) override;

		virtual void LoadBool(const std::string& name, bool value) override;

		virtual uint32_t GetAttributeLocation(const std::string& attribName) override;

	private:
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void CompileShader(const std::unordered_map<GLenum, std::string>& sources);
		GLint GetUniformLocation(const std::string& name) const;

		mutable std::unordered_map<std::string, GLint> m_UniformCache;
		uint32_t m_RendererID;
	};
}