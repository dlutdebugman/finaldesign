#include "stdafx.h"
#include "model.h"
#include "data.h"
#include <QDebug>

using namespace std;
using namespace dlib;

extern model* m;

//用lambda得到区域中的alphas 
bool getExpAlphas(const column_vector& lambda)
{
	data* d = m->d;
	//计算expAlpha
	for (int r = 0; r < d->R; ++r)
	{
		m->alphaSum[r] = 0;
		for (int t = 0; t < m->T; ++t)
		{
			double x = 0;
			for (int f = 0; f < d->F; ++f)
			{
				x += d->RegFeature[r][f] * lambda(t*d->F + f);
			}
			m->alpha[r][t] = exp(x);
			if (!isfinite(m->alpha[r][t]))
			{
				return false;
			}
			m->alphaSum[r] += m->alpha[r][t];
		}
	}
	return true;
}

//L-BFGS的lambda和z的联合可能性
double likelihood(const column_vector& lambda)
{
	data* d = m->d;
	double ret = 0;
	//TODO: need to be fixed
	/*if (!getExpAlphas(lambda))
	return -1000000;

	bool flag = getExpAlphas(lambda);
	_ASSERT(flag);*/

	for (int r = 0; r < d->R; ++r)
	{
		ret += util::logGammaStirling(m->alphaSum[r]) - util::logGammaStirling(m->alphaSum[r] + d->RegWordSum[r]);
		for (int t = 0; t < m->T; ++t)
		{
			ret += util::logGammaStirling(m->alpha[r][t] + m->RegTopicCnt[r][t]) - util::logGammaStirling(m->alpha[r][t]);
		}
	}

	for (int t = 0; t < m->T; ++t)
	{
		for (int f = 0; f < d->F - 1; ++f)
		{
			ret -= (lambda(t*d->F + f) * lambda(t*d->F + f)) / (2 * m->variance * m->variance);
		}
		ret -= (lambda(t*d->F + d->F - 1) * lambda(t*d->F + d->F - 1)) / (2 * m->large_variance * m->large_variance);
	}
	//if (isnan(ret))
	//	return -1000000;
	return ret;
}

//联合可能性的导数用于L-BFGS
const column_vector likelihood_derivative(const column_vector& lambda)
{
	data* d = m->d;

	column_vector ret(m->T*d->F);

	//TODO: need to be fixed, why there will be 1.#QNAN
	/*if (!getExpAlphas(lambda))
	{
	for (int t = 0; t < m->T; ++t)
	for (int f = 0; f < d->F; ++f)
	{
	ret(t*d->F + f) = 0;
	}
	return ret;
	}
	bool flag = getExpAlphas(lambda);
	_ASSERT(flag);*/

	for (int t = 0; t < m->T; ++t)
		for (int f = 0; f < d->F; ++f)
		{
			double x = 0;
			if (f == d->F - 1)
				x = -lambda(t*d->F + f) / (m->large_variance*m->large_variance);
			else
				x = -lambda(t*d->F + f) / (m->variance*m->variance);

			for (int r = 0; r < d->R; ++r)
			{
				double temp = 0;
				temp += util::digamma(m->alphaSum[r]);
				temp -= util::digamma(m->alphaSum[r] + d->RegWordSum[r]);
				temp += util::digamma(m->alpha[r][t] + m->RegTopicCnt[r][t]);
				temp -= util::digamma(m->alpha[r][t]);
				x += temp*(d->RegFeature[r][t])*(m->alpha[r][t]);
			}

			ret(t*d->F + f) = x;
		}

	return ret;
}

model::model()
{
	d = new data();
}

model::model(string root, string fFile, string wFile) : root(root)
{
	d = new data(root + fFile, root + wFile);
}

model::~model()
{
	util::delete2dArray<double>(alpha, d->R);
	util::delete1dArray<double>(alphaSum);

	util::delete1dArray<double>(betaSum);
	util::delete2dArray<int>(RegTopicCnt, d->R);
	util::delete3dArray<int>(TopicWordCnt, d->N, T);
	util::delete2dArray<int>(TopicWordSum, d->N);
	util::delete1dArray<double>(p);

	util::delete3dArray<double>(phi, d->N, T);
	util::delete3dArray<double>(yita, d->R, d->N);

	//删除主题分配
	if (!TopicAssignment)
		return;
	for (int r = 0; r < d->R; ++r)
	{
		for (int n = 0; n < d->N; ++n)
		{
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				delete[] TopicAssignment[r][n][w];
				TopicAssignment[r][n][w] = NULL;
			}
			delete[] TopicAssignment[r][n];
			TopicAssignment[r][n] = NULL;
		}
		delete[] TopicAssignment[r];
		TopicAssignment[r] = NULL;
	}
	delete[] TopicAssignment;
	TopicAssignment = NULL;
	//结束删除主题分配

	delete d;
}

