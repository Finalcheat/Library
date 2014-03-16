#include "userlogindialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

UserLoginDialog::UserLoginDialog( QWidget *parent) :
    QDialog(parent)
{
    groupBox = new QGroupBox(tr("Login Information"));

    userNameLabel = new QLabel(tr("User Na&me:"));
    userNameLineEdit = new QLineEdit;
    userNameLabel->setBuddy(userNameLineEdit);

    passwordLabel = new QLabel(tr("Passwor&d:"));
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);;
    passwordLabel->setBuddy(passwordLineEdit);

    userTypeLabel = new QLabel(tr("User Typ&e:"));
    userTypeComboBox = new QComboBox;
    userTypeComboBox->addItems(QStringList() << tr("Reader") << tr("Operator") << tr("Administrator"));
    userTypeLabel->setBuddy(userTypeComboBox);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addWidget(userNameLabel, 0, 0);
    topLayout->addWidget(userNameLineEdit, 0, 1);
    topLayout->addWidget(passwordLabel, 1, 0);
    topLayout->addWidget(passwordLineEdit, 1, 1);
    topLayout->addWidget(userTypeLabel, 2, 0);
    topLayout->addWidget(userTypeComboBox, 2, 1);

    groupBox->setLayout(topLayout);


    loginButton = new QPushButton(tr("Login"));
    cancelButton = new QPushButton(tr("Cancel"));

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(loginButton);
    bottomLayout->addStretch();
    bottomLayout->addWidget(cancelButton);
    bottomLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);

    setWindowTitle(tr("User Login"));
    setWindowIcon(QIcon(":/images/user.png"));

    setFixedHeight(sizeHint().height());

    resize(350, sizeHint().height());

    connect(loginButton, SIGNAL(clicked()), this, SLOT(loginButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    db = QSqlDatabase::addDatabase("QODBC");
    QString dsn = "Driver={sql server};server=;database=library";
    db.setDatabaseName(dsn);
    db.open();
}

void UserLoginDialog::loginButtonClicked()
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

    power = userTypeComboBox->currentIndex();

    QString sql = "select * from admin where user_name='" + userName
            + "' and password='" + password + "' and power=" + QString::number(power);

    QSqlQuery query = db.exec(sql);
    if (!query.isActive())
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
        return;
    }

    if (!query.next())
    {
        QMessageBox::information(this, tr("Error"), tr("User name or password or user type mistake."));
        return;
    }

    int state = query.value(3).toInt();
    if (state)
    {
        QMessageBox::information(this, tr("Error"), tr("The User has already ban"));
        return;
    }

    power = query.value(2).toInt();
    QDialog::accept();
}

QSqlDatabase UserLoginDialog::getDB()
{
    return db;
}

int UserLoginDialog::getPower() const
{
    return power;
}

void UserLoginDialog::clear()
{
    userNameLineEdit->clear();
    passwordLineEdit->clear();
    userTypeComboBox->setCurrentIndex(0);
    power = 0;
}

QString UserLoginDialog::getUserName() const
{
    return userNameLineEdit->text();
}
