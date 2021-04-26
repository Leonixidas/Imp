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
		}

		IMP_ERROR("UNKNOWN SHADER DATA TYPE!");

		return 0;
	}

	struct Vertex
	{
		glm::vec3 Position = {};
		glm::vec2 uv = {};
	};

	class ShaderProps
	{
	public:
		ShaderProps(const std::vector<ShaderDataType>& props)
		{
			for (const ShaderDataType& d : props)
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

		void SetShaderProperty(uint32_t index, const char* data, const ShaderDataType type)
		{
			uint32_t size = GetShaderDataTypeSize(type);

			if (index + size >= BufferSize) Log::Error("shader data type doesn't fit in buffer starting at given index"); return;

			for(uint32_t i = 0; i < size; ++i)
				Buffer[index] = data[i];
		}

		template<typename T>
		T* GetShaderProperty(uint32_t index)
		{
			if (index + sizeof(T) >= BufferSize) Log::Error("the size of the given type doesn't fit in the buffer at the given index"); return nullptr;

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

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
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
			}

			IMP_ERROR("UNKNOWN SHADER DATA TYPE!");

			return 0;
		}
	};

	class BufferLayout
	{
	public:

		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& layout)
			: mElements(layout)
		{
			CalculateElementOffsetAndStride();
		}

		virtual ~BufferLayout() = default;

		uint32_t GetStride() const { return mStride; }
		inline const std::vector<BufferElement>& GetElements() const { return mElements; }
	
		std::vector<BufferElement>::iterator begin() { return mElements.begin(); }
		std::vector<BufferElement>::iterator end() { return mElements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return mElements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return mElements.end(); }

	private:
		//FUNCTIONS
		void CalculateElementOffsetAndStride()
		{
			uint32_t offset = 0;
			mStride = 0;
			for (auto& element : mElements)
			{
				element.Offset = offset;
				offset += element.Size;
				mStride += element.Size;
			}
		}

		//VARIABLES
		std::vector<BufferElement> mElements;
		uint32_t mStride = 0;
	};


	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetRendererID() = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
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