/*void model::parse_arg(int argc, char** argv)
{
int i = 2; //首先是数据的后缀
while (i < argc)
{
string arg = argv[i];
if (arg == "-useBFGS")
{
useBFGS = ((int)atof(argv[++i]));
}
else if (arg == "-variance")
{
variance = atof(argv[++i]);
}
else if (arg == "-large_variance")
{
large_variance = atof(argv[++i]);
}
else if (arg == "-optinterval")
{
optimizeInterval = (int)atof(argv[++i]);
}
else if (arg == "-inita")
{
initialAlpha = atof(argv[++i]);
}
else if (arg == "-beta")
{
beta = atof(argv[++i]);
}
else if (arg == "-maxIter")
{
maxIter = (int)atof(argv[++i]);
}
else if (arg == "-topic")
{
T = (int)atof(argv[++i]);
}
else if (arg == "-verbose")
{
verbose = true;
}
else
{
_ASSERT(false);
}
i++;
}
}*/

void model::init(int argc, char** argv)
{
	//parse_arg(argc, argv); 剥夺位置

	//输出参数
	printf("useBFGS\t %d \n", useBFGS);
	printf("variance\t %lf \n", variance);
	printf("large_variance\t %lf \n", large_variance);
	printf("initialAlpha\t %lf \n", initialAlpha);
	printf("beta\t %lf \n", beta);
	printf("T\t %d \n", T);
	printf("maxIter\t %d \n", maxIter);
	printf("optimizeInterval\t %d \n", optimizeInterval);
	printf("\n\n");
	//设置lambda 主题数*特征维度
	lambda = column_vector(T*d->F);
	for (int i = 0; i < T*d->F; ++i)
		lambda(i) = (std::rand() - RAND_MAX) * 0.01 / RAND_MAX;
	util::create2dArray<double>(alpha, d->R, T);   //每个区域的alpha
	util::create1dArray<double>(alphaSum, d->R);   //每个地区的alpha总数
	//模型数据
	util::create1dArray<double>(betaSum, d->N);    //每个单词集的beta总数
	util::create2dArray<int**>(TopicAssignment, d->R, d->N);//主题分配
	util::create2dArray<int>(RegTopicCnt, d->R, T); //区域中每个主题的数量
	util::create2dArray<int*>(TopicWordCnt, d->N, T);//区域中每个主题中单词的数量
	util::create2dArray<int>(TopicWordSum, d->N, T);//主题中单词的总数
	util::create1dArray<double>(p, T);//存储每个主题的概率

	util::create2dArray<double*>(phi, d->N, T);//phi
	util::create2dArray<double*>(yita, d->R, d->N);//区域中单词的比例

	lambdaChanged = false;

	//每个区域每个单词集中单词的数量
	for (int r = 0; r < d->R; ++r)
		for (int n = 0; n < d->N; ++n)
		{
			TopicAssignment[r][n] = new int*[d->SetWordCnt[n]];
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
				TopicAssignment[r][n][w] = new int[d->RegWordCnt[r][n][w]];
		}
	//每个单词集中每个主题中单词的数量
	for (int n = 0; n < d->N; ++n)
		for (int t = 0; t < T; ++t)
		{
			TopicWordCnt[n][t] = new int[d->SetWordCnt[n]];
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				TopicWordCnt[n][t][w] = 0;
			}
		}
	//phi
	for (int n = 0; n < d->N; ++n)
		for (int t = 0; t < T; ++t)
		{
			phi[n][t] = new double[d->SetWordCnt[n]];
		}
	//yita
	for (int r = 0; r < d->R; ++r)
		for (int n = 0; n < d->N; ++n)
		{
			yita[r][n] = new double[d->SetWordCnt[n]];
		}
	//alpha
	for (int r = 0; r < d->R; ++r)
	{
		for (int t = 0; t < T; ++t)
		{
			alpha[r][t] = initialAlpha;
		}
		alphaSum[r] = initialAlpha * T;
	}

	//beta
	for (int n = 0; n < d->N; ++n)
	{
		betaSum[n] = d->SetWordCnt[n] * beta;
	}

	//随机给每个单词挑选主题

	for (int r = 0; r < d->R; ++r)
		for (int n = 0; n < d->N; ++n)
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
				for (int i = 0; i < d->RegWordCnt[r][n][w]; ++i)
				{
					int t = std::rand() % T;
					TopicAssignment[r][n][w][i] = t;
					RegTopicCnt[r][t]++;
					TopicWordCnt[n][t][w]++;
					TopicWordSum[n][t]++;
				}

	//随机设置lambda
	/*	for (int t = 0; t < T; ++t)
	for (int f = 0; f < d->F; ++f)
	{
	lambda(t*d->F+f) = 1;
	}*/
}
#include <windows.h>
void model::run()
{
	srand(time(0));
	evaluate(false); //评估
	for (int iter = 0; iter < maxIter; ++iter)
	{
		if (verbose)
			qDebug( "gibbs: %d\n", iter);
		print_data.clear();
		print_data = QString("gibbs:%1").arg(iter);

		Sleep(1);

		//每个单词的样本
		for (int r = 0; r < d->R; ++r)
			for (int n = 0; n < d->N; ++n)
				for (int w = 0; w < d->SetWordCnt[n]; ++w)
					for (int i = 0; i < d->RegWordCnt[r][n][w]; ++i)
					{
						int oldT = TopicAssignment[r][n][w][i];
						_ASSERT(RegTopicCnt[r][oldT] > 0); //使用VS assert来避免检查发布版本
						RegTopicCnt[r][oldT]--;
						_ASSERT(TopicWordCnt[n][oldT][w] > 0);
						TopicWordCnt[n][oldT][w]--;
						_ASSERT(TopicWordSum[n][oldT] > 0);
						TopicWordSum[n][oldT]--;

						for (int t = 0; t < T; ++t)
						{
							p[t] = (alpha[r][t] + RegTopicCnt[r][t]) * (beta + TopicWordCnt[n][t][w]) / (betaSum[n] + TopicWordSum[n][t]);
						}
						for (int t = 1; t < T; ++t)
						{
							p[t] += p[t - 1];
						}
						double sample = (std::rand()*1.0 / RAND_MAX)*p[T - 1];  //采样

						int newT;
						for (newT = 0; newT < T; ++newT)
						{
							if (p[newT] >= sample)
								break;
						}

						TopicAssignment[r][n][w][i] = newT;
						RegTopicCnt[r][newT]++;
						TopicWordCnt[n][newT][w]++;
						TopicWordSum[n][newT]++;
					}

		//L-BFGS优化算法
		if (useBFGS && ((iter > burnIn && iter % optimizeInterval == 0) || iter == maxIter - 1))
		{
			qDebug("L-BFGS at iteration %d\n", iter);
			print_data.clear();
			print_data = QString("L-BFGS at iteration:%1").arg(iter);

			find_max(bfgs_search_strategy(), objective_delta_stop_strategy(1e-7).be_verbose(), likelihood, likelihood_derivative, lambda, 1e7);
			find_max_using_approximate_derivatives(bfgs_search_strategy(), objective_delta_stop_strategy(1e-7).be_verbose(), likelihood, lambda, 1e7);
			find_max(cg_search_strategy(), objective_delta_stop_strategy(1e-7).be_verbose(), likelihood, likelihood_derivative, lambda, 1e7);
			std::cout << lambda;
			qDebug("L-BFGS done\n");
			print_data.clear();
			print_data = QString("L-BFGS done");
			getExpAlphas(lambda);
		}

		//评估
		if (((iter > burnIn && iter % evalInterval == 0) || iter == maxIter - 1))
		{
			evaluate();
		}
	}
	//std::cout << likelihood(lambda) << std::endl;
	qDebug() << likelihood(lambda) << endl;
}
QString model::getPrintfInfo()
{
	return print_data;
}
void model::getOutput(bool getExpAlphaFirst)
{
	if (getExpAlphaFirst)
		getExpAlphas(lambda);

	//首先计算phi
	for (int n = 0; n < d->N; ++n)
		for (int t = 0; t < T; ++t)
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				phi[n][t][w] = ((TopicWordCnt[n][t][w] + 1) * 1.0 / (TopicWordSum[n][t] + d->SetWordCnt[n]));
			}

	//计算每个区域中每个单词集中单词的比例
	for (int r = 0; r < d->R; ++r)
		for (int n = 0; n < d->N; ++n)
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				double x = 0;
				for (int t = 0; t < T; ++t)
				{
					x += ((alpha[r][t] / alphaSum[r]) * phi[n][t][w]);
				}
				yita[r][n][w] = x;
			}

	outputGot = true;
}

