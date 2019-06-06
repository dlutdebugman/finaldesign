#pragma once
#include "stdafx.h"
#include <vector>
#include <set>
#include <algorithm>
#include <stdarg.h>
#include "util.h"
#include "DataSource.h"

class LRT
{
protected:

	double lnFactor[10000];

public:

	const DataSource* d;

	LRT() {}

	LRT(const DataSource* d) : d(d)
	{
		lnFactor[0] = lnFactor[1] = 0;
		for (int i = 2; i < 10000; ++i)
		{
			lnFactor[i] = lnFactor[i - 1] + log(i);
		}
	}

	~LRT();

	void getValid(const std::set<int> &nodeSet, bool** &valid) const
	{
		std::set<int>::iterator iter;
		util::createArray<bool*>(valid, d->N);
		for (int n = 0; n < d->N; ++n)
		{
			valid[n] = new bool[d->SetWordCnt[n]];
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				valid[n][w] = true;
			}
		}

		int sumCnt;
		for (int n = 0; n < d->N; ++n)
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				sumCnt = 0;
				for (iter = nodeSet.begin(); iter != nodeSet.end(); ++iter)
				{
					if (d->lambda[(*iter) % d->R][(*iter) / d->R][n][w] != 0)
						sumCnt += d->cnt[(*iter) % d->R][(*iter) / d->R][n][w];
				}
				if (sumCnt == 0)
					valid[n][w] = false;
			}
	}

	int getValidCnt(const std::set<int> &nodeSet) const
	{
		std::set<int>::iterator iter;
		int ret = 0;
		int sumCnt;
		for (int n = 0; n < d->N; ++n)
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				sumCnt = 0;
				for (iter = nodeSet.begin(); iter != nodeSet.end(); ++iter)
				{
					if (d->lambda[(*iter) % d->R][(*iter) / d->R][n][w] != 0)
						sumCnt += d->cnt[(*iter) % d->R][(*iter) / d->R][n][w];
				}
				if (sumCnt > 0)
					++ret;
			}
		return ret;
	}

	inline virtual double lnLikelihood(int cnt, int pCnt, ...) const = 0;

	virtual double getUpBound(const std::set<int> &nodeSet) const = 0;

	virtual double getLRT(const std::set<int> &nodeSet) const = 0;
};

/* deprected
class PoissonLRT : public LRT
{
public:

PoissonLRT(const Data* d) : LRT(d)
{
}

~PoissonLRT();

virtual double getLRT(const std::set<int> &allNode, const std::set<int> &nodeSet) const
{
std::set<int>::iterator iter;
std::set<int> nodeCompSet = std::set<int>();
std::set_difference(allNode.begin(), allNode.end(), nodeSet.begin(), nodeSet.end(), std::inserter(nodeCompSet, nodeCompSet.begin()));
bool** valid;
util::create1dArray<bool*>(valid, d->N);
for (int n = 0; n < d->N; ++n)
{
valid[n] = new bool[d->SetWordCnt[n]];
for (int w = 0; w < d->SetWordCnt[n]; ++w)
{
valid[n][w] = true;
}
}

int sumCnt;
for (int n = 0; n < d->N; ++n)
for (int w = 0; w < d->SetWordCnt[n]; ++w)
{
sumCnt = 0;
for (iter = nodeSet.begin(); iter != nodeSet.end(); ++iter)
{
sumCnt += d->cnt[(*iter) % d->R][(*iter) / d->R][n][w];
}
if (sumCnt == 0)
valid[n][w] = false;
sumCnt = 0;
for (iter = nodeCompSet.begin(); iter != nodeCompSet.end(); ++iter)
{
sumCnt += d->cnt[(*iter) % d->R][(*iter) / d->R][n][w];
}
if (sumCnt == 0)
valid[n][w] = false;
}

double ret = 2 * (getModifiedLnLikelihood(nodeSet, valid) + getModifiedLnLikelihood(nodeCompSet, valid) - getModifiedLnLikelihood(allNode, valid));
util::delete2dArray(valid, d->N);
return ret;
}
};
*/

class ZipLRT : public LRT
{
public:

	ZipLRT(const DataSource* d) : LRT(d)
	{
	}

	~ZipLRT();

	inline double lnLikelihood(int cnt, int pCnt, ...) const
	{
		util::ODassert(pCnt == 1, "Poisson likelihood parameter number error");
		va_list ap;
		va_start(ap, pCnt); //Requires the last fixed parameter (to get the address)
		double lambda = va_arg(ap, double); //Requires the type to cast to. Increments ap to the next argument.
		va_end(ap);
		return (-lambda + cnt*log(lambda) - lnFactor[cnt]);
	}



