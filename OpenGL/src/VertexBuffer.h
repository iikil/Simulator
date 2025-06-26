#ifndef LIVRENDER_VERTEXBUFFER_H
#define LIVRENDER_VERTEXBUFFER_H

namespace LivRender{

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

}      // LivRender
#endif // LIVRENDER_VERTEXBUFFER_H