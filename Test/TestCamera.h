#ifndef LIVTEST_TESTCAMERA_H
#define LIVTEST_TESTCAMERA_H

#include <memory>
#include "Test.h"
#include "Camera.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexBuffer.h"

namespace LivTest {

class TestCamera:public Test
{
public:
	TestCamera();
	~TestCamera();

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnImGuiRender() override;
private:
	std::unique_ptr<LivRender::VertexArray> m_VAO;
	std::unique_ptr<LivRender::VertexBuffer> m_VBO;
	std::unique_ptr<LivRender::IndexBuffer> m_IndexBuffer;
	std::unique_ptr<LivRender::Shader> m_Shader;
	std::unique_ptr<LivRender::Texture> m_Texture;
	LivRender::Renderer m_Renderer;
	LivRender::Camera m_Camera;
};

}      // LivTest
#endif // LIVTEST_TEST_H
