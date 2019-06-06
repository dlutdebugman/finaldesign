#include "modelrun.h"
#include "qdebug.h"
#if 1
#include <string>
#include <iostream>
#include <cstdlib>
#include "Date.h"
#include "LRT.h"
#include "Detector.h"
#include "public.h"
#include "component/messageBox.h"

using namespace std;
model *ms;
#endif

std::string root(DATA_PATH);
std::string feature(POI_PATH);
std::string words(WORDS_PATH);
std::string output(OUTPUT);

ModelRun::ModelRun(QObject *parent)
	: QObject(parent)
{
	ms = new model(root, feature, words);
}

ModelRun::~ModelRun()
{

}
void ModelRun::selectModel()
{
# if 1
	//1.init
	
	m_argc_num = 5;

	char **argv;
	
	ms->init(m_argc_num, argv);     //创建数组并进行初始化
	ms->run();                //开始吉布斯采样和L-BFGS
	ms->output(root + output);
	delete ms;
	qDebug("step one finished");
#endif
	emit init_end();
}


model *ModelRun::getModel()
{
	return ms;
}