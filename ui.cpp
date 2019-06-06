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
* @brief: 初始化相关参数
* @param: void
* @return: void
*/
void UI::intw()
{
	m_titleBar->setTitleIcon(":Resources/log.png");
	m_titleBar->setTitleContent(QStringLiteral("城市异常检测系统"), 15);
	m_titleBar->setButtonType(MIN_BUTTON);
	m_titleBar->setTitleWidth(this->width());

	this->setFixedSize(WIDTH, HEIGHT);

	/*************************设置菜单栏**************************************/
	m_toolMenu = new QListWidget;
	m_toolMenu->setStyleSheet("background-color : rgba(255,255,255,0);"
		"border-width: 3px;"
		"border-style: solid;"
		"border-top-color: rgba(153, 153, 153,0);"
		"border-left-color:rgba(153, 153, 153,0);"
		"border-right-color:rgba(153, 153, 153,0);");
	m_toolMenu->setViewMode(QListView::IconMode);
	m_toolMenu->setIconSize(QSize(500, 48));//设置图标大小
	m_toolMenu->setMovement(QListView::Static);
	m_toolMenu->setMaximumWidth(this->width());//设置宽度和窗口宽度
	m_toolMenu->setMinimumHeight(80);//设置最小高度
	m_toolMenu->setMaximumHeight(100);//设置最大像素高
	m_toolMenu->setWrapping(false);//禁止换行	
	
	m_toolMenu->setFlow(QListView::LeftToRight);
	
	/*************************设置页面**************************************/
	m_stackedWidget = new QStackedWidget;
	/*!
	*@[0]:查看文件
	*/
	m_stackedWidget->addWidget(new file_dialog);
	/*!
	*@[1]:异常检测
	*/
	m_stackedWidget->addWidget(new detection);
	/*!
	*@[2]:图片展示
	*/
	m_stackedWidget->addWidget(new image_show);

	m_stackedWidget->addWidget(new personal_information);

	/***************************设置布局**************************************/
	CreateIcons();
	m_toolMenu->setCurrentRow(0);

	QVBoxLayout *horizontalLayout = new QVBoxLayout;//水平放置两个控件（上下）
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
* @brief: 创建工具菜单栏
* @param: void
* @return: void
*/
void  UI::CreateIcons()
{
	QListWidgetItem *mainPageButton = new QListWidgetItem(m_toolMenu);
	mainPageButton->setIcon(QIcon(":/Resources/image/statistics.png"));
	mainPageButton->setText(QStringLiteral("查看文件"));
	mainPageButton->setTextAlignment(Qt::AlignHCenter);
	mainPageButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	mainPageButton->setSizeHint(QSize(245, 80));
	mainPageButton->setFont(QFont("Yahei", 15));

	QListWidgetItem *productHistroyButton = new QListWidgetItem(m_toolMenu);
	productHistroyButton->setIcon(QIcon(":/Resources/image/Analysis.png"));
	productHistroyButton->setText(QStringLiteral("区域异常检测"));
	productHistroyButton->setTextAlignment(Qt::AlignHCenter);
	productHistroyButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	productHistroyButton->setSizeHint(QSize(245, 80));
	productHistroyButton->setFont(QFont("Yahei", 15));


	QListWidgetItem *statisticsButton = new QListWidgetItem(m_toolMenu);
	statisticsButton->setIcon(QIcon(":/Resources/image/battery.png"));
	statisticsButton->setText(QStringLiteral("结果展示"));
	statisticsButton->setTextAlignment(Qt::AlignHCenter);
	statisticsButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	statisticsButton->setSizeHint(QSize(245, 80));
	statisticsButton->setFont(QFont("Yahei", 15));

	QListWidgetItem *person_page = new QListWidgetItem(m_toolMenu);
	person_page->setIcon(QIcon(":/Resources/image/Persona.png"));
	person_page->setText(QStringLiteral("个人主页"));
	person_page->setTextAlignment(Qt::AlignHCenter);
	person_page->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	person_page->setSizeHint(QSize(245, 80));
	person_page->setFont(QFont("Yahei", 15));

	connect(m_toolMenu,
		SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)),
		this, SLOT(ChangePage(QListWidgetItem*, QListWidgetItem*)));
}

/*!
* @brief: 跳转到指定的widget
* @param: [in] current widget当前索引 previous widget跳转索引
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
