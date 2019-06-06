#pragma once
#include "stdafx.h"
#include <string>
#include <QString>

typedef dlib::matrix<double, 0, 1> column_vector;

class data;

class model 
{
public:

	std::string root;

	//Ԥ�����
	bool useBFGS = true; //��DMR���߾���LDA
	double variance = 1.0; //\ lambda�ķ����ֵΪ0
	double large_variance = 1000.0; //��λ����\ lambda�ķ���
	double initialAlpha = 0.1; //��һ�ֵ�Alpha
	double beta = 0.1; //����ʵ�beta
	int T = 10; //������
	int maxIter = 2000; //����������
	int optimizeInterval = 100; //�����Ż�\ lambda�ĵ������ 
	int evalInterval = 100; //��������ĵ������
	int burnIn = 50; //ȼ����

	bool verbose = true; //����Ƿ����(to stderr)

	//����
	column_vector lambda; // \lambda, <topic index t, feature index f> will be indexed by <t*F+f>    ������
	double** alpha; //ÿ�������alpha����ʼ����Ϊ0.1, index by <region index r, topic index t>
	double* alphaSum; //ÿ��������alpha����, index by <region index r>

	//ģ������
	double* betaSum; //ÿ�����ʼ���beta����, index by <region index r>
	int**** TopicAssignment; //������䣬index by <region index r, wordset index n, word index w, word i>
	int** RegTopicCnt; //������ÿ�������������index by <region index r, topic index t>
	int*** TopicWordCnt; //������ÿ�������е���������index by <wordset index n, topic index t, word index w>
	int** TopicWordSum; //�����е��ʵ�������index by <wordset index n, topic index t>
	bool lambdaChanged; //�Ż�lambda������Ϊtrue
	double* p; //���ڳ������洢ѡ��ÿ������ĸ���, index by <topic index t>

	data* d; //��������

	//���
	bool outputGot; //mark for having call getOutput()
	double*** phi; //index by <wordset index n, topic index t, word index w>
	double*** yita; //�����дʵı���, index by <region index r, wordset index n, word index w>

	model();
	~model();

	model(std::string root, std::string fFile, std::string wFile); //�����ļ��͵����ļ�
	void parse_arg(int argc, char** argv); //����������args
	void init(int argc, char** argv); //�������鲢����һЩ��ʼ��

	//void getExpAlphas(const column_vector& lambda); //get region alphas using lambda
	//double likelihood(const column_vector& lambda); //joint-likelihood of \lambda and z, for L-BFGS
	//const column_vector likelihood_derivative(const column_vector& lambda); //derivative of joint-likelihood. for L-BFGS

	void run(); //��ʼ����˹������L-BFGS

	void getOutput(bool = true); //����phi�������ֱ���
	void evaluate(bool = true); //�������������theta��phi������ʵ�������ֲ����бȽ�

	void output(std::string yitaFile); //������ļ�
	void writeLambda(std::string lambdaIn, std::string lambdaOut); //��������lambda��������Poisson�ֲ���lambda��

	void test(); //

	void setIteration(int i)
	{
		maxIter = i;
	}
	QString getPrintfInfo();

private:
	QString  print_data;
};

