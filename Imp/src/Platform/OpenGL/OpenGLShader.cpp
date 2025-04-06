#include "ImpPCH.h"
#include "OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>
#include "Imp/Core/Log.h"

namespace
{
	GLenum ShaderTypeFromString(std::string const& type)
	{
		if (type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}
		else if (type == "pixel" || type == "fragment")
		{
			return GL_FRAGMENT_SHADER;
		}

		return 0;
	}
}

Imp::OpenGLShader::OpenGLShader(std::string const& filePath)
	: m_FilePath(filePath)
{
	std::string source = ReadFile(filePath);
	auto shaderSources = PreProcess(source);
	CompileShader(shaderSources);
}

Imp::OpenGLShader::OpenGLShader(std::string const& vertexSrc, std::string const& pixelSrc)
{
	std::unordered_map<GLenum, std::string> sources;
	sources[GL_VERTEX_SHADER] = vertexSrc;
	sources[GL_FRAGMENT_SHADER] = pixelSrc;
	CompileShader(sources);
}

Imp::OpenGLShader::OpenGLShader(std::string const& name, std::string const& vertexSrc, std::string const& pixelSrc)
	: m_Name(name)
{
	std::unordered_map<GLenum, std::string> sources;
	sources[GL_VERTEX_SHADER] = vertexSrc;
	sources[GL_FRAGMENT_SHADER] = pixelSrc;
	CompileShader(sources);
}

Imp::OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(m_RendererID);
}

void Imp::OpenGLShader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Imp::OpenGLShader::UnBind() const
{
	glUseProgram(0);
}

void Imp::OpenGLShader::LoadFloat(std::string const& name, float value)
{
	GLint location = GetUniformLocation(name);
	glUniform1f(location, value);
}

void Imp::OpenGLShader::LoadFloat2(std::string const& name, glm::vec2 const& value)
{
	GLint location = GetUniformLocation(name);
	glUniform2fv(location, 1, glm::value_ptr(value));
}

void Imp::OpenGLShader::LoadFloat3(std::string const& name, glm::vec3 const& value)
{
	GLint location = GetUniformLocation(name);
	glUniform3fv(location, 1, glm::value_ptr(value));
}

void Imp::OpenGLShader::LoadFloat4(std::string const& name, glm::vec4 const& value)
{
	GLint location = GetUniformLocation(name);
	glUniform4fv(location, 1, glm::value_ptr(value));
}

void Imp::OpenGLShader::LoadMat3(std::string const& name, glm::mat3 const& matrix)
{
	GLint location = GetUniformLocation(name);
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Imp::OpenGLShader::LoadMat4(std::string const& name, glm::mat4 const& matrix)
{
	GLint location = GetUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Imp::OpenGLShader::LoadInt(std::string const& name, int value)
{
	GLint location = GetUniformLocation(name);
	glUniform1i(location, value);
}

void Imp::OpenGLShader::LoadInt2(std::string const& name, glm::ivec2 const& value)
{
	GLint location = GetUniformLocation(name);
	glUniform2iv(location, 1, glm::value_ptr(value));
}

void Imp::OpenGLShader::LoadInt3(std::string const& name, glm::ivec3 const& value)
{
	GLint location = GetUniformLocation(name);
	glUniform3iv(location, 1, glm::value_ptr(value));
}

void Imp::OpenGLShader::LoadInt4(std::string const& name, glm::ivec4 const& value)
{
	GLint location = GetUniformLocation(name);
	glUniform4iv(location, 1, glm::value_ptr(value));
}

void Imp::OpenGLShader::LoadBool(std::string const& name, bool value)
{
	GLint location = GetUniformLocation(name);
	glUniform1i(location, value);
}

uint32_t Imp::OpenGLShader::GetAttributeLocation(std::string const& attribName)
{
	return static_cast<uint32_t>(glGetAttribLocation(m_RendererID, attribName.c_str()));
}

void Imp::OpenGLShader::CompileShader(std::unordered_map<GLenum, std::string> const& sources)
{
	GLuint program = glCreateProgram();
	std::vector<GLenum> glShaderIDs;
	glShaderIDs.reserve(sources.size());
	for (auto& kv : sources)
	{
		GLenum type = kv.first;
		std::string const& source = kv.second;
		GLuint shader = glCreateShader(type);

		const GLchar* sourceCSTR = source.c_str();
		glShaderSource(shader, 1, &sourceCSTR, 0);

		// Compile the vertex shader
		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());

			glDeleteShader(shader);
#ifdef IMP_DEBUG
			__debugbreak();
#endif
			break;
		}
		glAttachShader(program, shader);
		glShaderIDs.push_back(shader);
	}

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());

		// We don't need the program anymore.
		glDeleteProgram(program);
		// Don't leak shaders either.
		for (auto id : glShaderIDs)
		{
			glDeleteShader(id);
		}


#ifdef IMP_DEBUG
		__debugbreak();
#endif
		// In this simple program, we'll just leave
		return;
	}

	for (auto id : glShaderIDs)
	{
		glDetachShader(program, id);
		glDeleteShader(id);
	}

	m_RendererID = program;
}

std::string Imp::OpenGLShader::ReadFile(std::string const& filePath)
{
	std::string result;
	std::ifstream in(filePath, std::ios::in, std::ios::binary);

	if (in)
	{
		in.seekg(0, std::ios::end);
		result.resize((uint32_t)in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(result.data(), static_cast<std::streamsize>(result.size()));
	}
	else
	{
		IMP_CORE_ERROR("Could not open file: {0}", filePath);
	}
	return result;
}

std::unordered_map<GLenum, std::string> Imp::OpenGLShader::PreProcess(std::string const& source)
{
	std::unordered_map<GLenum, std::string> shaderSources;
	const char* typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	size_t pos = source.find(typeToken, 0);

	//add logic to load the properties that link to the uniforms

	while (pos != std::string::npos)
	{
		size_t eol = source.find_first_of("\r\n", pos);
		if (eol == std::string::npos)
			return {};
		size_t begin = pos + typeTokenLength + 1;
		std::string type = source.substr(begin, eol - begin);
		size_t nextLine = source.find_first_not_of("\r\n", eol);
		pos = source.find(typeToken, nextLine);
		shaderSources[ShaderTypeFromString(type)] = source.substr(nextLine, pos - (nextLine == std::string::npos ? source.size() - 1 : nextLine));
	}

	return shaderSources;
}

GLint Imp::OpenGLShader::GetUniformLocation(std::string const& name) const
{
	if (m_UniformCache.contains(name))
	{
		return m_UniformCache[name];
	}

	GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	m_UniformCache[name] = location;
	return location;
}
