#include "ui.h"

#include "UI.h"
#include "file_dialog.h"
#include "image_show.h"
#include "detection.h"
#include "personal_information.h"

#include <QVBoxLayout>


UI::UI(QWidget *parent)
	: BaseWindow(parent)
{
	intw();
}
/*!
* @brief: ��ʼ����ز���
* @param: void
* @return: void
*/
void UI::intw()
{
	m_titleBar->setTitleIcon(":Resources/log.png");
	m_titleBar->setTitleContent(QStringLiteral("�����쳣���ϵͳ"), 15);
	m_titleBar->setButtonType(MIN_BUTTON);
	m_titleBar->setTitleWidth(this->width());

	this->setFixedSize(WIDTH, HEIGHT);

	/*************************���ò˵���**************************************/
	m_toolMenu = new QListWidget;
	m_toolMenu->setStyleSheet("background-color : rgba(255,255,255,0);"
		"border-width: 3px;"
		"border-style: solid;"
		"border-top-color: rgba(153, 153, 153,0);"
		"border-left-color:rgba(153, 153, 153,0);"
		"border-right-color:rgba(153, 153, 153,0);");
	m_toolMenu->setViewMode(QListView::IconMode);
	m_toolMenu->setIconSize(QSize(500, 48));//����ͼ���С
	m_toolMenu->setMovement(QListView::Static);
	m_toolMenu->setMaximumWidth(this->width());//���ÿ�Ⱥʹ��ڿ��
	m_toolMenu->setMinimumHeight(80);//������С�߶�
	m_toolMenu->setMaximumHeight(100);//����������ظ�
	m_toolMenu->setWrapping(false);//��ֹ����	
	
	m_toolMenu->setFlow(QListView::LeftToRight);
	
	/*************************����ҳ��**************************************/
	m_stackedWidget = new QStackedWidget;
	/*!
	*@[0]:�鿴�ļ�
	*/
	m_stackedWidget->addWidget(new file_dialog);
	/*!
	*@[1]:�쳣���
	*/
	m_stackedWidget->addWidget(new detection);
	/*!
	*@[2]:ͼƬչʾ
	*/
	m_stackedWidget->addWidget(new image_show);

	m_stackedWidget->addWidget(new personal_information);

	/***************************���ò���**************************************/
	CreateIcons();
	m_toolMenu->setCurrentRow(0);

	QVBoxLayout *horizontalLayout = new QVBoxLayout;//ˮƽ���������ؼ������£�
	horizontalLayout->addWidget(m_toolMenu, Qt::AlignCenter);
	horizontalLayout->setContentsMargins(40, 40, 0, 0);
	horizontalLayout->addWidget(m_stackedWidget, Qt::AlignBottom);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(horizontalLayout);
	setLayout(mainLayout);
	m_login = new login();
	m_login->show();
	connect(m_login, &login::login_account, this, &UI::show_main_window);
}
/*!
* @brief: �������߲˵���
* @param: void
* @return: void
*/
void  UI::CreateIcons()
{
	QListWidgetItem *mainPageButton = new QListWidgetItem(m_toolMenu);
	mainPageButton->setIcon(QIcon(":/Resources/image/statistics.png"));
	mainPageButton->setText(QStringLiteral("�鿴�ļ�"));
	mainPageButton->setTextAlignment(Qt::AlignHCenter);
	mainPageButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	mainPageButton->setSizeHint(QSize(245, 80));
	mainPageButton->setFont(QFont("Yahei", 15));

	QListWidgetItem *productHistroyButton = new QListWidgetItem(m_toolMenu);
	productHistroyButton->setIcon(QIcon(":/Resources/image/Analysis.png"));
	productHistroyButton->setText(QStringLiteral("�����쳣���"));
	productHistroyButton->setTextAlignment(Qt::AlignHCenter);
	productHistroyButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	productHistroyButton->setSizeHint(QSize(245, 80));
	productHistroyButton->setFont(QFont("Yahei", 15));


	QListWidgetItem *statisticsButton = new QListWidgetItem(m_toolMenu);
	statisticsButton->setIcon(QIcon(":/Resources/image/battery.png"));
	statisticsButton->setText(QStringLiteral("���չʾ"));
	statisticsButton->setTextAlignment(Qt::AlignHCenter);
	statisticsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	statisticsButton->setSizeHint(QSize(245, 80));
	statisticsButton->setFont(QFont("Yahei", 15));

	QListWidgetItem *person_page = new QListWidgetItem(m_toolMenu);
	person_page->setIcon(QIcon(":/Resources/image/Persona.png"));
	person_page->setText(QStringLiteral("������ҳ"));
	person_page->setTextAlignment(Qt::AlignHCenter);
	person_page->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	person_page->setSizeHint(QSize(245, 80));
	person_page->setFont(QFont("Yahei", 15));

	connect(m_toolMenu,
		SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
		this, SLOT(ChangePage(QListWidgetItem*, QListWidgetItem*)));
}

/*!
* @brief: ��ת��ָ����widget
* @param: [in] current widget��ǰ���� previous widget��ת����
* @return: void
*/
void UI::ChangePage(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (!current)
		current = previous;
	m_stackedWidget->setCurrentIndex(m_toolMenu->row(current));
}
void UI::show_main_window()
{
	this->show();
	m_login->setAttribute(Qt::WA_DeleteOnClose);
}
