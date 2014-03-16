#include "readerinfodialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

ReaderInfoDialog::ReaderInfoDialog(const QString &u, const QString &num, QWidget *parent) :
    QDialog(parent), str(num), user_name(u)
{
    IDLabel = new QLabel(tr("&ID:"));
    IDLineEdit = new QLineEdit;
    IDLabel->setBuddy(IDLineEdit);
    queryButton = new QPushButton(tr("Quer&y"));

    passwordLabel = new QLabel(tr("&Password:"));
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLabel->setBuddy(passwordLineEdit);

    againPasswordLabel = new QLabel(tr("&Affirm Password:"));
    againPasswordLineEdit = new QLineEdit;
    againPasswordLineEdit->setEchoMode(QLineEdit::Password);
    againPasswordLabel->setBuddy(againPasswordLineEdit);

    nameLabel = new QLabel(tr("&Name:"));
    nameLineEdit = new QLineEdit;
    nameLabel->setBuddy(nameLineEdit);

    sexLabel = new QLabel(tr("&Sex:"));
    sexComboBox = new QComboBox;
    sexComboBox->addItems(QStringList() << tr("male") << tr("female"));
    sexLabel->setBuddy(sexComboBox);

    birthdayLabel = new QLabel(tr("&Birthday:"));
    birthdayDateEdit = new QDateEdit;
    birthdayLabel->setBuddy(birthdayDateEdit);

    cardDateLabel = new QLabel(tr("&Card Date:"));
    cardDateEdit = new QDateEdit;
    cardDateLabel->setBuddy(cardDateEdit);
    cardDateEdit->setDate(QDate::currentDate());

    validDateLabel = new QLabel(tr("&Valid Date:"));
    validDateEdit = new QDateEdit;
    validDateEdit->setDate(QDate::currentDate().addYears(1));
    validDateLabel->setBuddy(validDateEdit);

    IDCardLabel = new QLabel(tr("&ID Card:"));
    IDCardLineEdit = new QLineEdit;
    IDCardLabel->setBuddy(IDCardLineEdit);

    phoneLabel = new QLabel(tr("&Phone:"));
    phoneLineEdit = new QLineEdit;
    phoneLabel->setBuddy(phoneLineEdit);

    stateLabel = new QLabel(tr("&State:"));
    stateComboBox = new QComboBox;
    stateComboBox->addItems(QStringList() << tr("normal") << tr("logout"));
    stateLabel->setBuddy(stateComboBox);

    typeLabel = new QLabel(tr("&Type:"));
    typeComboBox = new QComboBox;
    typeComboBox->addItems(QStringList() << tr("normal") << tr("VIP"));
    typeLabel->setBuddy(typeComboBox);


    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(IDLabel, 0, 0);
    gridLayout->addWidget(IDLineEdit, 0, 1);
    gridLayout->addWidget(queryButton, 0, 2);
    gridLayout->addWidget(passwordLabel, 1, 0);
    gridLayout->addWidget(passwordLineEdit, 1, 1);
    gridLayout->addWidget(againPasswordLabel, 2, 0);
    gridLayout->addWidget(againPasswordLineEdit, 2, 1);
    gridLayout->addWidget(nameLabel, 3, 0);
    gridLayout->addWidget(nameLineEdit, 3, 1);
    gridLayout->addWidget(sexLabel, 4, 0);
    gridLayout->addWidget(sexComboBox, 4, 1);
    gridLayout->addWidget(birthdayLabel, 5, 0);
    gridLayout->addWidget(birthdayDateEdit, 5, 1);
    gridLayout->addWidget(cardDateLabel, 6, 0);
    gridLayout->addWidget(cardDateEdit, 6, 1);
    gridLayout->addWidget(validDateLabel, 7, 0);
    gridLayout->addWidget(validDateEdit, 7, 1);
    gridLayout->addWidget(IDCardLabel, 8, 0);
    gridLayout->addWidget(IDCardLineEdit, 8, 1);
    gridLayout->addWidget(phoneLabel, 9, 0);
    gridLayout->addWidget(phoneLineEdit, 9, 1);
    gridLayout->addWidget(stateLabel, 10, 0);
    gridLayout->addWidget(stateComboBox, 10, 1);
    gridLayout->addWidget(typeLabel, 11, 0);
    gridLayout->addWidget(typeComboBox, 11, 1);

    groupBox = new QGroupBox(tr("Reader Information"));
    groupBox->setLayout(gridLayout);

    okButton = new QPushButton(tr("&OK"));
    cancelButton = new QPushButton(tr("Cancel"));

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(okButton);
    bottomLayout->addWidget(cancelButton);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(groupBox);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);

    if (str.isEmpty())
    {
        connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    }
    else
    {
        init();
        connect(okButton, SIGNAL(clicked()), this, SLOT(modifyClicked()));
    }
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(queryButton, SIGNAL(clicked()), this, SLOT(queryClicked()));
}

