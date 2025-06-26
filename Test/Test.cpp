#include "Test.h"
#include "Renderer.h"
#include "imgui.h"

namespace LivTest {

TestMenu::TestMenu(Test*& currentTestPointer)
	:m_CurrentTest(currentTestPointer)
{
}

void TestMenu::OnRender()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestMenu::OnImGuiRender()
{
	for (auto& test : m_Tests)
	{
		if (ImGui::Button(test.first.c_str()))
		{
			m_CurrentTest = test.second();
		}
	}
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

}