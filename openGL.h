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
vector<vector<GLfloat>> points(pointCount, vector<GLfloat>(3));//���Ƶ�洢����

int count = 0;
static float T = 0.005;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)//����esc�˳�����
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
		glColor3f(1.0f, 0.0f, 0.0f);//������ɫ
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
		vector<GLfloat> vertex3f = vector<float>(3);
		Bezier::bezierPoint(T, vertex3f, points);
		glVertex3f(vertex3f[0],vertex3f[1],vertex3f[2]);
	}
	T = T <= 1 ? T + 0.005 : 1;
	glEnd();
	Sleep(100);
}

//�ĸ����Ƶ�ı���������
void drawBezier(int n)
{
	vector<GLfloat> vertex3f = vector <GLfloat> (3);
	float deltaT = 1.0 / n;
	float T;
	glBegin(GL_LINE_STRIP);
	glColor3f(0.8f, 0.2f, 0.5f);
	for (int i = 0; i <= n; i++) {
		T = i * deltaT;
		Bezier::bezierPoint(T, vertex3f, points);
		glVertex3f(vertex3f[0], vertex3f[1], vertex3f[2]);
	}
	glEnd();
}

void render(GLFWwindow* window)
{

	//glEnable(GL_DEPTH_TEST);

	if (count != 4)
	{
		drawPoint();
	}
	else
	{
		drawPoint();
		drawBezier(20);
		//drawCar();
	}
}


GLFWwindow* initWindow()
{
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Bezier", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	//���ð����ص�
	glfwSetKeyCallback(window, key_callback);
	//������갴�������ɿ��Ļص�
	glfwSetMouseButtonCallback(window, mouseButton_callback);
	//��������ƶ��Ļص�
	glfwSetCursorPosCallback(window, mouseMove_callback);
	//���ô��ڴ�С�ı�Ļص����û滭�����ڴ����м�
	//glfwSetWindowSizeCallback(window, windowResize_callback);

	return window;
}