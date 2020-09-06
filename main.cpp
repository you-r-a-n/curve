#include <iostream>
#include <Windows.h>
#include <GL/glew.h>    
#include <GLFW/glfw3.h>  
#include "openGL.h"
#include"Straight.h"
#include"Curve.h"

void roadCreate()
{
	//{
	//	//非特殊情况路径
	//	vector<float> start{ 0.3, -0.1 };
	//	vector<float> end{ 0.9, 0.1 };
	//	new Straight(start, end);
	//	start = { -0.1,-0.9 };
	//	end = { 0.1,-0.3 };
	//	new Straight(start, end);
	//	new Curve(Road::g_road[1], Road::g_road[0]);
	//}

	////十字路口
	//{
	//	//右
	//	vector<float> start{ 0.3, -0.1 };
	//	vector<float> end{ 0.9, -0.1 };
	//	Straight* straight = new Straight(start, end);
	//	Road* select = straight->clone();
	//	select->reverse();
	//	select->move(0, 0.2);
	//	//上
	//	start = { 0.1,0.3 };
	//	end = { 0.1,0.9 };
	//	straight = new Straight(start, end);
	//	select = straight->clone();
	//	select->reverse();
	//	select->move(-0.2, 0);
	//	//左
	//	start = { -0.3,0.1 };
	//	end = { -0.9,0.1 };
	//	straight = new Straight(start, end);
	//	select = straight->clone();
	//	select->reverse();
	//	select->move(0, -0.2);
	//	//下
	//	start = { -0.1,-0.3 };
	//	end = { -0.1,-0.9 };
	//	straight = new Straight(start, end);
	//	select = straight->clone();
	//	select->reverse();
	//	select->move(0.2, 0);
	//	//链接
	//	new Curve(Road::g_road[1], Road::g_road[2]);
	//	new Curve(Road::g_road[1], Road::g_road[4]);
	//	new Curve(Road::g_road[1], Road::g_road[6]);
	//	//new Curve(Road::g_road[3], Road::g_road[4]);
	//	//new Curve(Road::g_road[3], Road::g_road[6]);
	//	//new Curve(Road::g_road[3], Road::g_road[0]);
	//	new Curve(Road::g_road[5], Road::g_road[6]);
	//	new Curve(Road::g_road[5], Road::g_road[0]);
	//	new Curve(Road::g_road[5], Road::g_road[2]);
	//	//new Curve(Road::g_road[7], Road::g_road[0]);
	//	//new Curve(Road::g_road[7], Road::g_road[2]);
	//	//new Curve(Road::g_road[7], Road::g_road[4]);
	//	//掉头路径生成直接是直线了
	//	//new Curve(Road::g_road[1], Road::g_road[0]);
	//}

	{	
		//分支路口
		vector<float> start{ 0, -0.9 };
		vector<float> end{ 0, -0.1 };
		Road* straight = new Straight(start, end);
		Road* select = straight->clone();
		select->move(0.1, 0);
		select = straight->clone();
		select->move(-0.1, 0);
		start = { 0.3,0.1 };
		end = { 0.9,0.1 };
		straight = new Straight(start, end);
		new Curve(Road::g_road[1], Road::g_road[3]);
		straight = straight->clone();
		straight->move(-1.2, 0.2);
		straight->reverse();
		new Curve(Road::g_road[2], straight);
		straight = Road::g_road[0]->clone();
		straight->move(0, 1.1);
		new Curve(Road::g_road[0], straight);
	}

}

void roadInit()
{
	vector<Road*>::iterator itr = Road::g_road.begin();
	while (itr != Road::g_road.end()) {
		(*itr)->draw();
		itr++;
	}
}

int main()
{
	glfwInit();
	
	GLFWwindow* window = initWindow();

	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);//设置点圆滑

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);//设置线光滑

	glewInit();

	roadCreate();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		

		render(window);

		roadInit();

		glfwSwapBuffers(window);

		Sleep(200);
	}

	glfwTerminate();
	return 0;
}