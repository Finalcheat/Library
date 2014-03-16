/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Sun Sep 9 22:17:31 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGroupBox *groupBox;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_2;
    QComboBox *comboBox_2;
    QGroupBox *groupBox_3;
    QComboBox *comboBox_3;
    QPushButton *pushButton_3;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QComboBox *comboBox_5;
    QWidget *page_2;
    QComboBox *comboBox_4;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(741, 497);
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 40, 211, 121));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(20, 30, 161, 22));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 70, 75, 23));
        groupBox_2 = new QGroupBox(Dialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 170, 211, 131));
        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 80, 75, 23));
        comboBox_2 = new QComboBox(groupBox_2);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(20, 30, 161, 22));
        groupBox_3 = new QGroupBox(Dialog);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(30, 330, 211, 131));
        comboBox_3 = new QComboBox(groupBox_3);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(30, 30, 151, 22));
        pushButton_3 = new QPushButton(groupBox_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(30, 80, 75, 23));
        stackedWidget = new QStackedWidget(Dialog);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(320, 110, 341, 311));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        comboBox_5 = new QComboBox(page);
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));
        comboBox_5->setGeometry(QRect(70, 180, 69, 22));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        comboBox_4 = new QComboBox(page_2);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(120, 80, 69, 22));
        stackedWidget->addWidget(page_2);

        retranslateUi(Dialog);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Dialog", "reader information", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\346\211\200\346\234\211\347\224\250\346\210\267\346\225\260\351\207\217", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "\346\231\256\351\200\232\347\224\250\346\210\267\346\225\260\351\207\217", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "VIP\347\224\250\346\210\267\346\225\260\351\207\217", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "\345\200\237\344\271\246\347\264\257\350\256\241\346\225\260\351\207\217", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "\350\277\207\346\234\237\347\224\250\346\210\267", 0, QApplication::UnicodeUTF8)
        );
        pushButton->setText(QApplication::translate("Dialog", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("Dialog", "book information", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Dialog", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\350\242\253\345\200\237\346\254\241\346\225\260", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "\346\214\202\345\244\261\345\233\276\344\271\246", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "\345\207\272\347\211\210\347\244\276", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "\344\275\234\350\200\205", 0, QApplication::UnicodeUTF8)
        );
        groupBox_3->setTitle(QApplication::translate("Dialog", "fine information", 0, QApplication::UnicodeUTF8));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "\347\275\232\346\254\276\350\257\273\350\200\205", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "\347\275\232\346\254\276\345\233\276\344\271\246", 0, QApplication::UnicodeUTF8)
        );
        pushButton_3->setText(QApplication::translate("Dialog", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
