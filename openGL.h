#pragma once
#include <iostream>
#include <Windows.h>
#include <GL/glew.h>    
#include <GLFW/glfw3.h> 
#include <vector>
#include "bezier.h"

#define pointCount 4
#define pointWidth 5.0f
using std::vector;

GLuint WIDTH = 800, HEIGHT = 600;
GLfloat mouseX, mouseY;
vector<vector<GLfloat>> points(pointCount, vector<GLfloat>(3));//控制点存储数组
int count = 0;
static float T = 0.005;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)//按下esc退出程序
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void mouseButton_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		count %= pointCount;
		points[count][0] = mouseX / (WIDTH/2) - 1;
		points[count][1] = (mouseY / (HEIGHT/2) - 1) * -1;
		points[count][2] = 0.0f;
		count++;
	}
}

void mouseMove_callback(GLFWwindow* window, double xPos, double yPos)
{
	mouseX = xPos;
	mouseY = yPos;
}

//void windowResize_callback(GLFWwindow* window, int width, int height)
//{
//
//}

void drawPoint()
{
	glPointSize(pointWidth);
	glBegin(GL_POINTS);
	for (int i = 0; i < count; i++) {
		glColor3f(1.0f, 0.0f, 0.0f);//绘点的颜色
		glVertex3f(points[i][0], points[i][1], points[i][2]);
	}
	glEnd();
}

void drawCar()
{
	glPointSize(pointWidth * 2);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 1.0f);
	vector<float>vertex3f;
	if (T == 1)
	{
		glVertex3f(100, 100, 0);
	}
	else
	{
		glVertex3f((1 - T) * (1 - T) * (1 - T) * points[0][0] + 3 * T * (1 - T) * (1 - T) * points[1][0] + 3 * T * T * (1 - T) * points[2][0] + T * T * T * points[3][0],
			(1 - T) * (1 - T) * (1 - T) * points[0][1] + 3 * T * (1 - T) * (1 - T) * points[1][1] + 3 * T * T * (1 - T) * points[2][1] + T * T * T * points[3][1],
			(1 - T) * (1 - T) * (1 - T) * points[0][2] + 3 * T * (1 - T) * (1 - T) * points[1][2] + 3 * T * T * (1 - T) * points[2][2] + T * T * T * points[3][2]);
	}
	T = T <= 1 ? T + 0.005 : 1;
	glEnd();
	Sleep(100);
}

//四个控制点的贝塞尔曲线
void drawBezier(int n)
{
	float f1, f2, f3, f4;
	float deltaT = 1.0 / n;
	float T;
	float x, y, z;
	glBegin(GL_LINE_STRIP);
	glColor3f(0.8f, 0.2f, 0.5f);
	for (int i = 0; i <= n; i++) {
		T = i * deltaT;
		f1 = (1 - T) * (1 - T) * (1 - T);
		f2 = 3 * T * (1 - T) * (1 - T);
		f3 = 3 * T * T * (1 - T);
		f4 = T * T * T;
		x = f1 * points[0][0] + f2 * points[1][0] + f3 * points[2][0] + f4 * points[3][0];
		y = f1 * points[0][1] + f2 * points[1][1] + f3 * points[2][1] + f4 * points[3][1];
		z = f1 * points[0][2] + f2 * points[1][2] + f3 * points[2][2] + f4 * points[3][2];
		glVertex3f(x, y, z);

	}
	glEnd();
}

void render(GLFWwindow* window)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);

	if (count != 4)
	{
		drawPoint();
	}
	else
	{
		drawPoint();
		drawBezier(20);
		drawCar();
	}
}


GLFWwindow* initWindow()
{
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Bezier", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	//设置按键回调
	glfwSetKeyCallback(window, key_callback);
	//设置鼠标按键点下松开的回调
	glfwSetMouseButtonCallback(window, mouseButton_callback);
	//设置鼠标移动的回调
	glfwSetCursorPosCallback(window, mouseMove_callback);
	//设置窗口大小改变的回调，让绘画区域在窗口中间
	//glfwSetWindowSizeCallback(window, windowResize_callback);

	return window;
}