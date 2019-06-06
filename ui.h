#ifndef UI_H
#define UI_H

#pragma once
#define WIDTH  1120
#define HEIGHT 720

#include <QtWidgets/QMainWindow>
#include "Component\basewindow.h"
#include <QListWidget>
#include <QStackedWidget>
#include "Component/login.h"

class UI : public BaseWindow
{
	Q_OBJECT
public:
	UI(QWidget *parent = Q_NULLPTR);
public:
	void intw();
	void CreateIcons();
private slots:
	void ChangePage(QListWidgetItem * current, QListWidgetItem * previous);
	void show_main_window();
private:
private:
	login *m_login;
private:
	QListWidget *m_toolMenu;
	QStackedWidget *m_stackedWidget;
};


#endif // UI_H
