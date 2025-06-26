#ifndef LIVTEST_TESTDEPTHTEST_H
#define LIVTEST_TESTDEPTHTEST_H
#include <memory>

#include "Test.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexBuffer.h"


namespace LivTest {

class TestDepthTest:public Test
{
private:
	std::unique_ptr<LivRender::VertexArray> m_VAO;
	std::unique_ptr<LivRender::VertexBuffer> m_VBO;
	std::unique_ptr<LivRender::IndexBuffer> m_IndexBuffer;
	std::unique_ptr<LivRender::Shader> m_Shader;
	std::unique_ptr<LivRender::Texture> m_Texture;
	LivRender::Renderer m_Renderer;
	bool m_DepthTest;
	bool m_MultiObject;
public:
	TestDepthTest();
	~TestDepthTest();

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnImGuiRender() override;
};

}      // LivTest
#endif // LIVTEST_TESTDEPTHTEST_H