	double getOriginLnLikelihood(const std::set<int> &nodeSet) const
	{
		bool** valid;
		getValid(nodeSet, valid);

		double ret = 0;
		std::set<int>::iterator iter;
		for (int n = 0; n < d->N; ++n)
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
				if (valid[n][w])
				{
					double lambda;
					int cnt;

					for (iter = nodeSet.begin(); iter != nodeSet.end(); ++iter)
					{
						lambda = d->lambda[(*iter) % d->R][(*iter) / d->R][n][w];
						if (lambda != 0)
						{
							cnt = d->cnt[(*iter) % d->R][(*iter) / d->R][n][w];
							ret += lnLikelihood(cnt, 1, lambda);
						}
					}
				}
		util::delete2dArray(valid, d->N);
		return ret;
	}

	double getModifiedLnLikelihood(const std::set<int> &nodeSet) const
	{
		bool** valid;
		getValid(nodeSet, valid);

		double ret = 0;
		std::set<int>::iterator iter;
		for (int n = 0; n < d->N; ++n)
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
				if (valid[n][w])
				{
					int sumCnt = 0;
					double sumLambda = 0;
					double p, lambda;
					int cnt;
					for (iter = nodeSet.begin(); iter != nodeSet.end(); ++iter)
					{
						if (d->lambda[(*iter) % d->R][(*iter) / d->R][n][w] != 0)
						{
							sumCnt += d->cnt[(*iter) % d->R][(*iter) / d->R][n][w];
							sumLambda += d->lambda[(*iter) % d->R][(*iter) / d->R][n][w];
						}
					}

					p = sumCnt / sumLambda;
					if (p < 1)
						p = 1;

					for (iter = nodeSet.begin(); iter != nodeSet.end(); ++iter)
					{
						lambda = d->lambda[(*iter) % d->R][(*iter) / d->R][n][w] * p;
						if (lambda != 0)
						{
							cnt = d->cnt[(*iter) % d->R][(*iter) / d->R][n][w];
							ret += lnLikelihood(cnt, 1, lambda);
						}
					}
				}
		util::delete2dArray(valid, d->N);
		return ret;
	}

	double getUpBound(const std::set<int> &nodeSet) const
	{
		bool** valid;
		getValid(nodeSet, valid);

		double ret = 0;
		std::set<int>::iterator iter;
		for (int n = 0; n < d->N; ++n)
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
				if (valid[n][w])
				{
					double lambda;
					int cnt;
					for (iter = nodeSet.begin(); iter != nodeSet.end(); ++iter)
					{
						lambda = d->lambda[(*iter) % d->R][(*iter) / d->R][n][w];
						cnt = d->cnt[(*iter) % d->R][(*iter) / d->R][n][w];

						if (cnt == 0) // for cnt = 0, cuz p>=1, the best situation is p=1
							continue;

						ret += lnLikelihood(cnt, 1, cnt*1.0) - lnLikelihood(cnt, 1, lambda);
					}
				}
		util::delete2dArray(valid, d->N);
		ret *= 2;
		if (ret <= 0)
			return 0;
		else
			return boost::math::gamma_p(getValidCnt(nodeSet)*1.0 / 2, ret / 2);
	}

	double getLRT(const std::set<int> &nodeSet) const
	{
		double ret = 2 * (getModifiedLnLikelihood(nodeSet) - getOriginLnLikelihood(nodeSet));
		if (ret <= 0)
			return 0;
		else
			return boost::math::gamma_p(getValidCnt(nodeSet)*1.0 / 2, ret / 2);
	}
};

class NormLRT : public LRT
{
public:

	NormLRT(const DataSource* d) : LRT(d)
	{
	}

	~NormLRT();

	inline double getVar(double mean) const
	{
		//return (0.00962799 * mean * mean - 23.00133 * mean + 16395.8);
		return 4 * mean;
	}

	inline double lnLikelihood(int cnt, int pCnt, ...) const
	{
		util::ODassert(pCnt == 2, "Normal likelihood parameter number error");
		va_list ap;
		va_start(ap, pCnt);
		double mean = va_arg(ap, double);
		double var = va_arg(ap, double);
		va_end(ap);

		if (mean == 0)
			return 1e-6;
		return (-0.5*std::log(2 * PI * var) - (cnt - mean) * (cnt - mean) / (2 * var));
	}

	double getUpBound(const std::set<int> &nodeSet) const
	{
		double ret = 0;
		std::set<int>::iterator iter;
		for (int n = 0; n < d->N; ++n)
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				double lambda;
				int cnt;
				for (iter = nodeSet.begin(); iter != nodeSet.end(); ++iter)
				{
					lambda = d->lambda[(*iter) % d->R][(*iter) / d->R][n][w];
					cnt = d->cnt[(*iter) % d->R][(*iter) / d->R][n][w];

					ret += lnLikelihood(cnt, 2, cnt*1.0, getVar(cnt*1.0)) - lnLikelihood(cnt, 2, lambda, getVar(lambda));
				}
			}
		return 2 * ret;
	}

	double getLRT(const std::set<int> &nodeSet) const
	{
		double ret = 0;
		std::set<int>::iterator iter;
		for (int n = 0; n < d->N; ++n)
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				double lambda;
				int cnt;
				for (iter = nodeSet.begin(); iter != nodeSet.end(); ++iter)
				{
					lambda = d->lambda[(*iter) % d->R][(*iter) / d->R][n][w];
					cnt = d->cnt[(*iter) % d->R][(*iter) / d->R][n][w];

					ret += lnLikelihood(cnt, 2, cnt*1.0, getVar(cnt*1.0)) - lnLikelihood(cnt, 2, lambda, getVar(lambda));
				}
			}
		return 2 * ret;
	}
};

