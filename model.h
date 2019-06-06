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

	//预设参数
	bool useBFGS = true; //用DMR或者经典LDA
	double variance = 1.0; //\ lambda的方差，均值为0
	double large_variance = 1000.0; //移位特征\ lambda的方差
	double initialAlpha = 0.1; //第一轮的Alpha
	double beta = 0.1; //主题词的beta
	int T = 10; //主题数
	int maxIter = 2000; //最大迭代轮数
	int optimizeInterval = 100; //用于优化\ lambda的迭代间隔 
	int evalInterval = 100; //输出评估的迭代间隔
	int burnIn = 50; //燃烧期

	bool verbose = true; //输出是否迭代(to stderr)

	//参数
	column_vector lambda; // \lambda, <topic index t, feature index f> will be indexed by <t*F+f>    列向量
	double** alpha; //每个区域的alpha，初始设置为0.1, index by <region index r, topic index t>
	double* alphaSum; //每个地区的alpha总数, index by <region index r>

	//模型数据
	double* betaSum; //每个单词集的beta总数, index by <region index r>
	int**** TopicAssignment; //主题分配，index by <region index r, wordset index n, word index w, word i>
	int** RegTopicCnt; //区域中每个主题的数量，index by <region index r, topic index t>
	int*** TopicWordCnt; //区域中每个主题中单词数量，index by <wordset index n, topic index t, word index w>
	int** TopicWordSum; //主题中单词的总数，index by <wordset index n, topic index t>
	bool lambdaChanged; //优化lambda后设置为true
	double* p; //用于抽样，存储选择每个主题的概率, index by <topic index t>

	data* d; //数据输入

	//输出
	bool outputGot; //mark for having call getOutput()
	double*** phi; //index by <wordset index n, topic index t, word index w>
	double*** yita; //区域中词的比例, index by <region index r, wordset index n, word index w>

	model();
	~model();

	model(std::string root, std::string fFile, std::string wFile); //特征文件和单词文件
	void parse_arg(int argc, char** argv); //解析并设置args
	void init(int argc, char** argv); //创建数组并进行一些初始化

	//void getExpAlphas(const column_vector& lambda); //get region alphas using lambda
	//double likelihood(const column_vector& lambda); //joint-likelihood of \lambda and z, for L-BFGS
	//const column_vector likelihood_derivative(const column_vector& lambda); //derivative of joint-likelihood. for L-BFGS

	void run(); //开始吉布斯采样和L-BFGS

	void getOutput(bool = true); //计算phi和区域字比例
	void evaluate(bool = true); //评估结果，给出theta和phi，与真实的噪声分布进行比较

	void output(std::string yitaFile); //输出到文件
	void writeLambda(std::string lambdaIn, std::string lambdaOut); //输出计算的lambda（这里是Poisson分布的lambda）

	void test(); //

	void setIteration(int i)
	{
		maxIter = i;
	}
	QString getPrintfInfo();

private:
	QString  print_data;
};

