#pragma once

#include "glad/glad.h"
#include "Imp/Renderer/Shader.h"
#include <unordered_map>

namespace Imp
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(std::string const& filePath);
		OpenGLShader(std::string const& vertexSrc, std::string const& pixelSrc);
		OpenGLShader(std::string const& name, std::string const& vertexSrc, std::string const& pixelSrc);

		~OpenGLShader() override;
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void LoadFloat(std::string const& name, float value) override;
		virtual void LoadFloat2(std::string const& name, glm::vec2 const& value) override;
		virtual void LoadFloat3(std::string const& name, glm::vec3 const& value) override;
		virtual void LoadFloat4(std::string const& name, glm::vec4 const& value) override;
						  
		virtual void LoadMat3(std::string const& name, glm::mat3 const& matrix) override;
		virtual void LoadMat4(std::string const& name, glm::mat4 const& matrix) override;
						  
		virtual void LoadInt(std::string const& name, int value) override;
		virtual void LoadInt2(std::string const& name, glm::ivec2 const& value) override;
		virtual void LoadInt3(std::string const& name, glm::ivec3 const& value) override;
		virtual void LoadInt4(std::string const& name, glm::ivec4 const& value) override;

		virtual void LoadBool(std::string const& name, bool value) override;

		virtual uint32_t GetAttributeLocation(std::string const& attribName) override;

	private:
		static std::string ReadFile(std::string const& filePath);
		static std::unordered_map<GLenum, std::string> PreProcess(std::string const& source);
		void CompileShader(std::unordered_map<GLenum, std::string> const& sources);
		GLint GetUniformLocation(std::string const& name) const;

	private:
		mutable std::unordered_map<std::string, GLint> m_UniformCache;
		uint32_t m_RendererID;
		std::string m_Name;
		std::string m_FilePath;
	};
}