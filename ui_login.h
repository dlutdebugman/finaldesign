/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLineEdit *lineEdit_id;
    QLineEdit *lineEdit_pawssd;
    QPushButton *pushButton_login;
    QWidget *widget;
    QLabel *move_label;
    QLabel *label_theme;
    QLabel *label_3;
    QLabel *label_id;
    QPushButton *pushButton_min;
    QPushButton *pushButton_close;
    QPushButton *pushButton_reg;
    QPushButton *pushButton_modif_password;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(777, 421);
        lineEdit_id = new QLineEdit(login);
        lineEdit_id->setObjectName(QStringLiteral("lineEdit_id"));
        lineEdit_id->setGeometry(QRect(420, 130, 271, 27));
        lineEdit_id->setStyleSheet(QLatin1String("border: 1px solid #5CACEE;\n"
"	border-radius: 5px;\n"
"	padding: 2px;\n"
"	background: none;\n"
"	selection-background-color: #1B89CA;"));
        lineEdit_pawssd = new QLineEdit(login);
        lineEdit_pawssd->setObjectName(QStringLiteral("lineEdit_pawssd"));
        lineEdit_pawssd->setGeometry(QRect(420, 200, 271, 27));
        lineEdit_pawssd->setStyleSheet(QLatin1String("border: 1px solid #5CACEE;\n"
"	border-radius: 5px;\n"
"	padding: 2px;\n"
"	background: none;\n"
"	selection-background-color: #1B89CA;"));
        pushButton_login = new QPushButton(login);
        pushButton_login->setObjectName(QStringLiteral("pushButton_login"));
        pushButton_login->setGeometry(QRect(420, 260, 261, 41));
        pushButton_login->setStyleSheet(QLatin1String(" QPushButton\n"
"{\n"
"    font-family:Microsoft Yahei;\n"
"    color:white;\n"
"    background-color:rgb(14 , 150 , 254);\n"
"    border-radius:10px;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"    background-color:rgb(44 , 137 , 255);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"    background-color:rgb(14 , 135 , 228);\n"
"    padding-left:3px;\n"
"    padding-top:3px;\n"
"}"));
        widget = new QWidget(login);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 401, 421));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(241, 243, 242);"));
        move_label = new QLabel(widget);
        move_label->setObjectName(QStringLiteral("move_label"));
        move_label->setGeometry(QRect(90, 120, 211, 151));
        label_theme = new QLabel(widget);
        label_theme->setObjectName(QStringLiteral("label_theme"));
        label_theme->setGeometry(QRect(100, 10, 161, 31));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_theme->setFont(font);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(70, 350, 221, 51));
        label_3->setFont(font);
        label_3->setStyleSheet(QStringLiteral("color: rgb(102, 160, 207);"));
        label_id = new QLabel(login);
        label_id->setObjectName(QStringLiteral("label_id"));
        label_id->setGeometry(QRect(420, 100, 121, 17));
        pushButton_min = new QPushButton(login);
        pushButton_min->setObjectName(QStringLiteral("pushButton_min"));
        pushButton_min->setGeometry(QRect(690, 0, 41, 27));
        pushButton_min->setStyleSheet(QLatin1String("QPushButton {\n"
"	border-radius:0px;\n"
"color: rgb(102, 160, 207);\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-style:none;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(238, 0, 0, 128), stop:1 rgba(238, 44, 44, 255));\n"
"}\n"
""));
        pushButton_close = new QPushButton(login);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setGeometry(QRect(730, 0, 41, 27));
        pushButton_close->setStyleSheet(QLatin1String("QPushButton:hover{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(238, 0, 0, 128), stop:1 rgba(238, 44, 44, 255));\n"
"}\n"
"QPushButton {\n"
"	border-radius:0px;\n"
"color: rgb(102, 160, 207);\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-style:none;\n"
"}"));
        pushButton_reg = new QPushButton(login);
        pushButton_reg->setObjectName(QStringLiteral("pushButton_reg"));
        pushButton_reg->setGeometry(QRect(420, 300, 61, 27));
        pushButton_reg->setStyleSheet(QLatin1String("QPushButton {\n"
"	border-radius:0px;\n"
"	color: rgb(201, 174, 247);\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-style:none;\n"
"}\n"
""));
        pushButton_modif_password = new QPushButton(login);
        pushButton_modif_password->setObjectName(QStringLiteral("pushButton_modif_password"));
        pushButton_modif_password->setGeometry(QRect(620, 300, 61, 27));
        pushButton_modif_password->setStyleSheet(QLatin1String("QPushButton {\n"
"	border-radius:0px;\n"
"	color: rgb(201, 174, 247);\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-style:none;\n"
"}"));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QApplication::translate("login", "Dialog", Q_NULLPTR));
        lineEdit_id->setText(QString());
        lineEdit_pawssd->setText(QString());
        pushButton_login->setText(QApplication::translate("login", "\347\231\273\345\275\225", Q_NULLPTR));
        move_label->setText(QString());
        label_theme->setText(QString());
        label_3->setText(QApplication::translate("login", "\345\237\216\345\270\202\345\274\202\345\270\270\346\243\200\346\265\213\n"
"\346\225\260\346\215\256\345\210\206\346\236\220\357\274\214\344\271\220\346\255\244\344\270\215\347\226\262", Q_NULLPTR));
        label_id->setText(QString());
        pushButton_min->setText(QString());
        pushButton_close->setText(QString());
        pushButton_reg->setText(QApplication::translate("login", "\346\263\250\345\206\214", Q_NULLPTR));
        pushButton_modif_password->setText(QApplication::translate("login", "\344\277\256\346\224\271\345\257\206\347\240\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
