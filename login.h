#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "Search.h"
#include "register_info.h"

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();
private:
    /*!
      *@brief:鼠标移动事件
      *@param:e[in] 鼠标事件
      */
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    /*!
      *@brief:鼠标点击事件
      *@param:e[in] 鼠标事件
      */
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    /*!
      *@brief:鼠标释放事件
      *@param:e[in] 鼠标事件
      */
    void mouseReleaseEvent(QMouseEvent *) Q_DECL_OVERRIDE;
private:
    /*!
    *@brief:使窗口根据不同的显示器显示都居中显示
    */
    void FormInCenter(QWidget *frm);
private:
    /*!
     *@brief:鼠标拖动自定义标题栏时的坐标
     */
    QPoint mousePoint;
    bool mousePressed;
    /*!
     *@brief:是否最大化
    */
    bool max;
    Search  *m_search;
private slots:

    void on_pushButton_min_clicked();

    void on_pushButton_reg_clicked();

    void save_register_info(QString,QString,QString);

    void on_pushButton_modif_password_clicked();

    void set_name_check(QString id, QString password, QString check_name);

    void set_update_password(QString id, QString password, QString check_name);

    void on_pushButton_login_clicked();

signals:
    void login_account();
    void modification_password();
private:
    register_info *m_register;
    register_info *m_retrieve_password;
    register_info *m_set_password;
private:
    Ui::login *ui;
};

#endif // LOGIN_H
