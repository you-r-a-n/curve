#pragma once
#include <GL/glew.h>    
#include <GLFW/glfw3.h> 
#include"Road.h"

class Straight :public Road
{
public:
    Straight(vector<float>start, vector<float>end)
    {
        this->bezierPoints.push_back(start);
        this->bezierPoints.push_back(end);
        Road::g_road.push_back(this);
    }

    void draw()
    {
        //std::cout << "Straight draw" << std::endl;
        glBegin(GL_LINE_STRIP);
        glColor3f(0.8f, 0.2f, 0.5f);
        glVertex2f(bezierPoints[0][0], bezierPoints[0][1]);
        glVertex2f(bezierPoints[1][0], bezierPoints[1][1]);
        glEnd();

        glPointSize(5.0f);
        glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(bezierPoints[0][0], bezierPoints[0][1]);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(bezierPoints[1][0], bezierPoints[1][1]);
        glEnd();
    }

    

    Road* clone()
    {
        //std::cout << "Straight clone" << std::endl;
        return new Straight(this->bezierPoints[0],this->bezierPoints[1]);
    }
};

