#ifndef LIVRENDER_VERTEXBUFFERLAYOUT_H
#define LIVRENDER_VERTEXBUFFERLAYOUT_H
#include <vector>
#include <type_traits>
#include <glad/glad.h>

#include "Renderer.h"

namespace LivRender{

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	VertexBufferLayout()
		:m_Stride(0){}

	template<typename T>
	void Push(unsigned int count)
	{
		if constexpr (std::is_same_v<T, float>) {
			m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
		} else if constexpr (std::is_same_v<T, unsigned int>) {
			m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		} else if constexpr (std::is_same_v<T, unsigned char>) {
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		} else {
			static_assert(false);
		}
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }
};

}      // LivRender
#endif // LIVRENDER_VERTEXBUFFERLAYOUT_H