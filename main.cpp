#include <iostream>
#include <Windows.h>
#include <GL/glew.h>    
#include <GLFW/glfw3.h>  
#include "openGL.h"

int main()
{
	glfwInit();
	
	GLFWwindow* window = initWindow();

	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);//���õ�Բ��

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);//�����߹⻬

	glewInit();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		render(window);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}