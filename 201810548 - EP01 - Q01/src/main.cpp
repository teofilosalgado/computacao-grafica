#include <iostream>
#include <GLFW/glfw3.h>
#pragma warning(push, 0)
#include <imgui.h>
#pragma warning(pop)
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#pragma execution_character_set( "utf-8" )

#define LARGURA_JANELA 640
#define ALTURA_JANELA 480

struct Cor {
	int vermelho;
	int verde;
	int azul;
};

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !ImGui::GetIO().WantCaptureMouse)
	{
		/* Obtém a posição do mouse */
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << "Cursor em (" << xpos << ", " << ypos << ")" << std::endl;
	}
}

Cor hexadecimal_para_cor(const char* hexadecimal) 
{
	int vermelho, verde, azul;
	sscanf_s(hexadecimal, "#%02x%02x%02x", &vermelho, &verde, &azul);
	return Cor
	{
		 vermelho,
		 verde,
		 azul
	};
}

void desenhar_retangulo(float x, float y, float largura, float altura, const char* hexadecimal)
{
	/* Cria uma nova matriz para transformações */
	glPushMatrix();

	/* Aplica as transformações */
	glTranslatef(x, y, 0.0);
	glScalef(largura, altura, 0.0);

	/* Define a cor da figura */
	Cor cor = hexadecimal_para_cor(hexadecimal);
	glColor3f(cor.vermelho / 255.0, cor.verde / 255.0, cor.azul / 255.0);

	/* Desenha os vértices */
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(1.0, 0.0);
	glVertex2f(1.0, 1.0);
	glVertex2f(0.0, 1.0);
	glEnd();

	/* Retorna para a matriz original (limpa) */
	glPopMatrix();
}

void desenhar_cama(float x, float y) 
{
	const float largura = 150.0;
	const float altura = 220.0;
	const float cabeceira = 10.0;
	const float travesseiro = 40.0;
	const float colcha = 20.0;

	/* Desenha a cabeceira */
	desenhar_retangulo(x, y, largura, cabeceira, "#9A7C51");

	/* Desenha o travesseiro */
	desenhar_retangulo(x, y + cabeceira, largura, travesseiro, "#E9E9EA");

	/* Desenha a cama */
	desenhar_retangulo(x, y + cabeceira + travesseiro, largura, altura - cabeceira - travesseiro, "#AA2822");

	/* Desenha a colcha */
	desenhar_retangulo(x, y + cabeceira + travesseiro, largura, colcha, "#BC3A33");
}

void desenhar_armario(float x, float y) 
{
	const float largura_armario = 250.0;
	const float altura_armario = 100.0;
	const float largura_porta = 110.0;
	const float altura_porta = 10.0;

	/* Desenha o armário */
	desenhar_retangulo(x, y, largura_armario, altura_armario, "#4C3C26");

	/* Desenha as portas */
	desenhar_retangulo(x + altura_porta, y + altura_armario, largura_porta, altura_porta, "#9A7C51");
	desenhar_retangulo(x + largura_porta + (altura_porta * 2), y + altura_armario, largura_porta, altura_porta, "#9A7C51");
}

void desenhar_mesa(float x, float y)
{
	const float largura = 120.0;
	const float altura = 250.0;

	desenhar_retangulo(x, y, largura, altura, "#A17656");
}

void desenhar_cadeira(float x, float y)
{
	const float largura = 100.0;
	const float altura = 100.0;
	const float encosto = 20.0;

	desenhar_retangulo(x, y, largura, altura, "#03396C");
	desenhar_retangulo(x + largura - encosto, y, encosto, altura, "#005B96");
}

void desenhar_porta(float x, float y)
{
	const float largura = 15.0;
	const float altura = 150.0;
	const float macaneta = 10.0;

	desenhar_retangulo(x, y, largura, altura, "#815E44");
	desenhar_retangulo(x + largura, y + macaneta, macaneta, macaneta, "#4C4C4C");
}

void desenhar_janela(float x, float y)
{
	const float largura = 180.0;
	const float altura = 10.0;
	desenhar_retangulo(x, y, largura, altura, "#6DC1E5");
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(LARGURA_JANELA, ALTURA_JANELA, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	std::cout << "Versão do OpenGL: " << glGetString(GL_VERSION) << std::endl;

	/* Callback para clique do mouse dentro da janela */
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	/* Configuração do Dear ImGui */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	/* Definindo o modo de renderização */
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(4.0f);

	/* Definição de projeção, partindo a origem do canto superior esquerdo da tela */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, LARGURA_JANELA, ALTURA_JANELA, 0.0, 1.0, 0.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Cria uma janela do Dear ImGui */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* Define o modo de operação da matriz para realizar transformações */
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		/* Renderiza os móveis */
		desenhar_armario(0.0, 0.0);
		desenhar_cama(470.0, 0.0);
		desenhar_mesa(0.0, 230.0);
		desenhar_cadeira(130.0, 315);
		desenhar_porta(550.0, 330.0);
		desenhar_janela(270.0, 0);

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