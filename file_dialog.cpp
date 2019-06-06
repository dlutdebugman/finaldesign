#include "file_dialog.h"
#include "public.h"
#include <QDir>
#include <QListWidget>
#include <QVector>
#include <QFile>
#include <QListWidgetItem>
#include <QMenu>
#include "component/messageBox.h"

file_dialog::file_dialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_file_size = -1;
	connect(ui.listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(getClickItem(QListWidgetItem*)));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(update_data()));
	
	init_data();
	createAction();
	
}

file_dialog::~file_dialog()
{
	if (m_textEdit != NULL)
	{
		delete m_textEdit;
		m_textEdit = NULL;
	}
}

void file_dialog::init_data()
{
	ui.listWidget->setFocusPolicy(Qt::NoFocus);
	ui.listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	ui.listWidget->setStyleSheet("QScrollBar:vertical{width: 40px;}");
	ui.listWidget->setStyleSheet(
		"QListWidget{border:1px solid gray; color:black; }"
		"QListWidget::Item{border-width: 3px;border-style: solid;border-bottom-color: rgb(153, 153, 153);}"
		"QListWidget::Item{background-color:rgb(255,255,255)}"
		"QListWidget::Item{padding-top:20px; padding-bottom:4px; }"
		"QListWidget::Item:hover{background:skyblue; }"
		"QListWidget::item:selected:!active{border-width:2px; background-color:rgb(234,234,235); }"
	);
	QStringList file_list = GetFileList(QString(FILE_PATH));
	for (int i = 0; i < file_list.size(); ++i)
	{
		ui.listWidget->addItem(file_list.at(i));
	}
	m_textEdit = new QTextEdit;

	m_file_size = file_list.size();
}
QStringList file_dialog::GetFileList(QString pathsDir)
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

void file_dialog::createAction()
{
	m_openAction = new QAction(QStringLiteral("查看文件"), this);
	m_deleteAction = new QAction(QStringLiteral("删除"), this);
	connect(m_openAction, SIGNAL(triggered()), this, SLOT(show_click_data()));
	connect(m_deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));
}

void file_dialog::show_click_data( )
{
		m_textEdit->clear();
		QString fileName = m_item->text();
		QFile file(FILE_PATH + fileName);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return;
		QString allData;
		while (!file.atEnd()) {
			QByteArray line = file.readLine();
			allData.append(line);
			allData.append("\n\r");
		}
		m_textEdit->setWindowTitle(QStringLiteral("数据查看"));
		m_textEdit->setText(allData);
		m_textEdit->resize(600, 600);
		m_textEdit->show();
}
void file_dialog::contextMenuEvent(QContextMenuEvent * event)
{
	QMenu* popMenu = new QMenu(this);
	popMenu->addAction(m_openAction);
	popMenu->addAction(m_deleteAction);

	if (ui.listWidget->itemAt(mapFromGlobal(QCursor::pos())) != NULL) //如果有item则添加"修改"菜单 [1]*
	{
		//popMenu->addAction(new QAction(QStringLiteral("修改"), this));
	}

	popMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
}

void file_dialog::deleteItem()
{
	ui.listWidget->takeItem(ui.listWidget->currentRow());
}

void file_dialog::getClickItem(QListWidgetItem * item)
{
	m_item = item;
}
void file_dialog::update_data()
{
	if (m_file_size > 0)
	{
		//for (int i = 1; i <= m_file_size; ++i)
		//{
			ui.listWidget->clear();
			update();
		//}
#if 1
		QStringList file_list = GetFileList(QString(FILE_PATH));
		for (int i = 0; i < file_list.size(); ++i)
		{
			ui.listWidget->addItem(file_list.at(i));
		}
#endif
	}

}
void file_dialog::on_pushButton_data_clicked()
{
	MyMessageBox::showMyMessageBox(this, QStringLiteral("友情提醒"), QStringLiteral("弹出数据处理完成!"), MESSAGE_WARNNING, BUTTON_OK, true);
}