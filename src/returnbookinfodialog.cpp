#include "returnbookinfodialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QGroupBox>
#include <QDateEdit>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

ReturnBookInfoDialog::ReturnBookInfoDialog(const QString &u, const QString &n, const QString &bookNum, const QString &ID, bool renew, QWidget *parent) :
    QDialog(parent), num(n), user_name(u)
{
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

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(bookInfoGroupBox);
    topLayout->addWidget(readerGroupBox);

    okButton = new QPushButton(tr("O&K"));
    cancelButton = new QPushButton(tr("Cancel"));

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    if (!renew)
    {
        stateLabel = new QLabel(tr("&State:"));
        stateComboBox = new QComboBox;
        stateComboBox->addItems(QStringList() << tr("normal") << tr("damage") << tr("lose"));
        stateLabel->setBuddy(stateComboBox);
        bottomLayout->addWidget(stateLabel);
        bottomLayout->addWidget(stateComboBox);
    }
    bottomLayout->addStretch();
    bottomLayout->addWidget(okButton);
    bottomLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);

    initBookInfo(bookNum);
    initReaderInfo(ID);

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    if (renew)
    {
        connect(okButton, SIGNAL(clicked()), this, SLOT(renewClicked()));
    }
    else
    {
        connect(okButton, SIGNAL(clicked()), this, SLOT(okButtonClicked()));
    }
}

void ReturnBookInfoDialog::initBookInfo(const QString &bookNum)
{
    QString sql = "select book.ISBN,book.book_name,book.author,book.pages,book.price,book.publisher,book.pubdate "
            "from book,borrow_book where borrow_book.book_num=book.num and book.num='"
            + bookNum + "'";

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);
    if (query.next())
    {
        bookNumLineEdit->setText(bookNum);

        QString ISBN = query.value(0).toString();
        ISBNLineEdit->setText(ISBN);

        QString bookName = query.value(1).toString();
        bookNameLineEdit->setText(bookName);

        QString author = query.value(2).toString();
        authorLineEdit->setText(author);

        int pages = query.value(3).toInt();
        pagesSpinBox->setValue(pages);

        double price = query.value(4).toDouble();
        priceDoubleSpinBox->setValue(price);

        QString publisher = query.value(5).toString();
        publisherLineEdit->setText(publisher);

        QDate date = query.value(6).toDate();
        pubdateDateEdit->setDate(date);
    }
}

void ReturnBookInfoDialog::initReaderInfo(const QString &ID)
{
    QString sql = "select reader.card_num,reader.user_name,reader.sex,reader.birthday,reader.card_date,reader.ID_card,reader.phone "
            "from reader,borrow_book where borrow_book.reader_card_num=reader.card_num and reader.ID='"
            + ID + "'";

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);
    if (query.next())
    {
        QString cardNum = query.value(0).toString();
        cardNumLineEdit->setText(cardNum);

        IDLineEdit->setText(ID);

        QString userName = query.value(1).toString();
        nameLineEdit->setText(userName);

        QString sex = query.value(2).toString();
        bool b = sex.compare(QString::fromLocal8Bit("ÄÐ"));
        sexComboBox->setCurrentIndex(b);

        QDate birthday = query.value(3).toDate();
        birthdayDateEdit->setDate(birthday);

        QDate cardDate = query.value(4).toDate();
        cardDateEdit->setDate(cardDate);

        QString IDCard = query.value(5).toString();
        IDCardLineEdit->setText(IDCard);

        QString phone = query.value(6).toString();
        phoneLineEdit->setText(phone);
    }
}

void ReturnBookInfoDialog::okButtonClicked()
{
    QString ISBN = ISBNLineEdit->text();
    if (ISBN.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("ISBN information Error."));
        return;
    }

    int index = stateComboBox->currentIndex();

    switch (index)
    {
    case 0 :
        normalClicked();
        break;
    case 1 :
        damageClicked();
        break;
    default :
        loseClicked();
    }
}

void ReturnBookInfoDialog::loseClicked()
{
    if (!exceedTime())
        return;

    loseBook();
    QSqlDatabase db = QSqlDatabase::database();
    db.commit();
}

