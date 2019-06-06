#pragma once

#include <QWidget>
#include <QThread>
#include <qtimer.h>
#include "ui_detection.h"
#include "modelrun.h"

#include <QTimer>
#include <QDir>
#include <QListWidget>
#include "public.h"
class detection : public QWidget
{
	Q_OBJECT

public:
	detection(QWidget *parent = Q_NULLPTR);
	~detection();
private slots:
	//2.like
	void likelihood();
	//3.region
	void region();
	void printf_ouput_info();
	bool  get_init_state();
	void show_image1();
private:
	ModelRun *m_selsect_model;
	QThread  m_model_thread;
	QTimer   *m_timer;
	QStringList GetFileList1(QString pathsDir);

	QStringList m_image_path1;
	/*
	*@brief:图片文件个数
	*/
	int         m_image_num1;
	int         m_current_index1;
private:
	Ui::detection ui;
};
