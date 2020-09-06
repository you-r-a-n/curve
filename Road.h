#pragma once
#include<vector>
#include "trajectory.h"
#include "Entity.h"
#define ROAD_WIDTH 0.1

using std::vector;

class Road :public Entity, public trajectory
{
public:
	static vector<Road*> g_road;
	vector<vector<float>> bezierPoints;
	bool isOrigin = false;
	bool isDestination = false;
	vector<Road*>adjoin;
	vector<Road*>after;

	virtual Road* clone() = 0;

	void setOrigin()
	{
		this->isOrigin = true;
	}
	
	void setDestination()
	{
		this->isDestination = true;
	}

	void move(float x, float y)
	{
		vector<vector<float>>::iterator itr = this->bezierPoints.begin();
		while (itr != this->bezierPoints.end()) {
			(*itr)[0] += x;
			(*itr)[1] += y;
			itr++;
		}
	}

	void reverse()
	{
		for (int i = 0; i < bezierPoints.size() / 2; ++i)
		{
			vector<float> temp = bezierPoints[i];
			bezierPoints[i] = bezierPoints[bezierPoints.size() - 1 - i];
			bezierPoints[bezierPoints.size() - 1 - i] = temp;
		}
	}
};

vector<Road*> Road::g_road;