/********************************************************************************
** Form generated from reading UI file 'messageBox.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEBOX_H
#define UI_MESSAGEBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyMessageBox
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *MessageIcon;
    QLabel *MessageContent;
    QLineEdit *inputContent;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pButtonOk;
    QPushButton *pButtonCancel;

    void setupUi(QWidget *MyMessageBox)
    {
        if (MyMessageBox->objectName().isEmpty())
            MyMessageBox->setObjectName(QStringLiteral("MyMessageBox"));
        MyMessageBox->resize(388, 158);
        MyMessageBox->setMinimumSize(QSize(388, 158));
        MyMessageBox->setMaximumSize(QSize(388, 158));
        verticalLayout = new QVBoxLayout(MyMessageBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 22, 0, 10);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(12);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, -1, 22, -1);
        horizontalSpacer_2 = new QSpacerItem(48, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        MessageIcon = new QLabel(MyMessageBox);
        MessageIcon->setObjectName(QStringLiteral("MessageIcon"));
        MessageIcon->setMinimumSize(QSize(38, 38));
        MessageIcon->setMaximumSize(QSize(38, 38));

        horizontalLayout_2->addWidget(MessageIcon);

        MessageContent = new QLabel(MyMessageBox);
        MessageContent->setObjectName(QStringLiteral("MessageContent"));

        horizontalLayout_2->addWidget(MessageContent);

        inputContent = new QLineEdit(MyMessageBox);
        inputContent->setObjectName(QStringLiteral("inputContent"));
        inputContent->setMinimumSize(QSize(180, 25));
        inputContent->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_2->addWidget(inputContent);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(12);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 10, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pButtonOk = new QPushButton(MyMessageBox);
        pButtonOk->setObjectName(QStringLiteral("pButtonOk"));
        pButtonOk->setMinimumSize(QSize(70, 25));
        pButtonOk->setMaximumSize(QSize(70, 25));

        horizontalLayout->addWidget(pButtonOk);

        pButtonCancel = new QPushButton(MyMessageBox);
        pButtonCancel->setObjectName(QStringLiteral("pButtonCancel"));
        pButtonCancel->setMinimumSize(QSize(70, 25));
        pButtonCancel->setMaximumSize(QSize(70, 25));

        horizontalLayout->addWidget(pButtonCancel);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MyMessageBox);

        QMetaObject::connectSlotsByName(MyMessageBox);
    } // setupUi

    void retranslateUi(QWidget *MyMessageBox)
    {
        MyMessageBox->setWindowTitle(QApplication::translate("MyMessageBox", "MyMessageBox", Q_NULLPTR));
        MessageIcon->setText(QApplication::translate("MyMessageBox", "TextLabel", Q_NULLPTR));
        MessageContent->setText(QApplication::translate("MyMessageBox", "TextLabel", Q_NULLPTR));
        pButtonOk->setText(QString());
        pButtonCancel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MyMessageBox: public Ui_MyMessageBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEBOX_H
