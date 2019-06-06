#ifndef MODELRUN_H
#define MODELRUN_H

#include <QObject>
#include "model.h"
class ModelRun : public QObject
{
	Q_OBJECT

public:
	ModelRun(QObject *parent = 0);
	~ModelRun();
private slots:
	//1.init
	void selectModel();
public:
	model *getModel();

private:
	int m_argc_num;
signals:
	void init_end();
private:
	
};

#endif // MODELRUN_H
