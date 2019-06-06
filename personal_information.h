#pragma once

#include <QWidget>
#include <QSettings>

#include "ui_personal_information.h"

class personal_information : public QWidget
{
	Q_OBJECT

public:
	personal_information(QWidget *parent = Q_NULLPTR);
	~personal_information();
private slots:
	void saveSetting();
	void readSetting();
private:
	Ui::personal_information ui;
};
