#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Test.h"
#include "TestTexture2D.h"
#include "TestClearColor.h"
#include "TestDepthTest.h"
#include "TestCamera.h"
#include "TestLight.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        const char* glsl_version = "#version 130";
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        ImGui::StyleColorsDark();

        //test code
        LivTest::Test* currentTest = nullptr;
        LivTest::TestMenu* testMenu = new LivTest::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<LivTest::TestClearColor>("Clear Color");
        testMenu->RegisterTest<LivTest::TestTexture2D>("2D Texture");
        testMenu->RegisterTest<LivTest::TestDepthTest>("Depth Test");
        testMenu->RegisterTest<LivTest::TestCamera>("Camera");
        testMenu->RegisterTest<LivTest::TestLight>("Light");
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            if (currentTest)
            {
                currentTest->OnUpdate(0.0f);
                currentTest->OnRender();
                ImGui::Begin("Test");
                if (currentTest != testMenu && ImGui::Button("<-"))
                {
                    delete currentTest;
                    currentTest = testMenu;
                }
                currentTest->OnImGuiRender();
                ImGui::End();
            }


            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;  
}

//{
//float positions[] = {
//    -0.5f, -0.5f, 0.0f, 0.0f,  //0  0.0f, 0.0f,
//     0.5f, -0.5f, 1.0f, 0.0f,  //1  1.0f, 0.0f,
//     0.5f,  0.5f, 1.0f, 1.0f,  //2  1.0f, 1.0f,
//    -0.5f,  0.5f, 0.0f, 1.0f   //3  0.0f, 1.0f 
//};
//
//unsigned int indices[] = {
//    0,1,2,
//    2,3,0
//};
//
//GLCall(glEnable(GL_BLEND));
//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//
//VertexArray va;
//VertexBuffer vb(positions, 4 * 4 * sizeof(float));
//VertexBufferLayout layout;
//
//layout.Push<float>(2);
//layout.Push<float>(2);
//va.AddBuffer(vb, layout);
//
//IndexBuffer ib(indices, 6);
//
//glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
//
//Shader shader("res/shaders/Basic.shader");
//shader.Bind();
//shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
//shader.SetUniformMat4f("u_MVP", proj);
//
//Texture texture("res/textures/1.png");
//texture.Bind();
//shader.SetUniform1i("u_Texture", 0);
//
//va.Unbind();
//vb.Unbind();
//ib.Unbind();
//shader.Unbind();
//
//Renderer renderer;
//
//ImGui::CreateContext();
//ImGuiIO& io = ImGui::GetIO(); (void)io;
//const char* glsl_version = "#version 130";
//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
//
//ImGui_ImplGlfw_InitForOpenGL(window, true);
//ImGui_ImplOpenGL3_Init(glsl_version);
//
//ImGui::StyleColorsDark();
//
//bool show_demo_window = true;
//bool show_another_window = false;
//ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
//
//float r = 0.0f;
//float increment = 0.05f;
///* Loop until the user closes the window */
//while (!glfwWindowShouldClose(window))
//{
//    /* Render here */
//    renderer.Clear();
//
//    ImGui_ImplOpenGL3_NewFrame();
//    ImGui_ImplGlfw_NewFrame();
//    ImGui::NewFrame();
//    /*glBegin(GL_TRIANGLES);
//    glVertex2f(-0.5f, -0.5f);
//    glVertex2f(0.0f, 0.5f);
//    glVertex2f(0.5f, -0.5f);
//    glEnd();*/
//    shader.Bind();
//    //texture.Bind();
//    shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
//
//    /*GLCall(glBindVertexArray(vao));*/
//
//    renderer.Draw(va, ib, shader);
//
//    if (r > 1.0f)
//    {
//        increment = -0.05f;
//    }
//    else if (r < 0.0f) {
//        increment = 0.05f;
//    }
//
//    r += increment;
//
//    {
//        static float f = 0.0f;
//        static int counter = 0;
//
//        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
//
//        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//        ImGui::Checkbox("Another Window", &show_another_window);
//
//        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
//
//        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//            counter++;
//        ImGui::SameLine();
//        ImGui::Text("counter = %d", counter);
//
//        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
//        ImGui::End();
//    }
//
//    ImGui::Render();
//    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//
//    /* Swap front and back buffers */
//    GLCall(glfwSwapBuffers(window));
//
//    /* Poll for and process events */
//    GLCall(glfwPollEvents());
//}
//
//    }