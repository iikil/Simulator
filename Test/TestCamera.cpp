#include "TestCamera.h"
#include "VertexBufferLayout.h"
#include "imgui.h"
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "TestUtils.h"

namespace LivTest {

using namespace LivRender;

TestCamera::TestCamera()
    :m_Renderer(),m_Camera()
{
    auto shaderPath = getExecutableDir().parent_path() /  "res" / "shaders" / "Basic.shader";
    auto texturePath = getExecutableDir().parent_path() / "res" / "textures" / "1.png";

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
    
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_DEPTH_TEST));

    m_Camera.SetCameraPos(glm::vec3(0.0f, 0.0f, 2.0f));
    
    m_VAO = std::make_unique<VertexArray>();
    m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_VAO->AddBuffer(*m_VBO, layout);
    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 36);
    m_Texture = std::make_unique<Texture>(texturePath.string());
    m_Shader = std::make_unique<Shader>(shaderPath.string());

    m_Shader->Bind();

    m_Texture->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);
}

TestCamera::~TestCamera()
{

}

void TestCamera::OnUpdate(float deltaTime)
{

}

void TestCamera::OnRender()
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;

    m_Camera.SetCameraPos(glm::vec3(camX, 0.0f, camZ));
    m_Camera.SetCameraTarget(glm::vec3(0.0f, 0.0f, 0.0f));
    

    m_Texture->Bind();
    m_Shader->Bind();

    glm::mat4 iden = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    glm::mat4 mvp = glm::mat4(1.0f);

    view = m_Camera.GetCameraMatrix() * view;
    proj = m_Camera.GetCameraProjM() * proj;

    mvp = proj * view * model * iden;
    m_Shader->SetUniformMat4f("u_MVP", mvp);
    m_Renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
}

void TestCamera::OnImGuiRender()
{

}

} // LivTest