void ReturnBookInfoDialog::damageClicked()
{
    if (!exceedTime())
        return;

    QSqlDatabase db = QSqlDatabase::database();
    if (!damage())
    {
        db.rollback();
        return;
    }

    returnBook();

    db.commit();
}

void ReturnBookInfoDialog::normalClicked()
{
    if (!exceedTime())
        return;

    returnBook();

    QSqlDatabase db = QSqlDatabase::database();
    db.commit();
}

void ReturnBookInfoDialog::renewClicked()
{
//    QString cardNum = cardNumLineEdit->text();

    QString readerNum = cardNumLineEdit->text();
    if (readerNum.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Information Error."));
        return;
    }

    QString sql = "select reader.type,borrow_book.renew_count from reader,borrow_book "
            "where borrow_book.num='" + num + "' and reader.card_num='" + readerNum + "'";

    QSqlDatabase db = QSqlDatabase::database();

    QSqlQuery query = db.exec(sql);
    QString type = "reader_renew_book_max";
    int renewCount = 0;
    if (query.isActive())
    {
        if (query.next())
        {
            QString temp = query.value(0).toString();
            if (temp == "VIP")
            {
                type = "VIP_renew_book_max";
            }

            renewCount = query.value(1).toInt();
        }
    }
    else
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
        return;
    }

    sql = "select " + type + ",lend_book_date from library_info";
    query = db.exec(sql);
    int maxCount = 1;
    int addDate = 30;
    if (query.next())
    {
        maxCount = query.value(0).toInt();
        addDate = query.value(1).toInt();
    }
    else
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
        return;
    }

    if (renewCount >= maxCount)
    {
        QMessageBox::information(this, tr("Error"), tr("Renew More than limit"));
        return;
    }

    sql = "update borrow_book set renew_count=renew_count+1,should_return_date=DATEADD(day," +
            QString::number(addDate) + ",should_return_date) where num='" + num + "'";


    query = db.exec(sql);

    if (query.isActive())
    {
        QString ISBN = ISBNLineEdit->text();
        sql = "insert into book_log_info(ID,book_ISBN,operation,operation_date) values('"
                + user_name + "','" + ISBN + "','renew','" + QDateTime::currentDateTime().toString(Qt::ISODate)
                + "')";

        query = db.exec(sql);

        QMessageBox::information(this, tr("Succeed"), tr("Renew Book Succeed."));
        QDialog::accept();
    }
    else
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
    }
}

void ReturnBookInfoDialog::returnBook()
{
//    QString cardNum = cardNumLineEdit->text();
    QDate date = QDate::currentDate();

    QString sql = "update borrow_book set return_date='" + date.toString(Qt::ISODate)
            + "' where num='" + num + "'";

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

    if (query.isActive())
    {
        QString bookNum = bookNumLineEdit->text();
        sql = "update book set state='1' where num='" + bookNum + "'";
        db.exec(sql);

        QString ISBN = ISBNLineEdit->text();
        sql = "insert into book_log_info(ID,book_ISBN,operation,operation_date) values('"
                + user_name + "','" + ISBN + "','return','" + QDateTime::currentDateTime().toString(Qt::ISODate)
                + "')";

        query = db.exec(sql);

        QMessageBox::information(this, tr("Succeed"), tr("Return Book Succeed."));
        QDialog::accept();
    }
    else
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
    }
}

