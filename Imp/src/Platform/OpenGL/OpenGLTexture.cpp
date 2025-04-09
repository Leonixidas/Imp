#include "ImpPCH.h"
#include "OpenGLTexture.h"
#include "stb_image.h"
#include "glad/glad.h"
#include "Imp/Core/Log.h"
#include <fstream>

namespace Imp
{
	namespace Utils
	{

		static GLenum ImpImageFormatToGLDataFormat(ImageFormat const format)
		{
			switch (format)
			{
			case ImageFormat::RGB8:  return GL_RGB;
			case ImageFormat::RGBA8: return GL_RGBA;
			}

			IMP_CORE_ASSERT(false);
			return 0;
		}

		static GLenum ImpImageFormatToGLInternalFormat(ImageFormat const format)
		{
			switch (format)
			{
			case ImageFormat::RGB8:  return GL_RGB8;
			case ImageFormat::RGBA8: return GL_RGBA8;
			}

			IMP_CORE_ASSERT(false);
			return 0;
		}

	}

	OpenGLTexture2D::OpenGLTexture2D(std::string const& path)
		: m_Path(path)
	{
		int width, height, channel;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		{
			IMP_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(std::string const&)");
			stbi_load(path.c_str(), &width, &height, &channel, 0);
		}

		if (data)
		{
			m_Width = width;
			m_Height = height;

			GLenum internalFormat = 0, dataFormat = 0;

			if (channel == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (channel == 3)
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}

			m_InternalFormat = internalFormat;
			m_DataFormat = dataFormat;

			IMP_CORE_ASSERT(internalFormat & dataFormat, "Format not supported");

			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
			glTextureStorage2D(m_RendererId, 1, internalFormat, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height));

			glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(m_RendererId, 0, 0, 0, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height), dataFormat, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);
		}
	}

	OpenGLTexture2D::OpenGLTexture2D(TextureSpecification const& specification)
		: m_Specification(specification)
		, m_Width(m_Specification.Width)
		, m_Height(m_Specification.Height)
	{
		IMP_PROFILE_FUNCTION();

		m_InternalFormat = Utils::ImpImageFormatToGLInternalFormat(m_Specification.Format);
		m_DataFormat = Utils::ImpImageFormatToGLDataFormat(m_Specification.Format);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		glTextureStorage2D(m_RendererId, 1, m_InternalFormat, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height));

		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		IMP_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_RendererId);
	}

	void OpenGLTexture2D::Bind(uint32_t slot)
	{
		IMP_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_RendererId);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		IMP_PROFILE_FUNCTION();

		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;

		IMP_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");

		glTextureSubImage2D(m_RendererId, 0, 0, 0, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height), m_DataFormat, GL_UNSIGNED_BYTE, data);
	}



	OpenGLFontTexture::~OpenGLFontTexture()
	{
		m_FontCharacters.clear();
	}

	void OpenGLFontTexture::Bind(std::string const& fontName)
	{
		auto iter = m_FontTextures.find(fontName);

		if (iter != m_FontTextures.end())
		{
			m_FontTextures[fontName]->Bind();
		}
	}

	bool OpenGLFontTexture::HasTexture(std::string const& fontName)
	{
		return m_FontTextures.find(fontName) != m_FontTextures.end();
	}

	void OpenGLFontTexture::LoadFont(std::string const& filepath)
	{
		size_t lastSlash = filepath.rfind('/') + 1;
		size_t eol = filepath.length() - 1;
		std::string path = filepath.substr(0, lastSlash);
		std::string fontName = filepath.substr(lastSlash, filepath.rfind('.') - lastSlash);

		std::string result{};
		std::ifstream in(filepath, std::ios::in);

		m_FontTextures[fontName] = Texture2D::Create(path + fontName + ".png");

		size_t count = 0;
		float w = 0.f, h = 0.f, y = 0.f;
		float charSize = 0.f, base = 0.f;
		std::string countstr{ "count=" };
		std::string sizestr{ "size=" };
		std::string basestr{ "base=" };
		std::string scaleWstr{ "scaleW=" };
		std::string scaleHstr{ "scaleH=" };
		std::string idstr{ "id=" };
		std::string xstr{ "x=" };
		std::string ystr{ "y=" };
		std::string widthstr{ "width=" };
		std::string heightstr{ "height=" };
		std::string xoffsetstr{ "xoffset=" };
		std::string yoffsetstr{ "yoffset=" };
		std::string xadvancestr{ "xadvance=" };

		while (std::getline(in, result))
		{
			count = result.find(countstr);
			if (count != std::string::npos)
			{
				size_t size = std::stoi(result.substr(count + countstr.length()));
				m_FontCharacters[fontName].reserve(size);
				continue;
			}

			count = result.find(sizestr);
			if (count != std::string::npos)
			{
				size_t first = count + sizestr.length();
				size_t second = result.find(' ', first);
				charSize = std::stof(result.substr(first, second - first));
				continue;
			}

			count = result.find(scaleWstr);
			if (count != std::string::npos)
			{
				size_t first = count + scaleWstr.length();
				size_t second = result.find(' ', first);
				w = std::stof(result.substr(first, second));

				first = second + 1 + scaleHstr.length();
				second = result.find(' ', first);
				h = std::stof(result.substr(first, second));
			}

			count = result.find(basestr);
			if (count != std::string::npos)
			{
				size_t first = count + basestr.length();
				size_t second = result.find(' ', first);
				base = std::stof(result.substr(first, second - first));
				base = charSize - base;
				continue;
			}

			if (result.find("char ") != std::string::npos)
			{
				Character chr{};
				size_t first = result.find(idstr) + idstr.length();
				size_t second = result.find(' ', first);
				unsigned char c = (unsigned char)std::stoi(result.substr(first, second - first));

				first = result.find(xstr) + xstr.length();
				second = result.find(' ', first);
				chr.Uv.x = std::stof(result.substr(first, second - first)) / w;

				first = result.find(ystr) + ystr.length();
				second = result.find(' ', first);
				chr.Uv.z = std::stof(result.substr(first, second - first)) / h;

				first = result.find(widthstr) + widthstr.length();
				second = result.find(' ', first);
				chr.Size.x = std::stof(result.substr(first, second - first));
				chr.Uv.y = chr.Uv.x + chr.Size.x / w;
				chr.Size.x /= charSize;

				first = result.find(heightstr) + heightstr.length();
				second = result.find(' ', first);
				chr.Size.y = y = std::stof(result.substr(first, second - first));
				chr.Uv.w = chr.Uv.z - chr.Size.y / h;
				chr.Size.y /= charSize;

				first = result.find(xoffsetstr) + xoffsetstr.length();
				second = result.find(' ', first);
				chr.Offset.x = std::stof(result.substr(first, second - first)) / charSize;

				first = result.find(yoffsetstr) + yoffsetstr.length();
				second = result.find(' ', first);
				chr.Offset.y = (std::stof(result.substr(first, second - first)) - base) / charSize;

				first = result.find(xadvancestr) + xadvancestr.length();
				second = result.find(' ', first);
				chr.AdvanceX = std::stof(result.substr(first, second - first)) / charSize;

				chr.Uv.z += 1 / h;
				chr.Uv.z += y / w;
				chr.Uv.w += y / h;
				m_FontCharacters[fontName][c] = chr;
			}
		}
	}


	std::string Imp::OpenGLFontTexture::ReadFile(std::string const& filePath)
	{
		std::string result{};
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
			IMP_CORE_ERROR("Could not open file: {0}", filePath);
		}
		return std::move(result);
	}
}