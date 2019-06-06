#include "personal_information.h"
#include "public.h"

QSettings NTPClientini("setting.ini", QSettings::IniFormat);

personal_information::personal_information(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	readSetting();
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(saveSetting()));
}

personal_information::~personal_information()
{
 
}
void personal_information::saveSetting()
{
	if (!ui.lineEdit_name->text().isEmpty())
	{
		NTPClientini.setValue("name", ui.lineEdit_name->text());
	}
	if (!ui.lineEdit_phone->text().isEmpty())
	{
		NTPClientini.setValue("phone", ui.lineEdit_phone->text());
	}
	if (!ui.lineEdit_school->text().isEmpty())
	{
		NTPClientini.setValue("school", ui.lineEdit_school->text());
	}
	if (!ui.lineEdit_professional->text().isEmpty())
	{
		NTPClientini.setValue("pro", ui.lineEdit_professional->text());
	}
}
void personal_information::readSetting()
{
	QString fcText = NTPClientini.value("name").toString();//[0]
	if (!fcText.isEmpty())
	{
		ui.lineEdit_name->setText(fcText);
	}
	QString pnText = NTPClientini.value("phone").toString();
	if (!pnText.isEmpty())
	{
		 
		ui.lineEdit_phone->setText(pnText);
	}
	QString mfText = NTPClientini.value("school").toString();
	if (!mfText.isEmpty())
	{ 
		ui.lineEdit_school->setText(mfText);
	}
	QString etText = NTPClientini.value("pro").toString();
	if (!fcText.isEmpty())
	{
		ui.lineEdit_professional->setText(etText);
	}
}