bool ReturnBookInfoDialog::exceedTime()
{
    QString ISBN = ISBNLineEdit->text();
//    QString cardNum = cardNumLineEdit->text();

    QString sql = "select borrow_book.lend_date,borrow_book.renew_count from borrow_book "
            "where num='" + num + "'";
    QSqlDatabase db = QSqlDatabase::database();
    db.transaction();
    QSqlQuery query = db.exec(sql);

    QDate lendDate;
    int renewCount = 0;
    if (query.next())
    {
        lendDate = query.value(0).toDate();
        renewCount = query.value(1).toInt();
    }

    sql = "select lend_book_date,date_money from library_info";
    query = db.exec(sql);
    int lendBookDate = 30;
    double dateMoney = 0.1;
    if (query.next())
    {
        lendBookDate = query.value(0).toInt();
        dateMoney = query.value(1).toDouble();
    }

    QDate shouldReturnDate = lendDate.addDays((renewCount + 1) * lendBookDate);
    QDate currentDate = QDate::currentDate();
//    qDebug() << shouldReturnDate << currentDate;
    int day = shouldReturnDate.daysTo(currentDate);
//    qDebug() << day;
    if (day > 0)
    {
        double money = day * dateMoney;

        int r = QMessageBox::warning(this, tr("Fine"),
                                             tr("exceed fine money %1?").arg(QString::number(money)),
                                             QMessageBox::Yes | QMessageBox::Default,
                                             QMessageBox::No,
                                             QMessageBox::Cancel | QMessageBox::Escape);

        if (r == QMessageBox::No || r == QMessageBox::Cancel)
        {
            QMessageBox::information(this, tr("Error"), tr("Return Book fail."));
            return false;
        }

        QString ID = IDLineEdit->text();
        sql = "insert into fine_info values('" + ISBN + "','" + ID + "','"
                + currentDate.toString(Qt::ISODate) + "','" + QString::number(money)
                + "','overdue')";
        query = db.exec(sql);
        if (!query.isActive())
        {
            QMessageBox::information(this, tr("Error"), query.lastError().text());
            return false;
        }
    }

    return true;
}

bool ReturnBookInfoDialog::damage()
{
    QString bookNum = bookNumLineEdit->text();
    QString ISBN = ISBNLineEdit->text();
    QString ID = IDLineEdit->text();
    QString sql = "select damage_money from library_info";
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);
    double count = 0.1;
    if (query.next())
    {
        count = query.value(0).toDouble();
    }

    sql = "select price from book where num=" + bookNum;
    double money = 10;
    query = db.exec(sql);
    if (query.next())
    {
        money = query.value(0).toDouble() * count;
    }

    int r = QMessageBox::warning(this, tr("Fine"),
                                         tr("damage fine money %1?").arg(QString::number(money)),
                                         QMessageBox::Yes | QMessageBox::Default,
                                         QMessageBox::No,
                                         QMessageBox::Cancel | QMessageBox::Escape);

    if (r == QMessageBox::No || r == QMessageBox::Cancel)
    {
        QMessageBox::information(this, tr("Error"), tr("Return Book fail."));
        return false;
    }

    sql = "insert into fine_info values('" + ISBN + "','" + ID + "','"
            + QDate::currentDate().toString(Qt::ISODate) + "','" + QString::number(money)
            + "','damage')";

    query = db.exec(sql);
    if (!query.isActive())
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
        return false;
    }

    return true;
}

void ReturnBookInfoDialog::loseBook()
{
    QString bookNum = bookNumLineEdit->text();
    QString ISBN = ISBNLineEdit->text();
    QString ID = IDLineEdit->text();
    QString sql = "select price from book where num=" + bookNum;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);
    double money = 10.0;
    if (query.next())
    {
        money = query.value(0).toDouble();
    }

    int r = QMessageBox::warning(this, tr("Fine"),
                                         tr("lose fine money %1?").arg(QString::number(money)),
                                         QMessageBox::Yes | QMessageBox::Default,
                                         QMessageBox::No,
                                         QMessageBox::Cancel | QMessageBox::Escape);

    if (r == QMessageBox::No || r == QMessageBox::Cancel)
    {
        QMessageBox::information(this, tr("Error"), tr("Return Book fail."));
        return;
    }

    sql = "update borrow_book set return_date='" + QDate::currentDate().toString(Qt::ISODate)
                + "' where num='" + num + "'";

    db.exec(sql);

    sql = "update book set state='2' where num='" + bookNum + "'";

    db.exec(sql);

    sql = "insert into fine_info values('" + ISBN + "','" + ID + "','"
            + QDate::currentDate().toString(Qt::ISODate) + "','" + QString::number(money)
            + "','lose')";

    query = db.exec(sql);

    if (query.isActive())
    {
        QMessageBox::information(this, tr("Succeed"), tr("Return Book Succeed."));
        QDialog::accept();
    }
    else
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
    }
}
