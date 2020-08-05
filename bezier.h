#pragma once
#include<vector>

using std::vector;


//目前只支持控制点数为4的贝塞尔曲线
//若pointCount数不为4，bezierPoint方法和bezierSlope方法都要重写(公式不对)
class Bezier
{
public:
	//int pointCount;
	//vector<vector<float>>controlPoints;//控制点存储数组
	
	static void bezierPoint(float T, vector<float>&vertex3f, vector<vector<float>>controlPoints)
	{
		float f1 = (1 - T) * (1 - T) * (1 - T);
		float f2 = 3 * T * (1 - T) * (1 - T);
		float f3 = 3 * T * T * (1 - T);
		float f4 = T * T * T;
		vertex3f[0] = f1 * controlPoints[0][0] + f2 * controlPoints[1][0] + f3 * controlPoints[2][0] + f4 * controlPoints[3][0];
		vertex3f[1] = f1 * controlPoints[0][1] + f2 * controlPoints[1][1] + f3 * controlPoints[2][1] + f4 * controlPoints[3][1];
		vertex3f[2] = f1 * controlPoints[0][2] + f2 * controlPoints[1][2] + f3 * controlPoints[2][2] + f4 * controlPoints[3][2];
	}

	static void bezierSlope(float T)//对贝塞尔公式求导得到斜率
	{
		
	}

};


