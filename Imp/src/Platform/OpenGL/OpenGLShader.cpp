#include "ImpPCH.h"
#include "OpenGLShader.h"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>
#include "Imp/Log.h"

static GLenum ShaderTypeFromString(const std::string& type)
{
	if (type == "vertex")
		return GL_VERTEX_SHADER;
	else if (type == "pixel" || type == "fragment")
		return GL_FRAGMENT_SHADER;

	return 0;
}

Imp::OpenGLShader::OpenGLShader(const std::string& filePath)
{
	std::string source = ReadFile(filePath);
	auto shaderSources = PreProcess(source);
	CompileShader(shaderSources);
}

Imp::OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& pixelSrc)
{
	std::unordered_map<GLenum, std::string> sources;
	sources[GL_VERTEX_SHADER] = vertexSrc;
	sources[GL_FRAGMENT_SHADER] = pixelSrc;
	CompileShader(sources);
}

Imp::OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(mRendererID);
}

void Imp::OpenGLShader::Bind() const
{
	glUseProgram(mRendererID);
}

void Imp::OpenGLShader::UnBind() const
{
	glUseProgram(0);
}

void Imp::OpenGLShader::LoadSVFloat(const std::string& name, float value)
{
	GLint location = GetUniformLocation(name);
	glUniform1f(location, value);
}

void Imp::OpenGLShader::LoadSVFloat2(const std::string& name, const glm::vec2& value)
{
	GLint location = GetUniformLocation(name);
	glUniform2fv(location, 1, glm::value_ptr(value));
}

void Imp::OpenGLShader::LoadSVFloat3(const std::string& name, const glm::vec3& value)
{
	GLint location = GetUniformLocation(name);
	glUniform3fv(location, 1, glm::value_ptr(value));
}

void Imp::OpenGLShader::LoadSVFloat4(const std::string& name, const glm::vec4& value)
{
	GLint location = GetUniformLocation(name);
	glUniform4fv(location, 1, glm::value_ptr(value));
}

void Imp::OpenGLShader::LoadSVMat3(const std::string& name, const glm::mat3& matrix)
{
	GLint location = GetUniformLocation(name);
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Imp::OpenGLShader::LoadSVMat4(const std::string& name, const glm::mat4& matrix)
{
	GLint location = GetUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Imp::OpenGLShader::LoadSVInt(const std::string& name, int value)
{
	GLint location = GetUniformLocation(name);
	glUniform1i(location, value);
}

void Imp::OpenGLShader::LoadSVInt2(const std::string& name, const glm::ivec2& value)
{
	GLint location = GetUniformLocation(name);
	glUniform2iv(location,1, glm::value_ptr(value));
}

void Imp::OpenGLShader::LoadSVInt3(const std::string& name, const glm::ivec3& value)
{
	GLint location = GetUniformLocation(name);
	glUniform3iv(location, 1, glm::value_ptr(value));
}

void Imp::OpenGLShader::LoadSVInt4(const std::string& name, const glm::ivec4& value)
{
	GLint location = GetUniformLocation(name);
	glUniform4iv(location, 1, glm::value_ptr(value));
}

void Imp::OpenGLShader::LoadSVBool(const std::string& name, bool value)
{
	GLint location = GetUniformLocation(name);
	glUniform1i(location, value);
}

uint32_t Imp::OpenGLShader::GetAttributeLocation(const std::string& attribName)
{
	return (uint32_t)glGetAttribLocation(mRendererID, attribName.c_str());
}

void Imp::OpenGLShader::CompileShader(const std::unordered_map<GLenum, std::string>& sources)
{
	GLuint program = glCreateProgram();
	std::vector<GLenum> glShaderIDs;
	glShaderIDs.reserve(sources.size());
	for (auto& kv : sources)
	{
		GLenum type = kv.first;
		const std::string& source = kv.second;
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
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

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
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);
		// Don't leak shaders either.
		for (auto id : glShaderIDs)
			glDeleteShader(id);
		

#ifdef IMP_DEBUG
		__debugbreak();
#endif
		// In this simple program, we'll just leave
		return;
	}

	for (auto id : glShaderIDs)
		glDetachShader(program, id);

	mRendererID = program;
}

std::string Imp::OpenGLShader::ReadFile(const std::string& filePath)
{
	std::string result;
	std::ifstream in(filePath, std::ios::in, std::ios::binary);

	if (in)
	{
		in.seekg(0, std::ios::end);
		result.resize((uint32_t)in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
	}
	else
	{
		IMP_ERROR("Could not open file: " + filePath);
	}
	return result;
}

std::unordered_map<GLenum, std::string> Imp::OpenGLShader::PreProcess(const std::string& source)
{
	std::unordered_map<GLenum, std::string> shaderSources;
	const char* typeToken = "#type";
	size_t typeTokenLength = strlen(typeToken);
	size_t pos = source.find(typeToken, 0);

	//add logic to load the properties that link to the uniforms

	while (pos != std::string::npos)
	{
		size_t eol = source.find_first_of("\r\n", pos);
		if (eol == std::string::npos) return {};
		size_t begin = pos + typeTokenLength + 1;
		std::string type = source.substr(begin, eol - begin);
		size_t nextLine = source.find_first_not_of("\r\n", eol);
		pos = source.find(typeToken, nextLine);
		shaderSources[ShaderTypeFromString(type)] = source.substr(nextLine, pos - (nextLine == std::string::npos ? source.size() - 1 : nextLine));
	}

	return shaderSources;
}

GLint Imp::OpenGLShader::GetUniformLocation(const std::string& name) const
{
	if (mUniformCache.find(name) != mUniformCache.end())
		return mUniformCache[name];

	GLint location = glGetUniformLocation(mRendererID, name.c_str());
	mUniformCache[name] = location;
	return location;
}
