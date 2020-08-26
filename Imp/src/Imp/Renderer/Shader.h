#pragma once
#include "Imp/Core.h"
#include <string>
#include "glm/glm.hpp"

namespace Imp
{
	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void LoadSVFloat(const std::string& name, float value) = 0;
		virtual void LoadSVFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void LoadSVFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void LoadSVFloat4(const std::string& name, const glm::vec4& value) = 0;

		virtual void LoadSVMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void LoadSVMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual void LoadSVInt(const std::string& name, int value) = 0;
		virtual void LoadSVInt2(const std::string& name, const glm::ivec2& value) = 0;
		virtual void LoadSVInt3(const std::string& name, const glm::ivec3& value) = 0;
		virtual void LoadSVInt4(const std::string& name, const glm::ivec4& value) = 0;

		virtual void LoadSVBool(const std::string& name, bool value) = 0;

		virtual uint32_t GetAttributeLocation(const std::string& attribName) = 0;

		static Ref<Shader> Create(const std::string& filePath);
		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& pixelSrc);
	};

}

