/*****************************************************************
* brief：实现提示对话框
******************************************************************/

#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QWidget>
#include "ui_messagebox.h"
#include "basewindow.h"
#include "publicenum.h"

class MyMessageBox : public BaseWindow
{
	Q_OBJECT

public:
	MyMessageBox(QWidget *parent = 0);
	~MyMessageBox();

	void setWindowTitle(QString title, int titleFontSize = 10);
	void setContentText(QString contentText);
	void setMessageType(MessageType messageType);
	void setButtonType(MessageButtonType buttonType);
	void setMessageContent(QString messageContent);

public:
	int static showMyMessageBox(QWidget* parent, const QString &title,const QString &contentText , MessageType messageType, MessageButtonType messageButtonType , bool isModelWindow = false);

private:
	void initWindow();
	void initTitleBar();
	int exec();

	void paintEvent(QPaintEvent *event);
	void closeEvent(QCloseEvent *event);

private slots:
	void onOkClicked();
	void onCancelClicked();

private:
	Ui::MyMessageBox ui;
	QEventLoop* m_eventLoop;
	ChosseResult m_chooseResult;
};
#endif // MYMESSAGEBOX_H