void ReaderInfoDialog::okButtonClicked()
{
    QString ID = IDLineEdit->text();

    QString sql = "select * from reader where ID='" + ID + "'";
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);
    if (query.isActive() && query.next())
    {
        QMessageBox::information(this, tr("Error"), tr("The ID has use."));
        return;
    }

    sql = "select * from admin where user_name='" + ID + "'";
    db = QSqlDatabase::database();
    query = db.exec(sql);
    if (query.isActive() && query.next())
    {
        QMessageBox::information(this, tr("Error"), tr("The ID has use."));
        return;
    }

    QString password1 = passwordLineEdit->text();
    QString password2 = againPasswordLineEdit->text();
    if (password1 != password2)
    {
        QMessageBox::information(this, tr("Error"), tr("Password error."));
        return;
    }
    QString name = nameLineEdit->text();
    QString sex = sexComboBox->currentText();
    QString birthday = birthdayDateEdit->date().toString(Qt::ISODate);
    QDate date = cardDateEdit->date();
    QString cardDate = date.toString(Qt::ISODate);
    QString validDate = validDateEdit->date().toString(Qt::ISODate);
    QString IDCard = IDCardLineEdit->text();
    QString phone = phoneLineEdit->text();

    int index = stateComboBox->currentIndex();
    QString state = QString::fromLocal8Bit("普通");
    if (index)
    {
        state = QString::fromLocal8Bit("注销");
    }

    index = typeComboBox->currentIndex();
    QString type = QString::fromLocal8Bit("普通");
    if (index)
    {
        type = "VIP";
    }


    sql = "insert into reader values('" + ID + "','" + name + "','" + sex + "','"
            + birthday + "','" + cardDate + "','" + validDate + "','" + IDCard + "','" + phone + "','"
            + state + "','" + type + "')";

    query = db.exec(sql);

    if (!query.isActive())
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
        return;
    }

    sql = "insert into admin values('" + ID + "','" + password1 + "','0','0')";
    query = db.exec(sql);

    sql = "insert into reader_log_info(ID,reader_ID,operation,operation_date) values('"
            + user_name + "','" + ID + "','add','" + QDateTime::currentDateTime().toString(Qt::ISODate)
            + "')";

    query = db.exec(sql);

    if (query.isActive())
    {
        QMessageBox::information(this, tr("Succeed"), tr("Add data succeed."));
        IDLineEdit->clear();
        passwordLineEdit->clear();
        againPasswordLineEdit->clear();
        nameLineEdit->clear();
        sexComboBox->setCurrentIndex(0);
        QDate date = QDate::currentDate();
        cardDateEdit->setDate(date);
        validDateEdit->setDate(date.addYears(1));
        IDCardLineEdit->clear();
        phoneLineEdit->clear();
    }
    else
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
    }
}

void ReaderInfoDialog::init()
{
    QString sql = "select * from reader where card_num='" + str + "'";
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);
    if (query.next())
    {
        QString ID = query.value(1).toString();
        IDLineEdit->setText(ID);
        IDLineEdit->setEnabled(false);

        QString name = query.value(2).toString();
        nameLineEdit->setText(name);

        passwordLabel->setVisible(false);
        passwordLineEdit->setVisible(false);
        againPasswordLabel->setVisible(false);
        againPasswordLineEdit->setVisible(false);

        QString sex = query.value(3).toString();
        bool b = sex.compare(QString::fromLocal8Bit("男"));
        sexComboBox->setCurrentIndex(b);

        QDate birthday = query.value(4).toDate();
        birthdayDateEdit->setDate(birthday);

        QDate cardDate = query.value(5).toDate();
        cardDateEdit->setDate(cardDate);

        QDate validDate = query.value(6).toDate();
        validDateEdit->setDate(validDate);

        QString IDCard = query.value(7).toString();
        IDCardLineEdit->setText(IDCard);

        QString phone = query.value(8).toString();
        phoneLineEdit->setText(phone);

        QString state = query.value(9).toString();
        b = state.compare(QString::fromLocal8Bit("普通"));
        stateComboBox->setCurrentIndex(b);

        QString type = query.value(10).toString();
        b = type.compare(QString::fromLocal8Bit("普通"));
        typeComboBox->setCurrentIndex(b);
    }
}

void ReaderInfoDialog::modifyClicked()
{
//    QString password1 = passwordLineEdit->text();
//    QString password2 = againPasswordLineEdit->text();
//    if (password1 != password2)
//    {
//        QMessageBox::information(this, tr("Error"), tr("Password error."));
//        return;
//    }
    QString ID = IDLineEdit->text();
    QString name = nameLineEdit->text();
    QString sex = sexComboBox->currentText();
    QString birthday = birthdayDateEdit->date().toString(Qt::ISODate);
    QString cardDate = cardDateEdit->date().toString(Qt::ISODate);
    QString validDate = validDateEdit->date().toString(Qt::ISODate);
    QString IDCard = IDCardLineEdit->text();
    QString phone = phoneLineEdit->text();
    QString state = stateComboBox->currentText();
    QString type = typeComboBox->currentText();

    QString sql = "update reader set user_name='" + name + "', sex='"
            + sex + "', birthday='" + birthday + "', card_date='" + cardDate + "', valid_date='" + validDate +
            "', ID_card='" + IDCard + "', phone='" + phone + "', state='" + state + "', type='" +type +
            "' where card_num='" + str + "'";

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

    if (!query.isActive())
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
        return;
    }

    sql = "insert into reader_log_info(ID,reader_ID,operation,operation_date) values('"
            + user_name + "','" + ID + "','update','" + QDateTime::currentDateTime().toString(Qt::ISODate)
            + "')";

    query = db.exec(sql);

    if (query.isActive())
    {
        QMessageBox::information(this, tr("Succeed"), tr("Modify data succeed."));
        QDialog::accept();
    }
    else
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
    }
}

void ReaderInfoDialog::queryClicked()
{
    QString ID = IDLineEdit->text();
    if (ID.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("The ID is empty."));
        return;
    }

    QString sql = "select * from reader where ID='" + ID + "'";
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);
    if (query.isActive() && query.next())
    {
        QMessageBox::information(this, tr("Error"), tr("The ID has use."));
        return;
    }

    sql = "select * from admin where user_name='" + ID + "'";
    db = QSqlDatabase::database();
    query = db.exec(sql);
    if (query.isActive() && query.next())
    {
        QMessageBox::information(this, tr("Error"), tr("The ID has use."));
        return;
    }

    QMessageBox::information(this, tr("Succeed"), tr("The ID Can use."));
}


