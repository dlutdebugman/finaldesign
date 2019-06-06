#pragma once
#include <string>

class data
{
public:

	int R; //��������
	int F; //����ά��
	int N; //���ʼ�����

	double** RegFeature; //ÿ�����������, ������ <region number r, feature index f>
	int* SetDaySec; //���ݴ������е�ʱ϶, ������<���ʼ�����n>
	int* SetCate; //���ݴ������е�����,������<���ʼ�����n>
	int* SetWordCnt; //ÿ�����ʼ��в�ͬ���ʵ�������������<���ʼ�����n>
	int*** RegWordCnt; //������ÿ�����ʵ�����, ������ <region index r, word set index n, word index w>
	int* RegWordSum; //������ܵ�����, ������ <region index r>

	data();

	data(std::string fFile, std::string wFile); //�����ļ��͵����ļ�

	~data();
};

