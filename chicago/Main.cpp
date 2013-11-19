#include <gl\glew.h>
#include <windows.h>
#include "glfw\glfw3.h"
#include <gl\GLU.h>

#include "soil\SOIL.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\matrix_inverse.hpp"

#include "imgui\imgui.h"
#include "imgui\imguiRenderGL3.h"

GLFWwindow *window;


void setup3d(double w, double h) {

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, w, h);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_MULTISAMPLE);
}

void prepareGUI(double w, double h) {
	glBindVertexArray(0);
	glUseProgram(0);

	glViewport(0, 0, w, h);
	glDisable(GL_DEPTH_TEST);

}


static void keyPress(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	
}

int main() {

	if(!glfwInit())
		exit(EXIT_FAILURE);


	//window = glfwCreateWindow(1920, 1080, "chicago", glfwGetPrimaryMonitor(), NULL);
	window = glfwCreateWindow(1728, 972, "chicago", NULL, NULL);
	//window = glfwCreateWindow(1024, 768, "chicago", NULL, NULL);
	
	if(!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowPos(window, 20, 20);
	
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyPress);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glfwSwapInterval(1);
	if(glewInit() != GLEW_OK)
		exit(EXIT_FAILURE);

	
	if(!imguiRenderGLInit("media/fonts/DroidSans.ttf"))
		exit(EXIT_FAILURE);
	
	//load and set up shit

	glClearColor(0.0f, 0.5f, 1.f, 1.f);

	char buffer[20];
	unsigned frames = 0;
	unsigned fps = 0;
	double lastUpdate = 0;
	double last = glfwGetTime();

	while(!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		setup3d(width, height);
		
		double delta = glfwGetTime() - last;
		last = glfwGetTime();

		
		prepareGUI(width, height);
		imguiBeginFrame(100, 100, 0, 0);

        imguiEndFrame();	
        imguiDrawText(20, height - 20, IMGUI_ALIGN_LEFT, buffer, imguiRGBA(255, 255, 255, 255));
        imguiRenderGLDraw(width, height); 

		glfwSwapBuffers(window);

		frames++;
		if(glfwGetTime() - lastUpdate > 1.0) {
			fps = frames;
			sprintf(buffer, "%i fps", fps);
			lastUpdate = glfwGetTime();
			frames = 0;
		}

		glfwPollEvents();
	}
	
	imguiRenderGLDestroy();
	glfwTerminate();
	exit(EXIT_SUCCESS);
}