#include "stdafx.h"
#include "data.h"

using namespace std;

data::data()
{
	printf("请提供feature文件和word文件");
}

data::data(string fFile, string wFile)
{
	FILE* fin;
	errno_t err;
	bool error;

	//读feature文件
	err = fopen_s(&fin, fFile.c_str(), "r");
	util::TopicAssert(err == 0, "不能打开feature文件 " + fFile);

	error = false;
	//printf("%d", fscanf_s(fin, "%d", &R));
	error = error || (fscanf_s(fin, "%d", &R) != 1);
	error = error || (fscanf_s(fin, "%d", &F) != 1);
	F++;
	//创建区域特征矩阵
	util::create2dArray<double>(RegFeature, R, F);
	for (int r = 0; r < R; ++r)
	{
		for (int f = 0; f < F - 1; ++f)
		{
			error = error || (fscanf_s(fin, "%lf", &RegFeature[r][f]) != 1);
		}
		RegFeature[r][F - 1] = 1;
	}
	util::TopicAssert(error == false, "feature文件格式错误");
	fclose(fin);


	//读word文件
	err = fopen_s(&fin, wFile.c_str(), "r");
	util::TopicAssert(err == 0, "不能打开word文件 " + wFile);

	error = false;
	//判断word文件和feature文件中的地区数量是否相等
	int tempR;
	error = error || (fscanf_s(fin, "%d", &tempR) != 1);
	util::TopicAssert(tempR == R, "word文件和feature文件中的地区数量不相等");
	//计算单词集中不同单词的数量
	error = error || (fscanf_s(fin, "%d", &N) != 1);
	util::create1dArray<int>(SetWordCnt, N);
	util::create1dArray<int>(SetDaySec, N);
	util::create1dArray<int>(SetCate, N);
	for (int n = 0; n < N; ++n)
	{
		error = error || (fscanf_s(fin, "%d", &SetDaySec[n]) != 1);
		error = error || (fscanf_s(fin, "%d", &SetCate[n]) != 1);
		SetWordCnt[n] = SetDaySec[n] * SetCate[n];
	}

	//计算地区中每个单词的数量和区域中单词的总数
	util::create2dArray<int*>(RegWordCnt, R, N);
	util::create1dArray<int>(RegWordSum, R);
	for (int r = 0; r < R; ++r)
		for (int n = 0; n < N; ++n)
		{
			RegWordCnt[r][n] = new int[SetWordCnt[n]];
			for (int w = 0; w < SetWordCnt[n]; ++w)
			{
				error = error || (fscanf_s(fin, "%d", &RegWordCnt[r][n][w]) != 1);
				RegWordSum[r] += RegWordCnt[r][n][w];
			}
		}
	util::TopicAssert(error == false, "word file format error");
	fclose(fin);
}

data::~data()
{
	util::delete2dArray<double>(RegFeature, R);
	util::delete1dArray<int>(SetDaySec);
	util::delete1dArray<int>(SetCate);
	util::delete1dArray<int>(SetWordCnt);
	util::delete3dArray<int>(RegWordCnt, R, N);
	util::delete1dArray<int>(RegWordSum);
}
