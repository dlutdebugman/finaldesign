#pragma once
#include <string>
#include <vector>
#include "util.h"
#include "LRT.h"

typedef std::vector<const LRT*> SourceVector;

template <class T>
struct Box
{
	T first, second;
	Box()
	{
		first = second = 0;
	}
};

class Date
{
public:

	int R; //区域
	int T = 12; //时隙

	SourceVector sv;

	Box<double>* location; //index by <region index r>

	Date() {};

	Date(std::string geoFile)
	{
		FILE* fin;
		errno_t err;
		bool error;

		//读地理文件
		err = fopen_s(&fin, geoFile.c_str(), "r");
		util::ODassert(err == 0, "Cannot open file " + geoFile);

		error = false;
		error = error || (fscanf_s(fin, "%d", &R) != 1);
		util::createArray<Box<double>>(location, R);
		for (int r = 0; r < R; ++r)
		{
			error = error || (fscanf_s(fin, "%lf%lf", &(location[r].first), &(location[r].second)) != 2);
		}
		util::ODassert(err == 0, geoFile + "file format error");
		fclose(fin);
	}

	void addSource(const LRT* lrt)
	{
		sv.push_back(lrt);
	}

	void printSet(const i_set &nodeSet, double lrtScore = 0, bool detail = true) const
	{
		i_set::const_iterator cIter;
		if (detail)
			printf("==================\n");
		if (lrtScore != 0)
		{
			if (detail)
				printf("LRTScore is %lf\n", lrtScore);
		}
		for (cIter = nodeSet.begin(); cIter != nodeSet.end(); ++cIter)
		{
			if (detail)
			{
				printf("%d %d:\t%lf %lf\n", *cIter % R, *cIter / R, location[*cIter % R].first, location[*cIter % R].second);
				for (int source = 0; source < sv.size(); ++source)
				{
					const DataSource* ds = sv[source]->d;
					const LRT* lrt = sv[source];

					for (int n = 0; n < ds->N; ++n)
						for (int w = 0; w < ds->SetWordCnt[n]; ++w)
						{
							if (ds->extraLambda)
							{
								double mean = ds->lambda[(*cIter) % R][(*cIter) / R][n][w];
								double var = ds->lambda2[(*cIter) % R][(*cIter) / R][n][w];
								int cnt = ds->cnt[(*cIter) % R][(*cIter) / R][n][w];
								double x = 2 * (lrt->lnLikelihood(cnt, 2, cnt*1.0, var / mean * cnt) - lrt->lnLikelihood(cnt, 2, mean, var));
								if (x <= 0)
									continue;
								x = boost::math::gamma_p(0.5, x / 2);
								printf("%d %d: %d %lf %lf %lf\n", n, w, ds->cnt[(*cIter) % R][(*cIter) / R][n][w], ds->lambda[(*cIter) % R][(*cIter) / R][n][w], ds->lambda2[(*cIter) % R][(*cIter) / R][n][w], x);
							}
							else
								printf("%d %d: %d %lf\n", n, w, ds->cnt[(*cIter) % R][(*cIter) / R][n][w], ds->lambda[(*cIter) % R][(*cIter) / R][n][w]);
						}
					printf("\n");
				}
			}
			else
			{
				printf("%d %d %lf %lf\n", *cIter % R, *cIter / R, location[*cIter % R].first, location[*cIter % R].second);
			}

		}
	}

	void visualize()
	{
		writeRegionTime(308, 3, 8);
		writeRegionTime(313, 3, 8);
	}

	void writeRegionTime(int r, int begin, int end)
	{
		printf("%d %d %d\n", r, begin, end);
		for (int source = 0; source < sv.size(); ++source)
		{
			const DataSource* ds = sv[source]->d;
			if (!ds->extraLambda)
				continue;
			for (int n = 0; n < ds->N; ++n)
				for (int w = 0; w < ds->SetWordCnt[n]; ++w)
				{
					printf("cnt <- c(");
					for (int t = begin; t < end; ++t)
					{
						if (t < end - 1)
						{
							printf("%d,", ds->cnt[r][t][n][w]);
						}
						else
							printf("%d", ds->cnt[r][t][n][w]);
					}
					printf(")\n");
					printf("mean <- c(");
					for (int t = begin; t < end; ++t)
					{
						if (t < end - 1)
						{
							printf("%lf,", ds->lambda[r][t][n][w]);
						}
						else
							printf("%lf", ds->lambda[r][t][n][w]);
					}
					printf(")\n");
					printf("sd <- c(");
					for (int t = begin; t < end; ++t)
					{
						if (t < end - 1)
						{
							printf("%lf,", ds->lambda2[r][t][n][w]);
						}
						else
							printf("%lf", ds->lambda2[r][t][n][w]);
					}
					printf(")\n");
				}
		}

		for (int source = 0; source < sv.size(); ++source)
		{
			const DataSource* ds = sv[source]->d;
			if (!ds->extraLambda)
				continue;
			for (int n = 0; n < ds->N; ++n)
				for (int w = 0; w < ds->SetWordCnt[n]; ++w)
				{
					for (int t = begin; t < end; ++t)
					{
						double mean = ds->lambda[r][t][n][w];
						if (mean == 0)
						{
							printf("%lf ", 0);
							continue;
						}
						double var = ds->lambda2[r][t][n][w];
						int cnt = ds->cnt[r][t][n][w];

						double x = 2 * (sv[source]->lnLikelihood(cnt, 2, cnt*1.0, var / mean * cnt) - sv[source]->lnLikelihood(cnt, 2, mean, var));
						if (x <= 0)
						{
							printf("%lf ", 0);
							continue;
						}
						x = boost::math::gamma_p(0.5, x / 2);
						printf("%lf ", x);
					}
					printf("\n");
				}
			printf("\n");
		}
	}


	~Date()
	{
		util::deleteArray(location);
	}
};
