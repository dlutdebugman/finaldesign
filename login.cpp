#include "login.h"
#include "ui_login.h"
#include <QMouseEvent>
#include <QMovie>
#include <qdesktopwidget.h>

#include "customicon.h"
#include "messageBox.h"
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
	max = false;
    setStyleSheet("background-color:white");
    ui->label_theme->setText(QStringLiteral("城市异常检测"));
    ui->label_id->setText(QStringLiteral("账号"));
    ui->lineEdit_pawssd->setEchoMode(QLineEdit::Password);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    QMovie *move = new QMovie(":/Resources/image/timg.gif");
    ui->move_label->setMovie(move);
    move->start();
    customIcon::Instance()->SetIcon(ui->pushButton_min, QChar(0xf068), 10);
    customIcon::Instance()->SetIcon(ui->pushButton_close, QChar(0xf00d), 10);

    ui->lineEdit_id->setPlaceholderText(QStringLiteral("账号,如:root"));
    ui->lineEdit_pawssd->setPlaceholderText(QStringLiteral("密码"));
    connect(ui->pushButton_close, SIGNAL(clicked()),this,SLOT(close()));
    m_search = new Search();

    //1.login info register
    m_register = new register_info();
    FormInCenter(m_register);
    m_register->set_account_text(QStringLiteral("账号"));
    m_register->set_password_text(QStringLiteral("密码"));
    m_register->set_check_name_text(QStringLiteral("救援码"));
    m_register->set_login_text(QStringLiteral("确定"));
	m_register->set_dialog_tip(QStringLiteral("账号注册"));
    connect(m_register, &register_info::send_account, this,&login::save_register_info);

    //2.retreive password
    m_retrieve_password = new register_info();
    FormInCenter(m_retrieve_password);
    m_retrieve_password->set_account_text(QStringLiteral("账号"));
    m_retrieve_password->set_password_text(QStringLiteral("救援码"));
    m_retrieve_password->set_check_hide();
    m_retrieve_password->set_login_text(QStringLiteral("确定"));
    connect(m_retrieve_password, &register_info::send_account, this,&login::set_name_check);
	m_retrieve_password->set_dialog_tip(QStringLiteral("密码找回"));

    //3.set password
    m_set_password = new register_info();
    FormInCenter(m_set_password);
    m_set_password->set_account_text(QStringLiteral("账号"));
    m_set_password->set_check_name_text(QStringLiteral("再次确认密码"));
    m_set_password->set_password_text(QStringLiteral("新密码"));
    //m_set_password->set_check_hide();
    m_set_password->set_login_text(QStringLiteral("确认"));
	m_set_password->set_dialog_tip(QStringLiteral("密码修改"));

    connect(m_set_password, &register_info::send_account, this,&login::set_update_password);
}

login::~login()
{
    delete ui;
}

void login::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton) && !max) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void login::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void login::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void login::FormInCenter(QWidget *frm)
{
    int frmX = frm->width();
    int frmY = frm->height();
    QDesktopWidget w;
    int deskWidth = w.width();
    int deskHeight = w.height();
    QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
    frm->move(movePoint);
}

void login::on_pushButton_min_clicked()
{
    this->showMinimized();
}

void login::on_pushButton_reg_clicked()
{
    m_register->show();
}

void login::save_register_info(QString id, QString password, QString check_name)
{
    QByteArray bytes ,bytes_1;
    char *_id, *_password;

    bytes = id.toLocal8Bit();
    _id = bytes.data();

     bytes_1 = password.toLocal8Bit();
    _password = bytes_1.data();

    m_search->storePlotData(_id, _password, check_name.toInt());
    m_register->close();
}

void login::on_pushButton_modif_password_clicked()
{
    m_retrieve_password->show();
}

void login::set_name_check(QString id, QString password, QString check_name)
{
    Q_UNUSED(check_name);
    bool isSearch = m_search->searchDatabyID(id,"login",true);
    login_info _Data;
    memset(&_Data, 0x00,sizeof(login_info));
    if(isSearch)
    {
        m_search->getData(&_Data);
        if(std::strcmp(password.toLatin1(), _Data.check_num) == 0)
        {
             m_retrieve_password->close();
             m_set_password->show();
        }
        else
        {
            MyMessageBox::showMyMessageBox(this, QStringLiteral("友情提醒"), QStringLiteral("没有检索到相关数据!"), MESSAGE_WARNNING, BUTTON_OK, true);
        }
    }
}

void login::set_update_password(QString id, QString password, QString check_name)
{
    QByteArray bytes ,bytes_1;
    char *_id, *_password;

    bytes = id.toLocal8Bit();
    _id = bytes.data();

     bytes_1 = password.toLocal8Bit();
    _password = bytes_1.data();

    if(password == check_name)
    {
         m_search->storePlotData(_id, _password, check_name.toInt());
		 m_set_password->close();
    }
    else
    {
        MyMessageBox::showMyMessageBox(this, QStringLiteral("友情提醒"), QStringLiteral("两次密码不一致，请重新输入!"), MESSAGE_WARNNING, BUTTON_OK, true);
    }
}

void login::on_pushButton_login_clicked()
{
    bool isSearch = m_search->searchDatabyID(ui->lineEdit_id->text(),"login",true);
    login_info _Data;
    memset(&_Data, 0x00,sizeof(login_info));
    if(isSearch)
    {
        m_search->getData(&_Data);
        qDebug() << "lineEdit is :" << ui->lineEdit_id->text() << "_Data id is:"<< _Data.id;
        if(std::strcmp(ui->lineEdit_pawssd->text().toLatin1(), _Data.password))
        {
            emit login_account();
            this->close();
        }
        else
        {
            MyMessageBox::showMyMessageBox(this, QStringLiteral("友情提醒"), QStringLiteral("账号或者密码错误!"), MESSAGE_WARNNING, BUTTON_OK, true);
        }
    }
    else
     MyMessageBox::showMyMessageBox(this, QStringLiteral("友情提醒"), QStringLiteral("账号不存在，请选择注册!"), MESSAGE_WARNNING, BUTTON_OK, true);
}
