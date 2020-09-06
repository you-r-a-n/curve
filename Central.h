#pragma once
#include<map>
#include"Road.h"
#include <queue>
#include <set>
using namespace std;

class Central
{
public:
	static map<vector<Road*, Road*>, Road* > roadMap; 
	
	//!!�Ȳ�����now��destinationû�п��е�·�����
	static Road* getNextPath(Road* now, Road* destination)
	{
		if (now == destination) return nullptr;

		map<vector<Road*, Road*>, Road* >::iterator path = Central::roadMap.find({ now,destination });
		//ת�����л�������
		if (path != roadMap.end())
		{
			return path->second;
		}
		//ת������û����Ϣ
		//������������ҵ�һ����now��destination�ĵ�·�������������Ϣ����
		else
		{
			vector<Road*>roadChain;
			set<Road*> visited;
			set<Road*>::iterator iter;
			Road* cursor = now;
			while (cursor != destination)
			{
				visited.insert(cursor);
				if (cursor->after.size()==0)
				{
					cursor = (*roadChain.end());
				}
				else if (cursor->after.size() != 0)
				{
					roadChain.push_back(cursor);
					for (int i = 0; i < cursor->after.size(); ++i)
					{
						if ((iter = visited.find(cursor->after[i])) != visited.end())
						{
							cursor = cursor->after[i];
						}
					}
					if (cursor == (*roadChain.end()))
					{
						roadChain.erase(roadChain.end());
						cursor = (*roadChain.end());
					}
				}
			}
			roadChain.push_back(cursor);
			//���roadChain����ӳ����Ϣ
			for (int i = 0; i < roadChain.size()-1; ++i)
			{
				Central::roadMap.insert(pair<vector<Road*, Road*>, Road*>({roadChain[i],destination}, roadChain[i + 1]));
			}
			return Central::roadMap.find({ now,destination })->second;
		}
	}
};

