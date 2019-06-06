#pragma once
#include "Data.h"
#include "LRT.h"
#include "util.h"
#include "Skyline.h"
#include <ctime>
#include <map>
#include <algorithm>
using namespace std;

class Detector
{
protected:

	const Date *data;

	bool* skip;
	int timeRange;
	double regionRange;
	double lrtThres; //阈值
	int totalSkip;
	int outlierCnt;  //异常
	std::clock_t tStart, tEnd;

	std::set<outlier> outliers;
	Skyline* skyline;

	FILE* fout;

public:

	Detector(const Date *data, double lrtThres, int timeRange, double regionRange) : data(data), lrtThres(lrtThres), timeRange(timeRange), regionRange(regionRange)
	{
		//fopen_s(&fout, "D:\\candidates.txt", "w");
		skyline = new Skyline(data->sv.size());
	}

	virtual ~Detector()
	{
		//fclose(fout);
		delete skyline;
	}

	virtual void detect() = 0;
	virtual void summary() = 0;

	inline d_vec* getLRTUpperBoundVector(const i_set& nodeSet)
	{
		d_vec* p = new d_vec();
		for (int source = 0; source < data->sv.size(); ++source)
			p->push_back(data->sv[source]->getUpBound(nodeSet));
		return p;
	}

	inline d_vec* getLRTVector(const i_set& nodeSet)
	{
		d_vec* p = new d_vec();
		for (int source = 0; source < data->sv.size(); ++source)
		{
			p->push_back(data->sv[source]->getLRT(nodeSet));
			//fprintf_s(fout, "%lf ", data->sv[source]->getLRT(nodeSet));
		}
		//fprintf_s(fout, "\n");
		return p;
	}

	inline double getLRTUpperBound(const i_set& nodeSet)
	{
		double lrtScore = 1;
		for (int source = 0; source < data->sv.size(); ++source)
			lrtScore *= data->sv[source]->getUpBound(nodeSet);
		return lrtScore;
	}

	inline double getLRTScore(const i_set& nodeSet)
	{
		double sum = 0;
		bool cand = true;
		for (int source = 0; source < data->sv.size(); ++source)
		{
			sum += pow(data->sv[source]->getLRT(nodeSet), 2);
		}
		return 1 / (1 + exp(-sqrt(sum)));
	}
};

class CoolDetector : public Detector
{
private:

	pdi_i_set* points;
	i_vec* sequence;
	i_vec* start;
	int startTime, endTime;
	bool cut = false;

public:

	CoolDetector(const Date *data, double lrtThres, int timeRange, double regionRange, int startTime, int endTime) : Detector(data, lrtThres, timeRange, regionRange), startTime(startTime), endTime(endTime)
	{
		skip = new bool[data->R * data->T];
		for (int i = 0; i < data->R * data->T; ++i)
			skip[i] = false;

		points = new pdi_i_set[data->R]();
		sequence = new i_vec[data->R]();
		start = new i_vec[data->R]();

		totalSkip = 0;
		outlierCnt = 0;
	}

	~CoolDetector()
	{
		delete[] points;
		delete[] sequence;
		delete[] start;
	}

	void search(i_set& origin, i_set& cur, i_set::iterator iter)
	{
		if (iter == origin.end())
		{
			d_vec* ptr = getLRTVector(cur);
			skyline->add(*ptr, cur);
			delete ptr;
			return;
		}

		search(origin, cur, next(iter, 1));

		//delete
		cur.erase(*iter);
		d_vec* ptr = getLRTUpperBoundVector(cur);
		if (skyline->check(*ptr) || !cut)
			search(origin, cur, next(iter, 1));
		delete ptr;
		cur.insert(*iter);
	}

	void detect()
	{
		for (int r1 = 0; r1 < data->R; ++r1)
			for (int r2 = 0; r2 < data->R; ++r2)
				//if (r1 != r2)
			{
				pdd pair = util::getAngles(regionRange, data->location[r1].first, data->location[r1].second, data->location[r2].first, data->location[r2].second);
				if (pair.first == 0 && pair.second == 0)
					continue;
				points[r1].insert(std::make_pair(std::make_pair(pair.first, r2), 1));
				points[r1].insert(std::make_pair(std::make_pair(pair.second, r2), 0));
				if (pair.first > pair.second)
				{
					start[r1].push_back(r2);
				}
			}

		for (int r = 0; r < data->R; ++r)
		{
			pdi_i_set::const_iterator cIter;
			for (cIter = points[r].begin(); cIter != points[r].end(); ++cIter)
			{
				sequence[r].push_back(((*cIter).second ? 1 : -1) * ((*cIter).first.second + 1)); //识别在没在区域0
			}
		}

		tStart = std::clock();

		for (int r = 0; r < data->R; ++r)
		{
			for (int t = startTime; t < endTime - timeRange; ++t)
			{
				bool onlyOne = false;
				i_set nodeSet;
				for (int tNear = t; tNear <= t + timeRange; ++tNear)
					nodeSet.insert(tNear * data->R + r);

				int rSum = 0;
				for (int i = 0; i < start[r].size(); ++i)
				{
					rSum += start[r][i];
					for (int tNear = t; tNear <= t + timeRange; ++tNear)
						nodeSet.insert(tNear * data->R + start[r][i]);
				}

				if (rSum == 0)
					onlyOne = true;
				d_vec* ptr = getLRTUpperBoundVector(nodeSet);
				if (skyline->check(*ptr))
					search(nodeSet, i_set(nodeSet), nodeSet.begin());
				delete ptr;

				for (int i = 0; i < sequence[r].size() - 1; ++i)
				{
					rSum += sequence[r][i];
					if (sequence[r][i] < 0)
					{
						for (int tNear = t; tNear <= t + timeRange; ++tNear)
							nodeSet.erase(tNear * data->R - sequence[r][i] - 1);
					}
					else
					{
						for (int tNear = t; tNear <= t + timeRange; ++tNear)
							nodeSet.insert(tNear * data->R + sequence[r][i] - 1);
					}

					if (!(rSum == 0 && onlyOne))
					{
						if (rSum == 0)
							onlyOne = true;
						d_vec* ptr = getLRTUpperBoundVector(nodeSet);
						if (skyline->check(*ptr))
							search(nodeSet, i_set(nodeSet), nodeSet.begin());
						delete ptr;
					}

				}
				//cout << "1";
			}
			//cout << "2";
		}

		tEnd = std::clock();
	}

	void summary()
	{
		skyline->print(data);
	}
};