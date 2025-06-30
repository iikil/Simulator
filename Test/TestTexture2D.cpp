#include "TestTexture2D.h"

#include "VertexBufferLayout.h"
#include "imgui.h"

#include "TestUtils.h"

namespace LivTest {

using namespace LivRender;

TestTexture2D::TestTexture2D()
    :m_TranslationA(200,200,0), m_TranslationB(400,400,0)
{
    float positions[] = {
        -50.0f, -50.0f, 0.0f, 0.0f,  //0  0.0f, 0.0f,
        50.0f, -50.0f, 1.0f, 0.0f,  //1  1.0f, 0.0f,
        50.0f,  50.0f, 1.0f, 1.0f,  //2  1.0f, 1.0f,
        -50.0f,  50.0f, 0.0f, 1.0f   //3  0.0f, 1.0f 
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    auto shaderPath = getExecutableDir().parent_path() /  "res" / "shaders" / "Basic.shader";
    auto texturePath = getExecutableDir().parent_path() / "res" / "textures" / "1.png";

    m_Shader = std::make_unique<Shader>(shaderPath.string());
    m_VAO = std::make_unique<VertexArray>();
    m_VBO = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);
    m_Texture = std::make_unique<Texture>(texturePath.string());
    
    VertexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(2);
    m_VAO->AddBuffer(*m_VBO, layout);

    //TPDO:test 不在初始化uniform变量，直接在渲染循环中绑定

    m_Shader->Bind();
    m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    //m_Shader->SetUniformMat4f("u_MVP", proj);

    m_Texture->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);
}

TestTexture2D::~TestTexture2D()
{

}

void TestTexture2D::OnRender()
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT));

    Renderer renderer;
    m_Texture->Bind();

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
        glm::mat4 mvp = proj * view * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
        glm::mat4 mvp = proj * view * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }
}

void TestTexture2D::OnImGuiRender()
{
    ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
    ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

}      // LivTest