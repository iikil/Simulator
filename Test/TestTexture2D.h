#ifndef LIVTEST_TESTTEXTURE2D_H
#define LIVTEST_TESTTEXTURE2D_H

#include <memory>
#include "Test.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexBuffer.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"


namespace LivTest {

class TestTexture2D: public Test{
public:
	TestTexture2D();
	~TestTexture2D();

	void OnRender() override;
	void OnImGuiRender() override;
private:
	std::unique_ptr<LivRender::VertexArray> m_VAO;
	std::unique_ptr<LivRender::VertexBuffer> m_VBO;
	std::unique_ptr<LivRender::IndexBuffer> m_IndexBuffer;
	std::unique_ptr<LivRender::Shader> m_Shader;
	std::unique_ptr<LivRender::Texture> m_Texture;
	glm::vec3 m_TranslationA, m_TranslationB;
	LivRender::Renderer m_Renderer;
};

}      // LivTest
#endif // LIVTEST_TEST_H