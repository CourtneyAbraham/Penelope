#pragma once

namespace Penelope {

	enum class ShaderDataType : uint8_t {
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4,
		Mat3,
		Mat4,
		Bool
	};

	static size_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::Float:		return 4;
			case ShaderDataType::Float2:	return 8;
			case ShaderDataType::Float3:	return 12;
			case ShaderDataType::Float4:	return 16;
			case ShaderDataType::Int:		return 4;
			case ShaderDataType::Int2:		return 8;
			case ShaderDataType::Int3:		return 12;
			case ShaderDataType::Int4:		return 16;
			case ShaderDataType::Mat3:		return 36;
			case ShaderDataType::Mat4:		return 64;
			case ShaderDataType::Bool:		return 1;
		}

		PN_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement{
		ShaderDataType Type;
		std::string Name;
		size_t Offset;
		size_t Size; 
		bool Normailzed;
		
		BufferElement(ShaderDataType type, const std::string& name, bool normailzed = false) : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normailzed(normailzed) {}

		size_t GetComponentCount() const {
			switch (Type) 	{
				case ShaderDataType::Float:		return 1;
				case ShaderDataType::Float2:	return 2;
				case ShaderDataType::Float3:	return 3;
				case ShaderDataType::Float4:	return 4;
				case ShaderDataType::Int:		return 1;
				case ShaderDataType::Int2:		return 2;
				case ShaderDataType::Int3:		return 3;
				case ShaderDataType::Int4:		return 4;
				case ShaderDataType::Mat3:		return 9;
				case ShaderDataType::Mat4:		return 16;
				case ShaderDataType::Bool:		return 1;
			}

			PN_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout {
	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
			CalculateOffsetAndStride();
		}

		BufferLayout() {}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline size_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
	private:

		void CalculateOffsetAndStride() {
			size_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

		std::vector<BufferElement> m_Elements;
		size_t m_Stride = 0;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, size_t size);
	};
}

