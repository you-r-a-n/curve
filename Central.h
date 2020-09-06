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
	
	//!!先不考虑now到destination没有可行道路的情况
	static Road* getNextPath(Road* now, Road* destination)
	{
		if (now == destination) return nullptr;

		map<vector<Road*, Road*>, Road* >::iterator path = Central::roadMap.find({ now,destination });
		//转发表中缓存命中
		if (path != roadMap.end())
		{
			return path->second;
		}
		//转发表中没有信息
		//深度优先搜索找到一条由now到destination的道路链，并将拆分信息缓存
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
			//拆分roadChain插入映射信息
			for (int i = 0; i < roadChain.size()-1; ++i)
			{
				Central::roadMap.insert(pair<vector<Road*, Road*>, Road*>({roadChain[i],destination}, roadChain[i + 1]));
			}
			return Central::roadMap.find({ now,destination })->second;
		}
	}
};

