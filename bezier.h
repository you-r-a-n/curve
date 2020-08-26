#pragma once
#include<vector>

using std::vector;


//Ŀǰֻ֧�ֿ��Ƶ���Ϊ4�ı���������
//��pointCount����Ϊ4��bezierPoint������bezierSlope������Ҫ��д(��ʽ����)
class Bezier
{
public:
	//int pointCount;
	//vector<vector<float>>controlPoints;//���Ƶ�洢����
	
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

	static void bezierSlope(float T)//�Ա�������ʽ�󵼵õ�б��
	{
		
	}

};


