#pragma once
#include <set>
#include <vector>
#include "util.h"

class Detector;

class Skyline
{

public:

	skyline_set* skylines;
	int dim;

	Skyline(int dim) : dim(dim)
	{
		skylines = new skyline_set();
	}

	~Skyline()
	{
		skyline_set::iterator iter;
		for (iter = skylines->begin(); iter != skylines->end(); ++iter)
		{
			delete (*iter)->first;
			delete *iter;
		}
		delete skylines;
	}

	int count()
	{
		return skylines->size();
	}

	bool check(const d_vec &v)
	{
		util::ODassert(v.size() == dim, "od vector size error!");
		skyline_set::iterator iter;
		int geCnt, gCnt;

		for (iter = skylines->begin(); iter != skylines->end(); iter++)
		{
			d_vec* p = (*iter)->first;
			geCnt = 0;
			gCnt = 0;
			for (int d = 0; d < dim; ++d)
			{
				if (v[d] >= (*p)[d])
					geCnt++;
				if (v[d] >(*p)[d])
					gCnt++;
			}
			if (gCnt == 0)
				return false;
		}
		return true;
	}

	bool add(const d_vec &v, const i_set& nodeSet)
	{
		util::ODassert(v.size() == dim, "od vector size error!");
		skyline_set::iterator iter;
		int geCnt;
		int gCnt;

		for (iter = skylines->begin(); iter != skylines->end();)
		{
			d_vec* p = (*iter)->first;
			geCnt = 0;
			gCnt = 0;
			for (int d = 0; d < dim; ++d)
			{
				if (v[d] >= (*p)[d])
					geCnt++;
				if (v[d] >(*p)[d])
					gCnt++;
			}
			if (gCnt == 0)
				return false;
			if (geCnt == dim)
			{
				delete *iter;
				skylines->erase(iter++);
			}
			else
			{
				++iter;
			}
		}
		d_vec* pn = new d_vec(v);
		skyline_item* ip = new skyline_item(pn, nodeSet);
		skylines->insert(ip);
		return true;
	}

	void print(const Date* data)
	{
		skyline_set::iterator iter;
		for (iter = skylines->begin(); iter != skylines->end(); iter++)
		{
			d_vec* p = (*iter)->first;
			for (int d = 0; d < dim; ++d)
			{
				printf("%lf ", (*p)[d]);
			}
			printf("\n");
			//data->printSet((*iter)->second, 0, true);
		}
	}

};

