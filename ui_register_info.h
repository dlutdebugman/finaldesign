/********************************************************************************
** Form generated from reading UI file 'register_info.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_INFO_H
#define UI_REGISTER_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_register_info
{
public:
    QPushButton *pushButton_close;
    QLineEdit *lineEdit_id;
    QLabel *label_id;
    QLineEdit *lineEdit_id_2;
    QLabel *label_id_2;
    QLineEdit *lineEdit_id_3;
    QLabel *label_id_3;
    QPushButton *pushButton_login;
    QLabel *tip;

    void setupUi(QDialog *register_info)
    {
        if (register_info->objectName().isEmpty())
            register_info->setObjectName(QStringLiteral("register_info"));
        register_info->resize(623, 450);
        pushButton_close = new QPushButton(register_info);
        pushButton_close->setObjectName(QStringLiteral("pushButton_close"));
        pushButton_close->setGeometry(QRect(580, 0, 41, 27));
        pushButton_close->setStyleSheet(QLatin1String("QPushButton:hover{\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(238, 0, 0, 128), stop:1 rgba(238, 44, 44, 255));\n"
"}\n"
"QPushButton {\n"
"	border-radius:0px;\n"
"color: rgb(102, 160, 207);\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-style:none;\n"
"}"));
        lineEdit_id = new QLineEdit(register_info);
        lineEdit_id->setObjectName(QStringLiteral("lineEdit_id"));
        lineEdit_id->setGeometry(QRect(200, 120, 271, 27));
        lineEdit_id->setStyleSheet(QLatin1String("border: 1px solid #5CACEE;\n"
"	border-radius: 5px;\n"
"	padding: 2px;\n"
"	background: none;\n"
"	selection-background-color: #1B89CA;"));
        label_id = new QLabel(register_info);
        label_id->setObjectName(QStringLiteral("label_id"));
        label_id->setGeometry(QRect(70, 120, 121, 17));
        lineEdit_id_2 = new QLineEdit(register_info);
        lineEdit_id_2->setObjectName(QStringLiteral("lineEdit_id_2"));
        lineEdit_id_2->setGeometry(QRect(200, 170, 271, 27));
        lineEdit_id_2->setStyleSheet(QLatin1String("border: 1px solid #5CACEE;\n"
"	border-radius: 5px;\n"
"	padding: 2px;\n"
"	background: none;\n"
"	selection-background-color: #1B89CA;"));
        label_id_2 = new QLabel(register_info);
        label_id_2->setObjectName(QStringLiteral("label_id_2"));
        label_id_2->setGeometry(QRect(70, 170, 121, 17));
        lineEdit_id_3 = new QLineEdit(register_info);
        lineEdit_id_3->setObjectName(QStringLiteral("lineEdit_id_3"));
        lineEdit_id_3->setGeometry(QRect(200, 220, 271, 27));
        lineEdit_id_3->setStyleSheet(QLatin1String("border: 1px solid #5CACEE;\n"
"	border-radius: 5px;\n"
"	padding: 2px;\n"
"	background: none;\n"
"	selection-background-color: #1B89CA;"));
        label_id_3 = new QLabel(register_info);
        label_id_3->setObjectName(QStringLiteral("label_id_3"));
        label_id_3->setGeometry(QRect(70, 220, 121, 17));
        pushButton_login = new QPushButton(register_info);
        pushButton_login->setObjectName(QStringLiteral("pushButton_login"));
        pushButton_login->setGeometry(QRect(200, 300, 261, 41));
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
        tip = new QLabel(register_info);
        tip->setObjectName(QStringLiteral("tip"));
        tip->setGeometry(QRect(10, 10, 301, 41));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        tip->setFont(font);

        retranslateUi(register_info);

        QMetaObject::connectSlotsByName(register_info);
    } // setupUi

    void retranslateUi(QDialog *register_info)
    {
        register_info->setWindowTitle(QApplication::translate("register_info", "Dialog", Q_NULLPTR));
        pushButton_close->setText(QString());
        label_id->setText(QString());
        label_id_2->setText(QString());
        label_id_3->setText(QString());
        pushButton_login->setText(QString());
        tip->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class register_info: public Ui_register_info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_INFO_H