class NormConfidence : public LRT
{
public:

	NormConfidence(const DataSource *d) : LRT(d)
	{

	}

	~NormConfidence();

	inline double lnLikelihood(int cnt, int pCnt, ...) const
	{
		util::ODassert(pCnt == 2, "Normal likelihood parameter number error");
		va_list ap;
		va_start(ap, pCnt);
		double mean = va_arg(ap, double);
		double var = va_arg(ap, double);
		va_end(ap);

		if (mean == 0)
			return 1e-6;
		return (-0.5*std::log(2 * PI * var) - (cnt - mean) * (cnt - mean) / (2 * var));
	}

	double getUpBound(const std::set<int> &nodeSet) const
	{
		double ret = 0;
		std::set<int>::iterator iter;
		int nwCnt = 0;
		for (int n = 0; n < d->N; ++n)
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				double mean, var, x;
				int cnt;
				for (iter = nodeSet.begin(); iter != nodeSet.end(); ++iter)
				{
					nwCnt++;
					mean = d->lambda[(*iter) % d->R][(*iter) / d->R][n][w];
					if (mean == 0)
						continue;
					var = d->lambda2[(*iter) % d->R][(*iter) / d->R][n][w];
					cnt = d->cnt[(*iter) % d->R][(*iter) / d->R][n][w];

					x = 2 * (lnLikelihood(cnt, 2, cnt*1.0, var / mean * cnt) - lnLikelihood(cnt, 2, mean, var));
					if (x <= 0)
						continue;
					x = boost::math::gamma_p(0.5, x / 2);
					ret = fmax(ret, x);
				}
			}
		return ret;
	}

	double getLRT(const std::set<int> &nodeSet) const
	{
		double ret = 0;
		std::set<int>::iterator iter;
		int nwCnt = 0;
		for (int n = 0; n < d->N; ++n)
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				double mean, var, x;
				int cnt;
				for (iter = nodeSet.begin(); iter != nodeSet.end(); ++iter)
				{
					nwCnt++;
					mean = d->lambda[(*iter) % d->R][(*iter) / d->R][n][w];
					if (mean == 0)
						continue;
					var = d->lambda2[(*iter) % d->R][(*iter) / d->R][n][w];
					cnt = d->cnt[(*iter) % d->R][(*iter) / d->R][n][w];

					x = 2 * (lnLikelihood(cnt, 2, cnt*1.0, var / mean * cnt) - lnLikelihood(cnt, 2, mean, var));
					if (x <= 0)
						continue;
					x = boost::math::gamma_p(0.5, x / 2);
					ret += x*x;
				}
			}
		//return 1 / (1+exp(-sqrt(ret/nwCnt)));
		return (sqrt(ret / nwCnt));
	}
};

class Stupid : public LRT
{
public:

	Stupid(const DataSource *d) : LRT(d)
	{

	}

	~Stupid();

	inline double lnLikelihood(int cnt, int pCnt, ...) const
	{
		util::ODassert(pCnt == 2, "Normal likelihood parameter number error");
		va_list ap;
		va_start(ap, pCnt);
		double mean = va_arg(ap, double);
		double var = va_arg(ap, double);
		va_end(ap);

		if (mean == 0)
			return 1e-6;
		return (-0.5*std::log(2 * PI * var) - (cnt - mean) * (cnt - mean) / (2 * var));
	}

	double getUpBound(const std::set<int> &nodeSet) const
	{
		return 0;
	}

	double getLRT(const std::set<int> &nodeSet) const
	{
		double ret = 0;
		std::set<int>::iterator iter;
		int nwCnt = 0;
		for (int n = 0; n < d->N; ++n)
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				double mean, var, x;
				int cnt;
				for (iter = nodeSet.begin(); iter != nodeSet.end(); ++iter)
				{
					nwCnt++;
					mean = d->lambda[(*iter) % d->R][(*iter) / d->R][n][w];
					if (mean == 0)
						continue;
					var = d->lambda2[(*iter) % d->R][(*iter) / d->R][n][w];
					cnt = d->cnt[(*iter) % d->R][(*iter) / d->R][n][w];

					x = (cnt - mean) / sqrt(var);
					ret += x*x;
				}
			}
		//return 1 / (1+exp(-sqrt(ret/nwCnt)));
		return (sqrt(ret / nwCnt));
	}
};