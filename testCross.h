#include <iostream>
#include <Windows.h>
#include <GL/glew.h>    
#include <GLFW/glfw3.h> 
#include <vector>
#include "bezier.h"


GLFWwindow* initWindow()
{
	GLFWwindow* window = glfwCreateWindow(1600, 900, "Bezier", nullptr, nullptr);

	return window;
}

void roadInit()
{
	glBegin(GL_LINE_STRIP);

	glColor3f(0.8f, 0.2f, 0.5f);//»æµãµÄÑÕÉ«
	glVertex3f(100, 500, 0);
	glVertex3f(200, 300, 0);

	glEnd();
}

void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	roadInit();
}

