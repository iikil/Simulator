#ifndef LIVRENDER_VERTEXARRAY_H
#define LIVRENDER_VERTEXARRAY_H
#include "VertexBuffer.h"

namespace LivRender{

class VertexBufferLayout;

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;
};

}      // LivRender
#endif // LIVRENDER_VERTEXARRAY_H