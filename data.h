#pragma once
#include <string>

class data
{
public:

	int R; //地区数量
	int F; //特征维度
	int N; //单词集数量

	double** RegFeature; //每个区域的特征, 索引由 <region number r, feature index f>
	int* SetDaySec; //数据处理器中的时隙, 索引由<单词集索引n>
	int* SetCate; //数据处理器中的种类,索引由<单词集索引n>
	int* SetWordCnt; //每个单词集中不同单词的数量，索引由<单词集索引n>
	int*** RegWordCnt; //区域中每个单词的数量, 索引由 <region index r, word set index n, word index w>
	int* RegWordSum; //区域的总单词数, 索引由 <region index r>

	data();

	data(std::string fFile, std::string wFile); //特征文件和单词文件

	~data();
};

