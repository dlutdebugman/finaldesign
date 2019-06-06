#pragma once

#include <QWidget>
#include <QTimer>
#include "ui_image_show.h"
#include <QDir>
#include <QListWidget>
#include "public.h"
class image_show : public QWidget
{
	Q_OBJECT

public:
	image_show(QWidget *parent = Q_NULLPTR);
	~image_show();
private:
	QStringList GetFileList(QString pathsDir);
private slots:
	void show_image();

private:
	/*
	*@brief:图片文件路径
	*/
	QStringList m_image_path;
	/*
	*@brief:图片文件个数
	*/
	int         m_image_num;
	int         m_current_index;

private:
	Ui::image_show ui;
};
