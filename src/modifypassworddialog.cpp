#include "modifypassworddialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>

ModifyPasswordDialog::ModifyPasswordDialog(const QString &name, QWidget *parent) :
    QDialog(parent), userName(name)
{
    originalPasswordLabel = new QLabel(tr("Original Passwor&d:"));
    originalPasswordLineEdit = new QLineEdit;
    originalPasswordLineEdit->setEchoMode(QLineEdit::Password);
    originalPasswordLabel->setBuddy(originalPasswordLineEdit);

    targetPasswordLabel = new QLabel(tr("Target Passwor&d"));
    targetPasswordLineEdit = new QLineEdit;
    targetPasswordLineEdit->setEchoMode(QLineEdit::Password);
    targetPasswordLabel->setBuddy(targetPasswordLineEdit);

    atargetPasswordLabel = new QLabel(tr("Affirm Passwor&d"));
    atargetPasswordLineEdit = new QLineEdit;
    atargetPasswordLineEdit->setEchoMode(QLineEdit::Password);
    atargetPasswordLabel->setBuddy(atargetPasswordLineEdit);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addWidget(originalPasswordLabel, 0, 0);
    topLayout->addWidget(originalPasswordLineEdit, 0, 1);
    topLayout->addWidget(targetPasswordLabel, 1, 0);
    topLayout->addWidget(targetPasswordLineEdit, 1, 1);
    topLayout->addWidget(atargetPasswordLabel, 2, 0);
    topLayout->addWidget(atargetPasswordLineEdit, 2, 1);


    okButton = new QPushButton(tr("O&K"));
    cancelButton = new QPushButton(tr("Cance&l"));

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(okButton);
    bottomLayout->addStretch();
    bottomLayout->addWidget(cancelButton);
    bottomLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);

    setWindowTitle(tr("Modify Password"));

    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void ModifyPasswordDialog::okButtonClicked()
{
    QString password1 = targetPasswordLineEdit->text();
    QString password2 = atargetPasswordLineEdit->text();
    if (password1 != password2)
    {
        QMessageBox::information(this, tr("Error"), tr("Two password is not consistent"));
        return;
    }

    if (password1.size() > 16)
    {
        QMessageBox::information(this, tr("Error"), tr("Password length is not greater than 16"));
        return;
    }

    QString originalPassword = originalPasswordLineEdit->text();

    QString sql = "select * from admin where user_name='" + userName + "' and password='" + originalPassword + "'";

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

    if (!query.next())
    {
        QMessageBox::information(this, tr("Error"), tr("Original Password error"));
        return;
    }

    sql = "update admin set password='" + password1 + "' where user_name='" + userName + "'";

    query = db.exec(sql);
    if (query.isActive())
    {
        QMessageBox::information(this, tr("Succeed"), tr("Password modification success"));
        QDialog::accept();
    }
    else
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
    }
}
