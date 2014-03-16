#include "settingdialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent)
{
    lendBookMaxLaebl = new QLabel(tr("&Reader Lend Book Max:"));
    lendBookMaxLineEdit = new QLineEdit;
    lendBookMaxLaebl->setBuddy(lendBookMaxLineEdit);

    renewBookMaxLabel = new QLabel(tr("&Renew Book Max:"));
    renewBookMaxLineEdit = new QLineEdit;
    renewBookMaxLabel->setBuddy(renewBookMaxLineEdit);

    vipLendBookMaxLabel = new QLabel(tr("&VIP Lend Book Max:"));
    vipLendBookMaxLineEdit = new QLineEdit;
    vipLendBookMaxLabel->setBuddy(vipLendBookMaxLineEdit);

    vipRenewBookMaxLabel = new QLabel(tr("&VIP Renew Book Max:"));
    vipRenewBookMaxLineEdit = new QLineEdit;
    vipRenewBookMaxLabel->setBuddy(vipRenewBookMaxLineEdit);

    lendBookDateLabel = new QLabel(tr("&Lend Book Date:"));
    lendBookDateLineEdit = new QLineEdit;
    lendBookDateLabel->setBuddy(lendBookDateLineEdit);

    damageMoneyLabel = new QLabel(tr("&Damage Money:"));
    damageMoneyLineEdit = new QLineEdit;
    damageMoneyLabel->setBuddy(damageMoneyLineEdit);

    dateMoneyLabel = new QLabel(tr("&Date Money:"));
    dateMoneyLineEdit = new QLineEdit;
    dateMoneyLabel->setBuddy(dateMoneyLineEdit);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(lendBookMaxLaebl, 0, 0);
    gridLayout->addWidget(lendBookMaxLineEdit, 0, 1);
    gridLayout->addWidget(renewBookMaxLabel, 1, 0);
    gridLayout->addWidget(renewBookMaxLineEdit, 1, 1);
    gridLayout->addWidget(vipLendBookMaxLabel, 2, 0);
    gridLayout->addWidget(vipLendBookMaxLineEdit, 2, 1);
    gridLayout->addWidget(vipRenewBookMaxLabel, 3, 0);
    gridLayout->addWidget(vipRenewBookMaxLineEdit, 3, 1);
    gridLayout->addWidget(lendBookDateLabel, 4, 0);
    gridLayout->addWidget(lendBookDateLineEdit, 4, 1);
    gridLayout->addWidget(damageMoneyLabel, 5, 0);
    gridLayout->addWidget(damageMoneyLineEdit, 5, 1);
    gridLayout->addWidget(dateMoneyLabel, 6, 0);
    gridLayout->addWidget(dateMoneyLineEdit, 6, 1);

    QGroupBox *groupBox = new QGroupBox(tr("Library Information"));
    groupBox->setLayout(gridLayout);


    okButton = new QPushButton(tr("&OK"));
    cancelButton = new QPushButton(tr("Cancel"));

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(okButton);
    bottomLayout->addStretch();
    bottomLayout->addWidget(cancelButton);
    bottomLayout->addStretch();


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);

    initData();
    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void SettingDialog::initData()
{
    QString sql = "select * from library_info";
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);
    if (query.next())
    {
        str = query.value(0).toString();
        lendBookMaxLineEdit->setText(query.value(0).toString());
        renewBookMaxLineEdit->setText(query.value(1).toString());
        vipLendBookMaxLineEdit->setText(query.value(2).toString());
        vipRenewBookMaxLineEdit->setText(query.value(3).toString());
        lendBookDateLineEdit->setText(query.value(4).toString());
        damageMoneyLineEdit->setText(query.value(5).toString());
        dateMoneyLineEdit->setText(query.value(6).toString());
    }
}

void SettingDialog::okButtonClicked()
{
    QString str1 = lendBookMaxLineEdit->text();
    QString str2 = renewBookMaxLineEdit->text();
    QString str3 = vipLendBookMaxLineEdit->text();
    QString str4 = vipRenewBookMaxLineEdit->text();
    QString str5 = lendBookMaxLineEdit->text();
    QString str6 = damageMoneyLineEdit->text();
    QString str7 = dateMoneyLineEdit->text();

    QString sql = "update library_info set reader_lend_book_max='" + str1 + "',reader_renew_book_max='"
            + str2 + "',VIP_lend_book_max='" + str3 + "',VIP_renew_book_max='" + str4 + "',lend_book_date='"
            + str5 + "',damage_money='" + str6 + "',date_money='" + str7 + "' where reader_lend_book_max='"
            + str + "'";

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);
    if (query.isActive())
    {
        QMessageBox::information(this, tr("Succeed"), tr("Modify Succeed."));
        QDialog::accept();
    }
    else
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
    }
}
