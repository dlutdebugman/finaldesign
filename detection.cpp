#include "detection.h"
#if 1

#include "model.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include "Date.h"
#include "LRT.h"
#include "Detector.h"
#include "public.h"
#include <QDebug>
#include "component/messageBox.h"

using namespace std;
int use[3] = { 1, 1, 1 };
model *m;
Detector *detector;
#endif

detection::detection(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_selsect_model = new ModelRun();
	m = m_selsect_model->getModel();

	m_selsect_model->moveToThread(&m_model_thread);
	connect(&m_model_thread, &QThread::finished, m_selsect_model, &QObject::deleteLater);
	m_model_thread.start();

	connect(m_selsect_model, SIGNAL(init_end()), this, SLOT(get_init_state()));
	connect(ui.select_m_button, SIGNAL(clicked()), m_selsect_model, SLOT(selectModel()));


	connect(ui.likelihood_button, SIGNAL(clicked()), this, SLOT(likelihood()));
	connect(ui.pushButton_region, SIGNAL(clicked()), this, SLOT(region()));

	m_timer = new QTimer();
	connect(m_timer, SIGNAL(timeout()), this, SLOT(printf_ouput_info()));
	m_timer->start(10);

	
	connect(ui.fresh_button, SIGNAL(clicked()), this, SLOT(show_image1()));

	ui.label_4->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
	m_current_index1 = 0;
	m_image_path1 = GetFileList1(IMAGE_PATH);
	m_image_num1 = m_image_path1.size();
	m_current_index1 = m_image_num1;
	ui.label_4->setPixmap(QPixmap(IMAGE_PATH + m_image_path1.at(m_current_index1 - 1)));
}



detection::~detection()
{
	m_model_thread.wait();
	m_model_thread.quit();
}

QStringList detection::GetFileList1(QString pathsDir)
{
	/*获取文件夹下的文件名称*/
	QDir dir(pathsDir);
	if (!dir.exists())
	{
		return QStringList("");
	}
	dir.setFilter(QDir::Files);
	QStringList allImageNameList = dir.entryList();
	if (allImageNameList.count() <= 0)
	{
		return QStringList("");
	}
	return allImageNameList;
}

void detection::show_image1()
{
	if (m_current_index1 <= 0)
	{
		m_current_index1 = m_image_num1;
	}
	m_current_index1 = m_current_index1 - 1;
	ui.label_4->setPixmap(QPixmap(IMAGE_PATH + m_image_path1.at(m_current_index1)));
	update();
}
//2.like
void detection::likelihood()
{
	std::string root(DATA_PATH);
	std::string feature(POI_PATH);
	std::string words(WORDS_PATH);
	std::string output(OUTPUT);
	std::string region_center_file(OUTPUT_1);

	Date* d = new Date(root + region_center_file);

	std::string lambdaTaxi(OUTPUT_2);
	std::string lambdaBike(OUTPUT_3);
	std::string lambdaFour(OUTPUT_4);
	std::string cntTaxi(OUTPUT_5);
	std::string cntBike(OUTPUT_6);
	std::string cntFour(OUTPUT_7);
	int regionRange = ui.regionRange->text().toInt();
	int beginTime   = ui.beginTime->text().toInt();
	int endTime     = ui.endTime->text().toInt();

	DataSource *ds;
	LRT* lrt;

	if (use[0])
	{
		ds = new DataSource(lambdaTaxi, cntTaxi, d->R, d->T, true);
		lrt = new NormConfidence(ds);
		//lrt = new Stupid(ds);
		d->addSource(lrt);
	}

	if (use[1])
	{
		ds = new DataSource(lambdaBike, cntBike, d->R, d->T, true);
		lrt = new NormConfidence(ds);
		//lrt = new Stupid(ds);
		d->addSource(lrt);
	}

	if (use[2])
	{
		ds = new DataSource(lambdaFour, cntFour, d->R, d->T);
		lrt = new ZipLRT(ds);
		d->addSource(lrt);
	}

	detector=  new CoolDetector(d, 0.70, 1, regionRange, beginTime, endTime);
	detector->detect();//第二步操作结束
	qDebug("step two finished");
	MyMessageBox::showMyMessageBox(this, QStringLiteral("友情提醒"), QStringLiteral("第二步操作结束!"), MESSAGE_WARNNING, BUTTON_OK, true);
	
}
//3.region
void  detection::region()
{
	if (detector != NULL)
	{
		detector->summary();//第三步操作结束
		delete detector;
		detector = NULL;
	}
	qDebug("step three finished");
	MyMessageBox::showMyMessageBox(this, QStringLiteral("友情提醒"), QStringLiteral("第三步操作结束!"), MESSAGE_WARNNING, BUTTON_OK, true);
}
void detection::printf_ouput_info()
{
	qDebug() << "void detection::printf_ouput_info()"<< m->getPrintfInfo();
	ui.output->setText(m->getPrintfInfo());
}

bool detection::get_init_state()
{
	MyMessageBox::showMyMessageBox(this, QStringLiteral("友情提醒"), QStringLiteral("第一步操作结束!"), MESSAGE_WARNNING, BUTTON_OK, true); return false;
}