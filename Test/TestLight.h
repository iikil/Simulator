#ifndef LIVTEST_TESTLIGHT_H
#define LIVTEST_TESTLIGHT_H

#include <memory>
#include "Test.h"
#include "Camera.h"
#include "Renderer.h"
#include "VertexBuffer.h"

namespace LivTest {

class TestLight:public Test
{
public:
	TestLight();
	~TestLight();

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnImGuiRender() override;
private:
	std::unique_ptr<LivRender::VertexArray> m_VAO;
	std::unique_ptr<LivRender::VertexBuffer> m_VBO;
	std::unique_ptr<LivRender::IndexBuffer> m_IndexBuffer;
	std::unique_ptr<LivRender::Shader> m_ShaderObject;
    std::unique_ptr<LivRender::Shader> m_ShaderLight;
	LivRender::Renderer m_Renderer;
	LivRender::Camera m_Camera;
    glm::vec3 m_LightPos;
};

}      // LivTest
#endif // LIVTEST_TEST_H