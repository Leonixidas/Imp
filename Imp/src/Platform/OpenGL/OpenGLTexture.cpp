#include "ImpPCH.h"
#include "OpenGLTexture.h"
#include "stb_image.h"
#include "glad/glad.h"
#include "Imp/Log.h"
#include <fstream>

namespace Imp
{

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: mPath(path)
	{
		int width, height, channel;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channel, 0);
		mWidth = width;
		mHeight = height;

		GLenum storageType = 0, shaderType = 0;

		if (channel == 4)
		{
			storageType = GL_RGBA8;
			shaderType = GL_RGBA;
		}
		else if(channel == 3)
		{
			storageType = GL_RGB8;
			shaderType = GL_RGB;
		}
		else if (channel == 2)
		{
			storageType = GL_RG8;
			shaderType = GL_RG;
		}
		else if (channel == 1)
		{
			storageType = GL_R8;
			shaderType = GL_RED;
		}

		glCreateTextures(GL_TEXTURE_2D,1, &mRendererID);
		glTextureStorage2D(mRendererID, 1, storageType, mWidth, mHeight);

		glTextureParameteri(mRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(mRendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(mRendererID, 0, 0, 0, mWidth, mHeight, shaderType, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &mRendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot)
	{
		glBindTextureUnit(slot, mRendererID);
	}

	OpenGLFontTexture::~OpenGLFontTexture()
	{
		mFontCharacters.clear();
	}

	void OpenGLFontTexture::Bind(const std::string& fontName)
	{
		auto iter = mFontTextures.find(fontName);

		if(iter != mFontTextures.end())
			mFontTextures[fontName]->Bind();
	}

	bool OpenGLFontTexture::HasTexture(const std::string& fontName)
	{
		return mFontTextures.find(fontName) != mFontTextures.end();
	}

	void OpenGLFontTexture::LoadFont(const std::string& filepath)
	{
		size_t lastSlash = filepath.rfind('/') + 1;
		size_t eol = filepath.length() - 1;
		std::string path = filepath.substr(0, lastSlash);
		std::string fontName = filepath.substr(lastSlash, filepath.rfind('.') - lastSlash);

		std::string result{};
		std::ifstream in(filepath, std::ios::in);

		mFontTextures[fontName] = Texture2D::Create(path + fontName + ".png");

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
				mFontCharacters[fontName].reserve(size);
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
				chr.uv.x = std::stof(result.substr(first, second - first)) / w;

				first = result.find(ystr) + ystr.length();
				second = result.find(' ', first);
				chr.uv.z = std::stof(result.substr(first, second - first)) / h;

				first = result.find(widthstr) + widthstr.length();
				second = result.find(' ', first);
				chr.Size.x = std::stof(result.substr(first, second - first));
				chr.uv.y = chr.uv.x + chr.Size.x / w;
				chr.Size.x /= charSize;

				first = result.find(heightstr) + heightstr.length();
				second = result.find(' ', first);
				chr.Size.y = y = std::stof(result.substr(first, second - first));
				chr.uv.w = chr.uv.z - chr.Size.y / h;
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

				chr.uv.z += 1 / h;
				chr.uv.z += y / w;
				chr.uv.w += y / h;
				mFontCharacters[fontName][c] = chr;
			}
		}
	}


	std::string Imp::OpenGLFontTexture::ReadFile(const std::string& filePath)
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
			IMP_ERROR("Could not open file" + filePath);
		}
		return std::move(result);
	}
}