void model::evaluate(bool getExpAlphaFirst)
{
	getOutput(getExpAlphaFirst);
	int* eval_cnt = new int[d->N]();
	double* err = new double[d->N]();
	int eval_cnt_all = 0;
	double err_all = 0;
	for (int r = 0; r < d->R; ++r)
	{
		for (int n = 0; n < d->N; ++n)
		{
			int cnt = 0;
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				cnt += d->RegWordCnt[r][n][w];
			}
			if (cnt > 50)
			{
				eval_cnt[n]++;
				if (n >= d->N - 12)
					eval_cnt_all++;
				for (int w = 0; w < d->SetWordCnt[n]; ++w)
				{
					double tmp = std::pow(((d->RegWordCnt[r][n][w] * 1.0) / (cnt)-yita[r][n][w]), 2);
					err[n] += tmp;
					if (n >= d->N - 12)
						err_all += tmp;
				}
			}
		}
	}

	for (int n = 0; n < d->N; ++n)
	{
		err[n] = std::sqrt(err[n] / eval_cnt[n]);
		printf("wordset的平方误差 %d: %lf\n", n, err[n]);
	}

	printf("wordset all的平方误差: %lf\n", std::sqrt(err_all / eval_cnt_all));
	printf("\n");

	delete err;
	delete eval_cnt;
}

