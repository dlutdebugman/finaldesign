#include "image_show.h"
#include <QDir>
#include <QListWidget>
#include "public.h"
image_show::image_show(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(show_image()));
	
	ui.label->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
	m_current_index = 0;
	m_image_path = GetFileList(IMAGE_PATH);
	m_image_num = m_image_path.size();
	m_current_index = m_image_num;
	ui.label->setPixmap(QPixmap(IMAGE_PATH + m_image_path.at(m_current_index -1)));

	
}

image_show::~image_show()
{

}
QStringList image_show::GetFileList(QString pathsDir)
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

void image_show::show_image()
{
	if (m_current_index <= 0)
	{
		m_current_index = m_image_num;
	}
	m_current_index = m_current_index - 1;
	ui.label->setPixmap(QPixmap(IMAGE_PATH + m_image_path.at(m_current_index)));
	update();
}
