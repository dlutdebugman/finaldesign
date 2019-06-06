#include "ui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UI w;
	w.hide();
	return a.exec();
}
