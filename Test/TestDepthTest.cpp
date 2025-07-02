#include "TestDepthTest.h"
#include "VertexBufferLayout.h"
#include "imgui.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "TestUtils.h"

namespace LivTest {

using namespace LivRender;

TestDepthTest::TestDepthTest()
    :m_Renderer(),m_DepthTest(false),m_MultiObject(false)
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // 0
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   // 1
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   // 2
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   // 3

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   // 4
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   // 5
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // 6
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   // 7

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   // 8
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   // 9
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   // 10
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   // 11

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   // 12
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   // 13
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   // 14
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   // 15

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   // 16
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,   // 17
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   // 18
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   // 19

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   // 20
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   // 21
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   // 22
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   // 23
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0,
        4,5,6,
        6,7,4,
        8,9,10,
        10,11,8,
        12,13,14,
        14,15,12,
        16,17,18,
        18,19,16,
        20,21,22,
        22,23,20
    };

    //打开混合
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    auto shaderPath = getExecutableDir().parent_path() /  "res" / "shaders" / "DepthTest.shader";
    auto texturePath = getExecutableDir().parent_path() / "res" / "textures" / "1.png";

    m_VAO = std::make_unique<VertexArray>();
    m_VBO = std::make_unique<VertexBuffer>(vertices,sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_VAO->AddBuffer(*m_VBO, layout);
    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 36);
    m_Texture = std::make_unique<Texture>(texturePath.string());
    m_Shader = std::make_unique<Shader>(shaderPath.string());
}

TestDepthTest::~TestDepthTest()
{

}

void TestDepthTest::OnUpdate(float deltaTime)
{

}

void TestDepthTest::OnRender()
{
    if (m_DepthTest)
    {
        GLCall(glEnable(GL_DEPTH_TEST));
    }
    else {
        GLCall(glDisable(GL_DEPTH_TEST));
    }
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    m_Texture->Bind();
    m_Shader->Bind();

    glm::mat4 iden = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    glm::mat4 mvp = glm::mat4(1.0f);

    proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    m_Shader->SetUniformMat4f("u_proj", proj);
    m_Shader->SetUniformMat4f("u_view", view);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // 0
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   // 1
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   // 2
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   // 3

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   // 4
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   // 5
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // 6
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   // 7

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   // 8
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   // 9
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   // 10
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   // 11

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   // 12
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   // 13
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   // 14
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   // 15

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   // 16
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,   // 17
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   // 18
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   // 19

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   // 20
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   // 21
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   // 22
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   // 23
    };

    if (m_MultiObject)
    {
        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };
        for (int i = 0; i < 10; ++i)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);

            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            m_Shader->SetUniformMat4f("u_model", model);

            m_Renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
    }
    else {
        model = glm::rotate(model, (float)ImGui::GetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

        m_Shader->SetUniformMat4f("u_model", model);

        m_Renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }
}

void TestDepthTest::OnImGuiRender()
{
    ImGui::Checkbox("DepthTest", &m_DepthTest);
    ImGui::Checkbox("MultiObject", &m_MultiObject);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

}      // LivTest