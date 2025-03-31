#pragma once
#include "Imp/Core.h"
#include <string>
#include "glm/glm.hpp"

namespace Imp
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void LoadFloat(const std::string& name, float value) = 0;
		virtual void LoadFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void LoadFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void LoadFloat4(const std::string& name, const glm::vec4& value) = 0;

		virtual void LoadMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void LoadMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual void LoadInt(const std::string& name, int value) = 0;
		virtual void LoadInt2(const std::string& name, const glm::ivec2& value) = 0;
		virtual void LoadInt3(const std::string& name, const glm::ivec3& value) = 0;
		virtual void LoadInt4(const std::string& name, const glm::ivec4& value) = 0;

		virtual void LoadBool(const std::string& name, bool value) = 0;

		virtual uint32_t GetAttributeLocation(const std::string& attribName) = 0;

		static Ref<Shader> Create(const std::string& filePath);
		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& pixelSrc);
	};

}

