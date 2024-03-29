#pragma once
#include "Imp/Log.h"
#include "glm/glm.hpp"

namespace Imp
{
enum class ShaderDataType
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static uint32_t GetShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float:		return 4;
	case ShaderDataType::Float2:	return 4 * 2;
	case ShaderDataType::Float3:	return 4 * 3;
	case ShaderDataType::Float4:	return 4 * 4;
	case ShaderDataType::Mat3:		return 4 * 3 * 3;
	case ShaderDataType::Mat4:		return 4 * 4 * 4;
	case ShaderDataType::Int:		return 4;
	case ShaderDataType::Int2:		return 4 * 2;
	case ShaderDataType::Int3:		return 4 * 3;
	case ShaderDataType::Int4:		return 4 * 4;
	case ShaderDataType::Bool:		return 1;
	default:
		IMP_CORE_FATAL("UNKNOWN SHADER DATA TYPE!");
		return 0;
	}
}

struct Vertex
{
	glm::vec3 Position = {};
	glm::vec2 uv = {};
};

class ShaderProps
{
public:
	ShaderProps(std::vector<ShaderDataType> const& props)
	{
		for (ShaderDataType const& d : props)
		{
			BufferSize += GetShaderDataTypeSize(d);
		}

		Buffer = new char[BufferSize];
	}

	~ShaderProps()
	{
		delete[] Buffer;
		Buffer = nullptr;
	}

	void SetShaderProperty(uint32_t const index, char const* data, ShaderDataType const type) const
	{
		uint32_t size = GetShaderDataTypeSize(type);

		if (index + size >= BufferSize)
		{
			IMP_CORE_ERROR("Shader data type doesn't fit in buffer starting at given index");
			return;
		}

		for (uint32_t i = 0; i < size; ++i)
		{
			Buffer[index] = data[i];
		}
	}

	template<typename T>
	T* GetShaderProperty(uint32_t const index)
	{
		if (index + sizeof(T) >= BufferSize)
		{
			IMP_CORE_ERROR("The size of the given type doesn't fit in the buffer at the given index");
			return nullptr;
		}

		return static_cast<T*>(&Buffer[index]);
	}

private:
	char* Buffer = nullptr;
	uint32_t BufferSize = 0;
};

struct BufferElement
{
	ShaderDataType Type;
	std::string Name;
	uint32_t Size;
	uint32_t Offset;
	bool Normalized;

	BufferElement(ShaderDataType const type, std::string const& name, bool const normalized = false)
		: Type(type)
		, Name(name)
		, Size(GetShaderDataTypeSize(type))
		, Offset(0)
		, Normalized(normalized)
	{}

	uint32_t GetComponentCount() const
	{
		switch (Type)
		{
		case ShaderDataType::Float:		return 1;
		case ShaderDataType::Float2:	return 2;
		case ShaderDataType::Float3:	return 3;
		case ShaderDataType::Float4:	return 4;
		case ShaderDataType::Mat3:		return 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4;
		case ShaderDataType::Int:		return 1;
		case ShaderDataType::Int2:		return 2;
		case ShaderDataType::Int3:		return 3;
		case ShaderDataType::Int4:		return 4;
		case ShaderDataType::Bool:		return 1;
		default:
			IMP_CORE_FATAL("UNKNOWN SHADER DATA TYPE!");
			return 0;
		}
	}
};

class BufferLayout
{
public:

	BufferLayout() {}

	BufferLayout(std::initializer_list<BufferElement> const& layout)
		: m_Elements(layout)
	{
		CalculateElementOffsetAndStride();
	}

	virtual ~BufferLayout() = default;

	uint32_t GetStride() const { return m_Stride; }
	inline std::vector<BufferElement> const& GetElements() const { return m_Elements; }

	std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return m_Elements.cbegin(); }
	std::vector<BufferElement>::const_iterator end() const { return m_Elements.cend(); }

private:
	//FUNCTIONS
	void CalculateElementOffsetAndStride()
	{
		uint32_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

	//VARIABLES
	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride = 0;
};


class VertexBuffer
{
public:
	virtual ~VertexBuffer() {};
	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;

	virtual uint32_t GetRendererID() = 0;

	virtual void SetLayout(BufferLayout const& layout) = 0;
	virtual BufferLayout const& GetLayout() const = 0;

	static Ref<VertexBuffer> Create(float* vertices, uint32_t const size);
};

class IndexBuffer
{
public:
	virtual ~IndexBuffer() {};
	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;

	virtual uint32_t GetCount() const = 0;

	static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t const count);
};

class FrameBuffer
{
public:
	virtual ~FrameBuffer() {};

	virtual void Bind() const = 0;
	virtual void UnBind() const = 0;

	virtual void* GetFrame() const = 0;

	static Ref<FrameBuffer> Create();
};
}