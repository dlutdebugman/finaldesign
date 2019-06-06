#include "stdafx.h"
#include "data.h"

using namespace std;

data::data()
{
	printf("���ṩfeature�ļ���word�ļ�");
}

data::data(string fFile, string wFile)
{
	FILE* fin;
	errno_t err;
	bool error;

	//��feature�ļ�
	err = fopen_s(&fin, fFile.c_str(), "r");
	util::TopicAssert(err == 0, "���ܴ�feature�ļ� " + fFile);

	error = false;
	//printf("%d", fscanf_s(fin, "%d", &R));
	error = error || (fscanf_s(fin, "%d", &R) != 1);
	error = error || (fscanf_s(fin, "%d", &F) != 1);
	F++;
	//����������������
	util::create2dArray<double>(RegFeature, R, F);
	for (int r = 0; r < R; ++r)
	{
		for (int f = 0; f < F - 1; ++f)
		{
			error = error || (fscanf_s(fin, "%lf", &RegFeature[r][f]) != 1);
		}
		RegFeature[r][F - 1] = 1;
	}
	util::TopicAssert(error == false, "feature�ļ���ʽ����");
	fclose(fin);


	//��word�ļ�
	err = fopen_s(&fin, wFile.c_str(), "r");
	util::TopicAssert(err == 0, "���ܴ�word�ļ� " + wFile);

	error = false;
	//�ж�word�ļ���feature�ļ��еĵ��������Ƿ����
	int tempR;
	error = error || (fscanf_s(fin, "%d", &tempR) != 1);
	util::TopicAssert(tempR == R, "word�ļ���feature�ļ��еĵ������������");
	//���㵥�ʼ��в�ͬ���ʵ�����
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

	//���������ÿ�����ʵ������������е��ʵ�����
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
