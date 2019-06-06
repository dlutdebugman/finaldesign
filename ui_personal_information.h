/********************************************************************************
** Form generated from reading UI file 'personal_information.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSONAL_INFORMATION_H
#define UI_PERSONAL_INFORMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_personal_information
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_professional;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *lineEdit_school;
    QLineEdit *lineEdit_phone;
    QLineEdit *lineEdit_name;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;

    void setupUi(QWidget *personal_information)
    {
        if (personal_information->objectName().isEmpty())
            personal_information->setObjectName(QStringLiteral("personal_information"));
        personal_information->resize(868, 611);
        gridLayout_2 = new QGridLayout(personal_information);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(personal_information);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout->addWidget(label_3, 3, 1, 1, 1);

        label_4 = new QLabel(personal_information);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout->addWidget(label_4, 5, 1, 1, 1);

        lineEdit_professional = new QLineEdit(personal_information);
        lineEdit_professional->setObjectName(QStringLiteral("lineEdit_professional"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_professional->sizePolicy().hasHeightForWidth());
        lineEdit_professional->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        lineEdit_professional->setFont(font1);
        lineEdit_professional->setStyleSheet(QLatin1String("border-bottom-width: 5px;border-style: solid;border-color: rgb(0, 0, 0);\n"
"background-color: rgba(255, 255, 255, 0);"));
        lineEdit_professional->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout->addWidget(lineEdit_professional, 5, 2, 1, 1);

        label = new QLabel(personal_information);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);
        label->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout->addWidget(label, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 1, 1, 1);

        lineEdit_school = new QLineEdit(personal_information);
        lineEdit_school->setObjectName(QStringLiteral("lineEdit_school"));
        sizePolicy.setHeightForWidth(lineEdit_school->sizePolicy().hasHeightForWidth());
        lineEdit_school->setSizePolicy(sizePolicy);
        lineEdit_school->setFont(font1);
        lineEdit_school->setStyleSheet(QLatin1String("border-bottom-width: 5px;border-style: solid;border-color: rgb(0, 0, 0);\n"
"background-color: rgba(255, 255, 255, 0);border-bottom-width: 5px;border-style: solid;border-color: rgb(0, 0, 0);"));
        lineEdit_school->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout->addWidget(lineEdit_school, 4, 2, 1, 1);

        lineEdit_phone = new QLineEdit(personal_information);
        lineEdit_phone->setObjectName(QStringLiteral("lineEdit_phone"));
        sizePolicy.setHeightForWidth(lineEdit_phone->sizePolicy().hasHeightForWidth());
        lineEdit_phone->setSizePolicy(sizePolicy);
        lineEdit_phone->setFont(font1);
        lineEdit_phone->setStyleSheet(QLatin1String("border-bottom-width: 5px;border-style: solid;border-color: rgb(0, 0, 0);\n"
"background-color: rgba(255, 255, 255, 0);border-bottom-width: 5px;border-style: solid;border-color: rgb(0, 0, 0);"));
        lineEdit_phone->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout->addWidget(lineEdit_phone, 3, 2, 1, 1);

        lineEdit_name = new QLineEdit(personal_information);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        sizePolicy.setHeightForWidth(lineEdit_name->sizePolicy().hasHeightForWidth());
        lineEdit_name->setSizePolicy(sizePolicy);
        lineEdit_name->setFont(font1);
        lineEdit_name->setStyleSheet(QLatin1String("border-bottom-width: 5px;border-style: solid;border-color: rgb(0, 0, 0);\n"
"background-color: rgba(255, 255, 255, 0);"));
        lineEdit_name->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout->addWidget(lineEdit_name, 2, 2, 1, 1);

        label_2 = new QLabel(personal_information);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);

        gridLayout->addWidget(label_2, 4, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        pushButton = new QPushButton(personal_information);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMaximumSize(QSize(200, 50));
        pushButton->setStyleSheet(QLatin1String(" QPushButton\n"
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

        horizontalLayout_5->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_5, 6, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_6 = new QLabel(personal_information);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setMaximumSize(QSize(100, 200));
        label_6->setStyleSheet(QStringLiteral("border-image: url(:/Resources/image/header.jpg);"));

        horizontalLayout->addWidget(label_6);


        gridLayout->addLayout(horizontalLayout, 1, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 2, 1, 1);


        retranslateUi(personal_information);

        QMetaObject::connectSlotsByName(personal_information);
    } // setupUi

    void retranslateUi(QWidget *personal_information)
    {
        personal_information->setWindowTitle(QApplication::translate("personal_information", "personal_information", Q_NULLPTR));
        label_3->setText(QApplication::translate("personal_information", "\347\224\265\350\257\235\345\217\267\347\240\201\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("personal_information", "\344\270\223    \344\270\232\357\274\232", Q_NULLPTR));
        label->setText(QApplication::translate("personal_information", "\346\230\265    \347\247\260\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("personal_information", "\345\255\246    \346\240\241\357\274\232", Q_NULLPTR));
        pushButton->setText(QApplication::translate("personal_information", "\344\277\235\345\255\230", Q_NULLPTR));
        label_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class personal_information: public Ui_personal_information {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSONAL_INFORMATION_H
