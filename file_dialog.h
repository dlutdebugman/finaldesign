#pragma once

#include <QWidget>
#include <QFileInfoList>
#include <QTextEdit>

#include "ui_file_dialog.h"

class file_dialog : public QWidget
{
	Q_OBJECT

public:
	file_dialog(QWidget *parent = Q_NULLPTR);
	~file_dialog();
private:
	/*
	*@brief:��ʼ����������
	*/
	void init_data();
	/*
	*@brief:��ȡ�ļ�����
	*/
	QStringList GetFileList(QString path);
	void createAction();
	void contextMenuEvent(QContextMenuEvent * event);

private slots:
	/*
	*@brief:��ʾ����������ļ�����
    */
	void show_click_data();
	void getClickItem(QListWidgetItem *item);
	void deleteItem();
	void update_data();
	void on_pushButton_data_clicked();
private:
	QTextEdit *m_textEdit;
	QAction   *m_openAction;
	QAction   *m_deleteAction;
	QListWidgetItem *m_item;
private:
	int m_file_size;
private:
	Ui::file_dialog ui;
};
