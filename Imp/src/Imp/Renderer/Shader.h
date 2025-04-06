#pragma once
#include "Imp/Core/Base.h"
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

		virtual void LoadFloat(std::string const& name, float value) = 0;
		virtual void LoadFloat2(std::string const& name, glm::vec2 const& value) = 0;
		virtual void LoadFloat3(std::string const& name, glm::vec3 const& value) = 0;
		virtual void LoadFloat4(std::string const& name, glm::vec4 const& value) = 0;

		virtual void LoadMat3(std::string const& name, glm::mat3 const& matrix) = 0;
		virtual void LoadMat4(std::string const& name, glm::mat4 const& matrix) = 0;

		virtual void LoadInt(std::string const& name, int value) = 0;
		virtual void LoadInt2(std::string const& name, glm::ivec2 const& value) = 0;
		virtual void LoadInt3(std::string const& name, glm::ivec3 const& value) = 0;
		virtual void LoadInt4(std::string const& name, glm::ivec4 const& value) = 0;

		virtual void LoadBool(std::string const& name, bool value) = 0;

		virtual uint32_t GetAttributeLocation(std::string const& attribName) = 0;

		static Ref<Shader> Create(std::string const& filePath);
		static Ref<Shader> Create(std::string const& vertexSrc, std::string const& pixelSrc);
		static Ref<Shader> Create(std::string const& name, std::string const& vertexSrc, std::string const& pixelSrc);
	};

}

