#include "TestLight.h"
#include "VertexBufferLayout.h"
#include "imgui.h"
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "TestUtils.h"

namespace LivTest {

using namespace LivRender;

TestLight::TestLight()
    :m_Renderer(),m_Camera(),
    m_LightPos{glm::vec3(1.2f, 1.0f, 2.0f)}
{
    auto shaderObjectPath = getExecutableDir().parent_path() /  "res" / "shaders" / "1.colors.shader";
    auto shaderLightPath = getExecutableDir().parent_path() /  "res" / "shaders" / "1.light_cube.shader";

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f, 

        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f, 

         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  

        -0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f, -0.5f, 

        -0.5f,  0.5f, -0.5f, 
         0.5f,  0.5f, -0.5f,  
         0.5f,  0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f, -0.5f, 
    };
    
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_DEPTH_TEST));
    
    m_VAO = std::make_unique<VertexArray>();
    m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    m_VAO->AddBuffer(*m_VBO, layout);
    m_ShaderObject = std::make_unique<Shader>(shaderObjectPath.string());
    m_ShaderLight = std::make_unique<Shader>(shaderLightPath.string());

    m_Camera.SetCameraPos(glm::vec3(0.0f, 0.0f, 3.0f));
}

TestLight::~TestLight()
{

}

void TestLight::OnUpdate(float deltaTime)
{

}

void TestLight::OnRender()
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GLCall(glEnable(GL_DEPTH_TEST));
    
    m_ShaderObject->Bind();
    m_ShaderObject->SetUniform4f("objectColor", 1.0f, 0.5f, 0.31f, 1.0f);
    m_ShaderObject->SetUniform4f("lightColor", 1.0f, 1.0f, 1.0f, 1.0f);

    glm::mat4 iden = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    glm::mat4 mvp = glm::mat4(1.0f);

    view = m_Camera.GetCameraMatrix() * view;
    proj = m_Camera.GetCameraProjM() * proj;

    mvp = proj * view * model * iden;
    m_ShaderObject->SetUniformMat4f("u_MVP", mvp);
    m_Renderer.Draw(*m_VAO, 36, *m_ShaderObject);

    m_ShaderLight->Bind();
    model = glm::translate(model, m_LightPos);
    model = glm::scale(model, glm::vec3(0.2f));
    mvp = proj * view * model * iden;
    m_ShaderLight->SetUniformMat4f("u_MVP", mvp);

    m_Renderer.Draw(*m_VAO, 36, *m_ShaderLight);
    
}

void TestLight::OnImGuiRender()
{

}

}      // LivTest