#ifndef LIVRENDER_RENDERER_H
#define LIVRENDER_RENDERER_H

#include <glad/glad.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#ifdef _MSC_VER
    #define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
    #include <csignal>
    #ifndef SIGTRAP
        #define SIGTRAP 5
    #endif
    #define DEBUG_BREAK() raise(SIGTRAP)
#else
    #define DEBUG_BREAK() ((void)0)
#endif

#define ASSERT(x) if(!(x)) DEBUG_BREAK();
#define GLCall(x) LivRender::GLClearError();\
    x;\
    ASSERT(LivRender::GLLogCall(#x, __FILE__, __LINE__))

namespace LivRender {

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);


class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};

}      // LivRender
#endif // LIVRENDER_RENDERER_H