#pragma once
#include "Entity.h"
#include "trajectory.h"
#include "openGL.h"
#include "Road.h"
#include"central.h"

#define STEP_LENGTH 0.01



class Car :public Entity
{
public:
	float x, y;
	float velocity, acceleration;

	trajectory* trajectory;
	float T = 0;
	queue<Road*> path;

	Road* origin;
	Road* destination;

	Car(Road* origin,Road* destination,float velocity,float acceleration)
	{
		this->x = origin->bezierPoints[0][0];
		this->y = origin->bezierPoints[0][1];            
		this->origin = origin;
		this->trajectory = origin;
		this->destination = destination;
		this->velocity = velocity;
		this->acceleration = acceleration;
	}

	void update()
	{
		//更新一个步长内车辆的信息
	}

	void draw()
	{
		glPointSize(pointWidth);
		glBegin(GL_POINTS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(x, y);
		glEnd();            
	}
};

