#ifndef LIVRENDER_INDEXBUFFER_H
#define LIVRENDER_INDEXBUFFER_H

namespace LivRender{

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int getCount() const { return m_Count; }
};

}      // LivRender
#endif // LIVRENDER_INDEXBUFFER_H