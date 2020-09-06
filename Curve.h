#pragma once
#include <GL/glew.h>    
#include <GLFW/glfw3.h> 
#include "Road.h"

class Curve : public Road
{
public:
	Curve(){}
	Curve(Road* now, Road* target)
	{
		linkCross(now, target);
		Road::g_road.push_back(this);
		//测试
		//std::cout<<bezierPoints[0][0]<<" "<<bezierPoints[0][1]<<std::endl;
		//std::cout << bezierPoints[1][0] << " " << bezierPoints[1][1] << std::endl;
		//std::cout << bezierPoints[2][0] << " " << bezierPoints[2][1] << std::endl;
		//std::cout << bezierPoints[3][0] << " " << bezierPoints[3][1] << std::endl;
	}

	void draw()
	{
		float f1, f2, f3, f4;
		float T;
		float x, y;
		glBegin(GL_LINE_STRIP);
		glColor3f(0.8f, 0.2f, 0.5f);
		for (int i = 0; i <= 20; ++i)
		{
			T = i * 1.0 / 20;
			f1 = (1 - T) * (1 - T) * (1 - T);
			f2 = 3 * T * (1 - T) * (1 - T);
			f3 = 3 * T * T * (1 - T);
			f4 = T * T * T;
			x = f1 * bezierPoints[0][0] + f2 * bezierPoints[1][0] + f3 * bezierPoints[2][0] + f4 * bezierPoints[3][0];
			y = f1 * bezierPoints[0][1] + f2 * bezierPoints[1][1] + f3 * bezierPoints[2][1] + f4 * bezierPoints[3][1];
			glVertex2f(x, y);
		}
		glEnd();

		glPointSize(5.0f);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(bezierPoints[0][0], bezierPoints[0][1]);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(bezierPoints[3][0], bezierPoints[3][1]);
		glEnd();
	}

	Road* clone()
	{
		return nullptr;
	}

private:
	//延伸线到目标线中1/2点
	//y = a1x + b1
	//y = a2x + b2
	//特殊情况
	//1.两点连线为水平线
	//2.两点连线为竖直线
	//平行路径的掉头路径生成不对
	vector<float> controlPoint(vector<float> now1,vector<float> now2,vector<float> target1,vector<float> target2)
	{
		if (target1[1] - target2[1] == 0)
		{
			return vector<float>{now2[0], (now2[1] + target1[1]) / 2};
		}
		else if (target1[0] - target2[0] == 0)
		{
			return vector<float>{(now2[0] + target1[0]) / 2, now2[1]};
		}
		else
		{
			double a1 = (now1[1] - now2[1]) / (now1[0] - now2[0]);
			double b1 = now1[1] - a1 * now1[0];
			double a2 = (target1[1] - target2[1]) / (target1[0] - target2[0]);
			double b2 = target1[1] - a2 * target1[0];
			double x = (b2 - b1) / (a1 - a2);
			double y = a1 * x + b1;
			return { (float)(x + now2[0]) / 2,(float)(y + now2[1]) / 2 };
		}
	}

	void linkCross(Road* now, Road* target)
	{
		bezierPoints.push_back(now->bezierPoints[now->bezierPoints.size() - 1]);

		bezierPoints.push_back(controlPoint(now->bezierPoints[now->bezierPoints.size() - 2], now->bezierPoints[now->bezierPoints.size() - 1], target->bezierPoints[0], target->bezierPoints[1]));

		bezierPoints.push_back(controlPoint(target->bezierPoints[1],target->bezierPoints[0], now->bezierPoints[now->bezierPoints.size() - 1], now->bezierPoints[now->bezierPoints.size() - 2]));

		bezierPoints.push_back(target->bezierPoints[0]);

		now->after.push_back(target);
	}
};

