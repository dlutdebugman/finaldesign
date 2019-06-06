/********************************************************************************
** Form generated from reading UI file 'image_show.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGE_SHOW_H
#define UI_IMAGE_SHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_image_show
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *image_show)
    {
        if (image_show->objectName().isEmpty())
            image_show->setObjectName(QStringLiteral("image_show"));
        image_show->resize(885, 617);
        gridLayout_2 = new QGridLayout(image_show);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(image_show);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(500, 500));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pushButton = new QPushButton(image_show);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(100, 60));
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

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_2->addItem(verticalSpacer, 0, 0, 1, 1);


        retranslateUi(image_show);

        QMetaObject::connectSlotsByName(image_show);
    } // setupUi

    void retranslateUi(QWidget *image_show)
    {
        image_show->setWindowTitle(QApplication::translate("image_show", "image_show", Q_NULLPTR));
        label->setText(QString());
        pushButton->setText(QApplication::translate("image_show", "\344\270\213\344\270\200\345\274\240", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class image_show: public Ui_image_show {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGE_SHOW_H