void model::output(string yitaFile)
{
	getOutput();
	FILE* fout;
	errno_t err;
	bool error;

	err = fopen_s(&fout, yitaFile.c_str(), "w");
	for (int n = 0; n < d->N; ++n)
	{
		fprintf_s(fout, "%d %d\n", d->SetDaySec[n], d->SetCate[n]);
	}
	for (int r = 0; r < d->R; ++r)
	{
		for (int n = 0; n < d->N; ++n)
		{
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				fprintf_s(fout, "%lf ", yita[r][n][w]);
				//cout << yita[r][0][0];
			}
			fprintf_s(fout, "\n");
		}
	}
	fclose(fout);
}

void model::writeLambda(string lambdaIn, string lambdaOut)
{
	getOutput();
	FILE* fin;
	FILE* fout;
	errno_t err;
	bool error;

	//写结果
	err = fopen_s(&fin, lambdaIn.c_str(), "r");
	err = fopen_s(&fout, lambdaOut.c_str(), "w");
	fprintf_s(fout, "%d\n", d->R);

	int* detect = new int[d->N]();
	int* slot = new int[d->N]();
	int* cate = new int[d->N]();

	int detectNum = 0;

	for (int n = 0; n < d->N; ++n)
	{
		fscanf_s(fin, "%d%d%d", &slot[n], &cate[n], &detect[n]);
		if (detect[n])
		{
			detect[n] = true;
			detectNum++;
		}
	}

	/*	首先写入检测号码，然后写入每个slot和cate
	*	这将使异常值检测的输入更容易
	*/
	fprintf_s(fout, "%d\n", detectNum);

	for (int n = 0; n < d->N; ++n)
	{
		if (detect[n])
		{
			fprintf_s(fout, "%d %d\n", slot[n], cate[n]);
		}
	}

	for (int r = 0; r < d->R; ++r)
	{
		for (int n = 0; n < d->N; ++n)
		{
			double x;
			fscanf_s(fin, "%lf", &x);
			for (int w = 0; w < d->SetWordCnt[n]; ++w)
			{
				if (detect[n])
					fprintf_s(fout, "%lf ", x * yita[r][n][w]);
			}
			if (detect[n])
				fprintf_s(fout, "\n");
		}
		fprintf_s(fout, "\n");
	}

	delete[] detect;
	delete[] slot;
	delete[] cate;
	fclose(fin);
	fclose(fout);
}

void model::test()
{
	for (int i = 0; i < 10; ++i)
		printf("%d\n", std::rand());
}
