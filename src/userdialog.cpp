#include "userdialog.h"
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>

UserDialog::UserDialog(const QString &u,const QString &name, QWidget *parent) :
    QDialog(parent), str(name), user_name(u)
{
    groupBox = new QGroupBox(tr("User Information"));

    userNameLabel = new QLabel(tr("User Na&me:"));
    userNameLineEdit = new QLineEdit;
    userNameLabel->setBuddy(userNameLineEdit);

    passwordLabel = new QLabel(tr("Passwor&d:"));
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLabel->setBuddy(passwordLineEdit);

    userTypeLabel = new QLabel(tr("User Typ&e:"));
    userTypeComboBox = new QComboBox;
    userTypeComboBox->addItems(QStringList() << tr("Reader") << tr("Operator") << tr("Administrator"));
    userTypeLabel->setBuddy(userTypeComboBox);

    stateLabel = new QLabel(tr("Stat&e:"));
    stateComboBox = new QComboBox;
    stateComboBox->addItems(QStringList() << tr("Normal") << tr("Ban"));
    stateLabel->setBuddy(stateComboBox);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addWidget(userNameLabel, 0, 0);
    topLayout->addWidget(userNameLineEdit, 0, 1);
    topLayout->addWidget(passwordLabel, 1, 0);
    topLayout->addWidget(passwordLineEdit, 1, 1);
    topLayout->addWidget(userTypeLabel, 2, 0);
    topLayout->addWidget(userTypeComboBox, 2, 1);
    topLayout->addWidget(stateLabel, 3, 0);
    topLayout->addWidget(stateComboBox, 3, 1);

    groupBox->setLayout(topLayout);

    okButton = new QPushButton(tr("O&K"));
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

    setFixedHeight(sizeHint().height());
    resize(420, sizeHint().height());

    init();

    if (name.isEmpty())
    {
        connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    }
    else
    {
        userNameLineEdit->setEnabled(false);
        connect(okButton, SIGNAL(clicked()), this, SLOT(modifyClicked()));
    }
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void UserDialog::okButtonClicked()
{
    QString userName = userNameLineEdit->text();

    if (userName.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("User Name Can not be empty"));
        return;
    }

    if (userName.size() > 10)
    {
        QMessageBox::information(this, tr("Error"), tr("User Name length is not greater than 10"));
        return;
    }

    QString password = passwordLineEdit->text();
    if (password.size() > 16)
    {
        QMessageBox::information(this, tr("Error"), tr("Password length is not greater than 16"));
        return;
    }

    int power = userTypeComboBox->currentIndex();
    int state = stateComboBox->currentIndex();

    QString sql = "insert into admin values('" + userName + "','" + password + "','"
            + QString::number(power) + "','" + QString::number(state) + "')";


    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

//    sql = "insert into reader(ID) values('" + userName + "')";
//    query = db.exec(sql);

    sql = "insert into reader_log_info(ID,reader_ID,operation,operation_date) values('"
            + user_name + "','" + userName + "','add','" + QDateTime::currentDateTime().toString(Qt::ISODate)
            + "')";

    query = db.exec(sql);

    if (query.isActive())
    {
        QMessageBox::information(this, tr("Succeed"), tr("Add user %1 success").arg(userName));
        userNameLineEdit->clear();
        passwordLineEdit->clear();
        userTypeComboBox->setCurrentIndex(0);
        stateComboBox->setCurrentIndex(0);
    }
    else
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
    }
}

void UserDialog::init()
{
    if (!str.isEmpty())
    {
        userNameLineEdit->setText(str);

        QSqlDatabase db = QSqlDatabase::database();
        QString sql = "select * from admin where user_name='" + str + "'";
        QSqlQuery query = db.exec(sql);
        if (query.next())
        {
            QString password = query.value(1).toString();
//            qDebug() << password;
            passwordLineEdit->setText(password);
            int power = query.value(2).toInt();
            userTypeComboBox->setCurrentIndex(power);
            int state = query.value(3).toInt();
            stateComboBox->setCurrentIndex(state);
        }
    }
}

void UserDialog::modifyClicked()
{
    QString userName = userNameLineEdit->text();
    QString newPassword = passwordLineEdit->text();
    int power = userTypeComboBox->currentIndex();
    int state = stateComboBox->currentIndex();

    QString sql = "update admin set password='"
            + newPassword + "', power=" + QString::number(power) + ", state=" + QString::number(state)
            + " where user_name='" + str + "'";

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

    sql = "insert into reader_log_info(ID,reader_ID,operation,operation_date) values('"
            + user_name + "','" + userName + "','update','" + QDateTime::currentDateTime().toString(Qt::ISODate)
            + "')";

    query = db.exec(sql);

    if (query.isActive())
    {
        QMessageBox::information(this, tr("succeed"), tr("Modify succeed."));
        QDialog::accept();
    }
    else
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
    }
}
