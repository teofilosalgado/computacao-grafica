#include <iostream>
#include <GLFW/glfw3.h>
#pragma warning(push, 0)
#include <imgui.h>
#pragma warning(pop)
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#pragma execution_character_set( "utf-8" )

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    std::cout << "Versão do OpenGL: " << glGetString(GL_VERSION) << std::endl;

    /* Configuração do Dear ImGui */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Cria uma janela do Dear ImGui */
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        /* 
            Insira a lógica de renderização aqui 
        */

        /* Desenha elementos na janela */
        ImGui::Begin("Projeto de Computação Gráfica");
        ImGui::Text("Hello, world!");
        ImGui::End();

        /* Renderiza a janela */
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    /* Finaliza o Dear ImGui */
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    /* Encerra o programa */
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}