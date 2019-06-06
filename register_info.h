#ifndef REGISTER_INFO_H
#define REGISTER_INFO_H

#include <QDialog>

namespace Ui {
class register_info;
}

class register_info : public QDialog
{
    Q_OBJECT

public:
    explicit register_info(QWidget *parent = 0);
    ~register_info();
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
public:
    void set_account_text(QString);
    void set_password_text(QString);
    void set_check_name_text(QString);
    void set_login_text(QString);
    void set_check_hide();
	void set_dialog_tip(QString text);
signals:
  void send_account(QString,QString, QString);

private slots:
  void on_pushButton_login_clicked();

private:
    Ui::register_info *ui;
};

#endif // REGISTER_INFO_H
