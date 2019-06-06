#include "register_info.h"
#include "ui_register_info.h"
#include "customicon.h"
#include <QMouseEvent>
register_info::register_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_info)
{
    ui->setupUi(this);
	max = false;
    setWindowFlags(Qt::FramelessWindowHint |Qt::WindowMinMaxButtonsHint |Qt::WindowSystemMenuHint);
    setModal(true);
    customIcon::Instance()->SetIcon(ui->pushButton_close, QChar(0xf00d), 10);
    connect(ui->pushButton_close, SIGNAL(clicked()),this,SLOT(close()));

}

register_info::~register_info()
{
    delete ui;
}
void register_info::mouseMoveEvent(QMouseEvent *e)
{
    if (mousePressed && (e->buttons() && Qt::LeftButton) && !max) {
        this->move(e->globalPos() - mousePoint);
        e->accept();
    }
}

void register_info::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = e->globalPos() - this->pos();
        e->accept();
    }
}

void register_info::mouseReleaseEvent(QMouseEvent *)
{
    mousePressed = false;
}

void register_info::set_account_text(QString text)
{
    ui->label_id->setText(text);
}

void register_info::set_password_text(QString text)
{
    ui->label_id_2->setText(text);
}

void register_info::set_check_name_text(QString text)
{
    ui->label_id_3->setText(text);
}

void register_info::set_login_text(QString text)
{
    ui->pushButton_login->setText(text);
}

void register_info::set_check_hide()
{
    ui->label_id_3->hide();
    ui->lineEdit_id_3->hide();
    ui->lineEdit_id_3->setText("123");
}

void register_info::on_pushButton_login_clicked()
{
    if(!ui->lineEdit_id->text().isEmpty() &&
       !ui->lineEdit_id_2->text().isEmpty() &&
       !ui->lineEdit_id_3->text().isEmpty())
    {
        emit send_account(ui->lineEdit_id->text(), ui->lineEdit_id_2->text(), ui->lineEdit_id_3->text());
    }
   // this->close();
}
void register_info::set_dialog_tip(QString text)
{
	ui->tip->setText(text);
}