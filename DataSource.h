#pragma once
#include <string>
#include <vector>
#include "util.h"

class DataSource
{

public:

	int R;
	int T;
	int N; //词集号
	int* SetWordCnt; //每个单词集中不同单词的数量, index by <word set index n>
	int**** cnt; //index by <region index r, time slot t, word set index n, word index w>
	double**** lambda; //index by <region index r, time slot t, word set index n, word index w>
	double**** lambda2; //index by <region index r, time slot t, word set index n, word index w>

	bool extraLambda;

	DataSource()
	{
		R = T = N = 0;
	}

	DataSource(std::string lambdaFile, std::string cntFile, int R, int T, bool extraLambda = false) : R(R), T(T), extraLambda(extraLambda)
	{
		FILE* fin;
		errno_t err;
		bool error;

		//读lambda文件
		err = fopen_s(&fin, lambdaFile.c_str(), "r");
		util::ODassert(err == 0, "Cannot open file " + lambdaFile);

		error = false;
		int RTmp;
		error = error || (fscanf_s(fin, "%d", &RTmp) != 1);
		util::ODassert(R == RTmp, "R doesn't match");
		error = error || (fscanf_s(fin, "%d", &N) != 1);
		util::createArray<int>(SetWordCnt, N);

		for (int n = 0; n < N; ++n)
		{
			error = error || (fscanf_s(fin, "%d", &SetWordCnt[n]) != 1);
		}

		util::create3dArray<double*>(lambda, R, T, N);
		util::create3dArray<int*>(cnt, R, T, N);
		if (extraLambda)
			util::create3dArray<double*>(lambda2, R, T, N);
		for (int r = 0; r < R; ++r)
			for (int t = 0; t < T; ++t)
				for (int n = 0; n < N; ++n)
				{
					lambda[r][t][n] = new double[SetWordCnt[n]]();
					cnt[r][t][n] = new int[SetWordCnt[n]]();
					if (extraLambda)
						lambda2[r][t][n] = new double[SetWordCnt[n]]();
				}

		for (int r = 0; r < R; ++r)
			for (int n = 0; n < N; ++n)
				for (int t = 0; t < T; ++t)
					for (int w = 0; w < SetWordCnt[n]; ++w)
					{
						error = error || (fscanf_s(fin, "%lf", &lambda[r][t][n][w]) != 1);
						if (extraLambda)
							error = error || (fscanf_s(fin, "%lf", &lambda2[r][t][n][w]) != 1);
					}

		util::ODassert(err == 0, lambdaFile + "file format error");
		fclose(fin);

		//读cnt文件
		err = fopen_s(&fin, cntFile.c_str(), "r");
		util::ODassert(err == 0, "Cannot open file " + cntFile);

		error = false;
		for (int r = 0; r < R; ++r)
			for (int n = 0; n < N; ++n)
				for (int t = 0; t < T; ++t)
					for (int w = 0; w < SetWordCnt[n]; ++w)
					{
						error = error || (fscanf_s(fin, "%d", &cnt[r][t][n][w]) != 1);
					}
		util::ODassert(err == 0, cntFile + "file format error");
		fclose(fin);
	}

	~DataSource()
	{
		util::deleteArray(SetWordCnt);
		util::delete4dArray(cnt, R, T, N);
		util::delete4dArray(lambda, R, T, N);
		if (extraLambda)
			util::delete4dArray(lambda2, R, T, N);
	}
};