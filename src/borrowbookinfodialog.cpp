#include "borrowbookinfodialog.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDebug>

BorrowBookInfoDialog::BorrowBookInfoDialog(const QString &u, const QString &num, QWidget *parent) :
    QDialog(parent), user_name(u)
{
    comboBox = new QComboBox;
    comboBox->addItems(QStringList() << tr("card_num") << tr("ID") << tr("ID_card"));
    lineEdit = new QLineEdit;
    queryButton = new QPushButton(tr("Que&ry"));

    QHBoxLayout *toplayout = new QHBoxLayout;
    toplayout->addWidget(comboBox);
    toplayout->addWidget(lineEdit);
    toplayout->addWidget(queryButton);

    bookNumLabel = new QLabel(tr("&Number:"));
    bookNumLineEdit = new QLineEdit;
    bookNumLineEdit->setEnabled(false);
    bookNumLabel->setBuddy(bookNumLineEdit);
    ISBNLabel = new QLabel(tr("&ISBN:"));
    ISBNLineEdit = new QLineEdit;
    ISBNLineEdit->setEnabled(false);
    ISBNLabel->setBuddy(ISBNLineEdit);
    bookNameLabel = new QLabel(tr("&Book Name:"));
    bookNameLineEdit = new QLineEdit;
    bookNameLineEdit->setEnabled(false);
    bookNameLabel->setBuddy(bookNameLineEdit);
    authorLabel = new QLabel(tr("&Author:"));
    authorLineEdit = new QLineEdit;
    authorLineEdit->setEnabled(false);
    authorLabel->setBuddy(authorLineEdit);
    pagesLabel = new QLabel(tr("&Pages:"));
    pagesSpinBox = new QSpinBox;
    pagesSpinBox->setEnabled(false);
    pagesLabel->setBuddy(pagesSpinBox);
    priceLabel = new QLabel(tr("&Price:"));
    priceDoubleSpinBox = new QDoubleSpinBox;
    priceDoubleSpinBox->setEnabled(false);
    priceLabel->setBuddy(priceDoubleSpinBox);
    publisherLabel = new QLabel(tr("&Publisher:"));
    publisherLineEdit = new QLineEdit;
    publisherLineEdit->setEnabled(false);
    publisherLabel->setBuddy(publisherLineEdit);
    pubdateLabel = new QLabel(tr("&Pubdate:"));
    pubdateDateEdit = new QDateEdit;
    pubdateDateEdit->setEnabled(false);
    pubdateLabel->setBuddy(pubdateDateEdit);

    QGridLayout *bookInfoLayout = new QGridLayout;
    bookInfoLayout->addWidget(bookNumLabel, 0, 0);
    bookInfoLayout->addWidget(bookNumLineEdit, 0, 1);
    bookInfoLayout->addWidget(ISBNLabel, 1, 0);
    bookInfoLayout->addWidget(ISBNLineEdit, 1, 1);
    bookInfoLayout->addWidget(bookNameLabel, 2, 0);
    bookInfoLayout->addWidget(bookNameLineEdit, 2, 1);
    bookInfoLayout->addWidget(authorLabel, 3, 0);
    bookInfoLayout->addWidget(authorLineEdit, 3, 1);
    bookInfoLayout->addWidget(pagesLabel, 4, 0);
    bookInfoLayout->addWidget(pagesSpinBox, 4, 1);
    bookInfoLayout->addWidget(priceLabel, 5, 0);
    bookInfoLayout->addWidget(priceDoubleSpinBox, 5, 1);
    bookInfoLayout->addWidget(publisherLabel, 6, 0);
    bookInfoLayout->addWidget(publisherLineEdit, 6, 1);
    bookInfoLayout->addWidget(pubdateLabel, 7, 0);
    bookInfoLayout->addWidget(pubdateDateEdit, 7, 1);

    bookInfoGroupBox = new QGroupBox(tr("Book Information"));
    bookInfoGroupBox->setLayout(bookInfoLayout);


    cardNumLabel = new QLabel(tr("&Card Number:"));
    cardNumLineEdit = new QLineEdit;
    cardNumLineEdit->setEnabled(false);
    cardNumLabel->setBuddy(cardNumLineEdit);
    IDLabel = new QLabel(tr("&ID:"));
    IDLineEdit = new QLineEdit;
    IDLineEdit->setEnabled(false);
    IDLabel->setBuddy(IDLineEdit);
    nameLabel = new QLabel(tr("&Name:"));
    nameLineEdit = new QLineEdit;
    nameLineEdit->setEnabled(false);
    nameLabel->setBuddy(nameLineEdit);
    sexLabel = new QLabel(tr("&Sex:"));
    sexComboBox = new QComboBox;
    sexComboBox->setEnabled(false);
    sexComboBox->addItems(QStringList() << tr("male") << tr("female"));
    sexLabel->setBuddy(sexComboBox);
    birthdayLabel = new QLabel(tr("&Birthday:"));
    birthdayDateEdit = new QDateEdit;
    birthdayDateEdit->setEnabled(false);
    birthdayLabel->setBuddy(birthdayDateEdit);
    cardDateLabel = new QLabel(tr("&Card Date:"));
    cardDateEdit = new QDateEdit;
    cardDateEdit->setEnabled(false);
    cardDateLabel->setBuddy(cardDateEdit);
    IDCardLabel = new QLabel(tr("&ID Card:"));
    IDCardLineEdit = new QLineEdit;
    IDCardLineEdit->setEnabled(false);
    IDCardLabel->setBuddy(IDCardLineEdit);
    phoneLabel = new QLabel(tr("&Phone:"));
    phoneLineEdit = new QLineEdit;
    phoneLineEdit->setEnabled(false);
    phoneLabel->setBuddy(phoneLineEdit);

    QGridLayout *readerInfoLayout = new QGridLayout;
    readerInfoLayout->addWidget(cardNumLabel, 0, 0);
    readerInfoLayout->addWidget(cardNumLineEdit, 0, 1);
    readerInfoLayout->addWidget(IDLabel, 1, 0);
    readerInfoLayout->addWidget(IDLineEdit, 1, 1);
    readerInfoLayout->addWidget(nameLabel, 2, 0);
    readerInfoLayout->addWidget(nameLineEdit, 2, 1);
    readerInfoLayout->addWidget(sexLabel, 3, 0);
    readerInfoLayout->addWidget(sexComboBox, 3, 1);
    readerInfoLayout->addWidget(birthdayLabel, 4, 0);
    readerInfoLayout->addWidget(birthdayDateEdit, 4, 1);
    readerInfoLayout->addWidget(cardDateLabel, 5, 0);
    readerInfoLayout->addWidget(cardDateEdit, 5, 1);
    readerInfoLayout->addWidget(IDCardLabel, 6, 0);
    readerInfoLayout->addWidget(IDCardLineEdit, 6, 1);
    readerInfoLayout->addWidget(phoneLabel, 7, 0);
    readerInfoLayout->addWidget(phoneLineEdit, 7, 1);

    readerGroupBox = new QGroupBox(tr("Reader Information"));
    readerGroupBox->setLayout(readerInfoLayout);
    readerGroupBox->setVisible(false);

    okButton = new QPushButton(tr("OK"));
    cancelButton = new QPushButton(tr("Cancel"));

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(okButton);
    bottomLayout->addWidget(cancelButton);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(toplayout);
    mainLayout->addWidget(readerGroupBox);
    mainLayout->addWidget(bookInfoGroupBox);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);

    initBookInfo(num);

    connect(queryButton, SIGNAL(clicked()), this, SLOT(queryClicked()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void BorrowBookInfoDialog::initBookInfo(const QString &num)
{
    QString sql = "select * from book where num='" + num + "'";

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);
    if (query.next())
    {
        QString bookNum = query.value(0).toString();
        bookNumLineEdit->setText(bookNum);

        QString ISBN = query.value(1).toString();
        ISBNLineEdit->setText(ISBN);

        QString bookName = query.value(2).toString();
        bookNameLineEdit->setText(bookName);

        QString author = query.value(3).toString();
        authorLineEdit->setText(author);

        int pages = query.value(4).toInt();
        pagesSpinBox->setValue(pages);

        double price = query.value(5).toDouble();
        priceDoubleSpinBox->setValue(price);

        QString publisher = query.value(6).toString();
        publisherLineEdit->setText(publisher);

        QDate pubdate = query.value(7).toDate();
        pubdateDateEdit->setDate(pubdate);

    }
}

void BorrowBookInfoDialog::queryClicked()
{
    int index = comboBox->currentIndex();
    QString str;
    switch (index)
    {
    case 0 :
        str = "card_num";
        break;
    case 1 :
        str = "ID";
        break;
    default :
        str = "ID_card";
    }

    QString name = lineEdit->text();

    QString sql = tr("select * from reader where %1='%2'").arg(str).arg(name);

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

    if (query.next())
    {
        QString cardNum = query.value(0).toString();
        cardNumLineEdit->setText(cardNum);

        QString ID = query.value(1).toString();
        IDLineEdit->setText(ID);

        QString name = query.value(2).toString();
        nameLineEdit->setText(name);

        QString sex = query.value(3).toString();
        bool b = sex.compare(QString::fromLocal8Bit("ÄÐ"));
        sexComboBox->setCurrentIndex(b);

        QDate birthday = query.value(4).toDate();
        birthdayDateEdit->setDate(birthday);

        QDate cardDate = query.value(5).toDate();
        cardDateEdit->setDate(cardDate);

        QString IDCard = query.value(7).toString();
        IDCardLineEdit->setText(IDCard);

        QString phone = query.value(8).toString();
        phoneLineEdit->setText(phone);

        readerGroupBox->setVisible(true);
    }
    else
    {
        QMessageBox::information(this, tr("Error"), tr("No Information."));

//        readerGroupBox->setVisible(false);
    }
}

void BorrowBookInfoDialog::okButtonClicked()
{
    QString cardNum = cardNumLineEdit->text();
    if (cardNum.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("No Card Number."));
        return;
    }
    QString bookNum = bookNumLineEdit->text();
    QString ISBN = ISBNLineEdit->text();


    QString sql = "select valid_date,state,type from reader where card_num='" + cardNum + "'";
    QDate date = QDate::currentDate();
    QString type;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

    if (query.next())
    {
        QDate validDate = query.value(0).toDate();
//        qDebug() << validDate << date;
        if (validDate < date)
        {
            QMessageBox::information(this, tr("Error"), tr("The reader Certificate expired."));
            return;
        }
        QString state = query.value(1).toString();
        if (state != QString::fromLocal8Bit("ÆÕÍ¨"))
        {
            QMessageBox::information(this, tr("Error"), tr("The reader has logout."));
            return;
        }
        QString temp = query.value(2).toString();
        if (temp == "VIP")
        {
            type = "VIP_lend_book_max";
        }
        else
        {
            type = "reader_lend_book_max";
        }

    }

    sql = "select count(*) from borrow_book where reader_card_num='" + cardNum +
            "' and return_date is NULL";

    query = db.exec(sql);
    if (!query.isActive())
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
        return;
    }

    int count = 0;
    if (query.next())
    {
        count = query.value(0).toInt();
    }

    sql = "select " + type + ",lend_book_date from library_info";
    query = db.exec(sql);
    int addDate = 30;
    if (query.next())
    {
        int maxCount = query.value(0).toInt();
        if (count >= maxCount)
        {
            QMessageBox::information(this, tr("Error"), tr("Loan amount more than limit."));
            return;
        }
        addDate = query.value(1).toInt();
    }

    sql = "insert into borrow_book(book_num,book_ISBN,reader_card_num,lend_date,should_return_date,renew_count) values('"
            + bookNum + "','" + ISBN + "','" + cardNum + "','" + date.toString(Qt::ISODate) + "','"
            + date.addDays(addDate).toString(Qt::ISODate) + "','0')";

    query = db.exec(sql);

//    sql = "update book_circulate set send_num=send_num+1,send_count=send_count+1 where ISBN='" + ISBN + "'";
//    query = db.exec(sql);

    if (query.isActive())
    {
        sql = "update book set state='0' where num='" + bookNum + "'";
        db.exec(sql);

        sql = "insert into book_log_info(ID,book_ISBN,operation,operation_date) values('"
                + user_name + "','" + ISBN + "','borrow','" + QDateTime::currentDateTime().toString(Qt::ISODate)
                + "')";

        query = db.exec(sql);

        QMessageBox::information(this, tr("Succeed"), tr("Borrow Book Succees."));
        QDialog::accept();

    }
    else
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
    }
}
