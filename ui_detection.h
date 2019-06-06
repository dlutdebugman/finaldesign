/********************************************************************************
** Form generated from reading UI file 'detection.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETECTION_H
#define UI_DETECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_detection
{
public:
    QPushButton *select_m_button;
    QPushButton *likelihood_button;
    QPushButton *pushButton_region;
    QLineEdit *regionRange;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *endTime;
    QLineEdit *beginTime;
    QLabel *label;
    QLabel *output;
    QPushButton *fresh_button;
    QLabel *label_4;

    void setupUi(QWidget *detection)
    {
        if (detection->objectName().isEmpty())
            detection->setObjectName(QStringLiteral("detection"));
        detection->resize(1104, 547);
        select_m_button = new QPushButton(detection);
        select_m_button->setObjectName(QStringLiteral("select_m_button"));
        select_m_button->setGeometry(QRect(30, 80, 100, 50));
        select_m_button->setMinimumSize(QSize(0, 50));
        select_m_button->setStyleSheet(QLatin1String(" QPushButton\n"
"{\n"
"    font-family:Microsoft Yahei;\n"
"    color:white;\n"
"    background-color:rgb(14 , 150 , 254);\n"
"    border-radius:1px;\n"
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
        likelihood_button = new QPushButton(detection);
        likelihood_button->setObjectName(QStringLiteral("likelihood_button"));
        likelihood_button->setGeometry(QRect(30, 250, 100, 50));
        likelihood_button->setMinimumSize(QSize(0, 50));
        likelihood_button->setStyleSheet(QLatin1String(" QPushButton\n"
"{\n"
"    font-family:Microsoft Yahei;\n"
"    color:white;\n"
"    background-color:rgb(14 , 150 , 254);\n"
"    border-radius:1px;\n"
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
        pushButton_region = new QPushButton(detection);
        pushButton_region->setObjectName(QStringLiteral("pushButton_region"));
        pushButton_region->setGeometry(QRect(30, 420, 100, 50));
        pushButton_region->setMinimumSize(QSize(0, 50));
        pushButton_region->setStyleSheet(QLatin1String(" QPushButton\n"
"{\n"
"    font-family:Microsoft Yahei;\n"
"    color:white;\n"
"    background-color:rgb(14 , 150 , 254);\n"
"    border-radius:1px;\n"
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
        regionRange = new QLineEdit(detection);
        regionRange->setObjectName(QStringLiteral("regionRange"));
        regionRange->setGeometry(QRect(321, 141, 200, 50));
        regionRange->setMinimumSize(QSize(0, 50));
        regionRange->setMaximumSize(QSize(200, 16777215));
        label_2 = new QLabel(detection);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(161, 141, 81, 51));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_3 = new QLabel(detection);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(160, 261, 101, 41));
        label_3->setFont(font);
        endTime = new QLineEdit(detection);
        endTime->setObjectName(QStringLiteral("endTime"));
        endTime->setGeometry(QRect(321, 351, 200, 50));
        endTime->setMinimumSize(QSize(0, 50));
        endTime->setMaximumSize(QSize(200, 16777215));
        beginTime = new QLineEdit(detection);
        beginTime->setObjectName(QStringLiteral("beginTime"));
        beginTime->setGeometry(QRect(321, 251, 200, 50));
        beginTime->setMinimumSize(QSize(0, 50));
        beginTime->setMaximumSize(QSize(200, 16777215));
        label = new QLabel(detection);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(160, 360, 101, 31));
        label->setFont(font);
        output = new QLabel(detection);
        output->setObjectName(QStringLiteral("output"));
        output->setGeometry(QRect(170, 90, 800, 31));
        output->setMinimumSize(QSize(800, 0));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        output->setFont(font1);
        output->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        fresh_button = new QPushButton(detection);
        fresh_button->setObjectName(QStringLiteral("fresh_button"));
        fresh_button->setGeometry(QRect(290, 420, 100, 50));
        fresh_button->setMinimumSize(QSize(0, 50));
        fresh_button->setStyleSheet(QLatin1String(" QPushButton\n"
"{\n"
"    font-family:Microsoft Yahei;\n"
"    color:white;\n"
"    background-color:rgb(14 , 150 , 254);\n"
"    border-radius:1px;\n"
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
        label_4 = new QLabel(detection);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(570, 60, 450, 450));
        label_4->setMaximumSize(QSize(500, 500));

        retranslateUi(detection);

        QMetaObject::connectSlotsByName(detection);
    } // setupUi

    void retranslateUi(QWidget *detection)
    {
        detection->setWindowTitle(QApplication::translate("detection", "detection", Q_NULLPTR));
        select_m_button->setText(QApplication::translate("detection", "\346\275\234\345\234\250\344\270\273\351\242\230\346\250\241\345\236\213\345\210\206\351\205\215", Q_NULLPTR));
        likelihood_button->setText(QApplication::translate("detection", "\344\276\235\347\204\266\346\257\224\346\243\200\346\265\213", Q_NULLPTR));
        pushButton_region->setText(QApplication::translate("detection", "\345\274\202\345\270\270\345\214\272\345\237\237\347\224\237\346\210\220", Q_NULLPTR));
        regionRange->setText(QString());
        label_2->setText(QApplication::translate("detection", "\350\214\203  \345\233\264 \357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("detection", "\350\265\267\345\247\213\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        endTime->setText(QString());
        beginTime->setText(QString());
        label->setText(QApplication::translate("detection", "\347\273\210\346\255\242\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        output->setText(QString());
        fresh_button->setText(QApplication::translate("detection", "\345\210\267\346\226\260\345\233\276\347\211\207", Q_NULLPTR));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class detection: public Ui_detection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETECTION_H
