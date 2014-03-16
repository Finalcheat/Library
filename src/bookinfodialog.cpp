#include "bookinfodialog.h"
#include <QDateEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDebug>
#include <QtXml>
#include <QRegExp>
#include <QRegExpValidator>

BookInfoDialog::BookInfoDialog(const QString &u, const QString &num, QWidget *parent) :
    QDialog(parent), str(num), user_name(u)
{
    ISBNLabel = new QLabel(tr("ISB&N:"));
    ISBNLineEdit = new QLineEdit;
    ISBNLabel->setBuddy(ISBNLineEdit);
    ISBNButton = new QPushButton(tr("Get Information"));
    ISBNButton->setEnabled(!str.isEmpty());

    bookNameLabel = new QLabel(tr("Book Nam&e:"));
    bookNameLineEdit = new QLineEdit;
    bookNameLabel->setBuddy(bookNameLineEdit);

    authorLabel = new QLabel(tr("Aut&hor:"));
    authorLineEdit = new QLineEdit;
    authorLabel->setBuddy(authorLineEdit);

    pagesLabel = new QLabel(tr("P&ages:"));
    pagesSpinBox = new QSpinBox;
    pagesSpinBox->setMaximum(1000000);
    pagesLabel->setBuddy(pagesSpinBox);

    priceLabel = new QLabel(tr("&Price:"));
    priceDoubleSpinBox = new QDoubleSpinBox;
    priceDoubleSpinBox->setMaximum(100000.00);
    priceLabel->setBuddy(priceDoubleSpinBox);

    publisherLabel = new QLabel(tr("P&ublisher:"));
    publisherLineEdit = new QLineEdit;
    publisherLabel->setBuddy(publisherLineEdit);

    pubdateLabel = new QLabel(tr("&Pubdate:"));
    pubdateDateEdit = new QDateEdit;
    QDate date = QDate::currentDate();
    pubdateDateEdit->setDate(date);
    pubdateLabel->setBuddy(pubdateDateEdit);

    summaryLabel = new QLabel(tr("&Summary:"));
    summaryTextEdit = new QTextEdit;
    summaryLabel->setBuddy(summaryTextEdit);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(ISBNLabel, 0, 0);
    gridLayout->addWidget(ISBNLineEdit, 0, 1);
    gridLayout->addWidget(ISBNButton, 0, 2);
    gridLayout->addWidget(bookNameLabel, 1, 0);
    gridLayout->addWidget(bookNameLineEdit, 1, 1);
    gridLayout->addWidget(authorLabel, 2, 0);
    gridLayout->addWidget(authorLineEdit, 2, 1);
    gridLayout->addWidget(pagesLabel, 3, 0);
    gridLayout->addWidget(pagesSpinBox, 3, 1);
    gridLayout->addWidget(priceLabel, 4, 0);
    gridLayout->addWidget(priceDoubleSpinBox, 4, 1);
    gridLayout->addWidget(publisherLabel, 5, 0);
    gridLayout->addWidget(publisherLineEdit, 5, 1);
    gridLayout->addWidget(pubdateLabel, 6, 0);
    gridLayout->addWidget(pubdateDateEdit, 6, 1);
    gridLayout->addWidget(summaryLabel, 7, 0, Qt::AlignTop);
    gridLayout->addWidget(summaryTextEdit, 7, 1);

    groupBox = new QGroupBox(tr("Book Information"));
    groupBox->setLayout(gridLayout);


    okButton = new QPushButton(tr("Ok&"));
    okButton->setEnabled(!str.isEmpty());
    cancelButton = new QPushButton(tr("Canc&el"));

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
        connect(okButton, SIGNAL(clicked()), this, SLOT(okClicked()));
    }
    else
    {
        init();
        connect(okButton, SIGNAL(clicked()), this, SLOT(modifyClicked()));
    }

    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ISBNButton, SIGNAL(clicked()), this, SLOT(getBookInfo()));
    connect(&getInfo, SIGNAL(done(QString)), this, SLOT(httpDone(QString)));


    QRegExp regExp("[0-9]{13}");
    ISBNLineEdit->setValidator(new QRegExpValidator(regExp, this));

    connect(ISBNLineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChanged()));
}

void BookInfoDialog::textChanged()
{
    ISBNButton->setEnabled(ISBNLineEdit->hasAcceptableInput());
    okButton->setEnabled(ISBNLineEdit->hasAcceptableInput());
}

void BookInfoDialog::okClicked()
{
    QString ISBN = ISBNLineEdit->text();
    QString bookName = bookNameLineEdit->text();
    QString author = authorLineEdit->text();
    int pages = pagesSpinBox->value();
    double price = priceDoubleSpinBox->value();
    QString publisher = publisherLineEdit->text();
    QString pubdate = pubdateDateEdit->date().toString(Qt::ISODate);
    QString summary = summaryTextEdit->toPlainText();

//    qDebug() << ISBN << bookName << author << pages << price
//                << publisher << pubdate << summary;

    QString sql = "insert into book values('" + ISBN + "','" + bookName + "','"
            + author + "','" + QString::number(pages) + "','" + QString::number(price) + "','" + publisher + "','"
            + pubdate + "','" + summary + "','1')";

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

    sql = "insert into book_log_info(ID,book_ISBN,operation,operation_date) values('"
            + user_name + "','" + ISBN + "','add','" + QDateTime::currentDateTime().toString(Qt::ISODate)
            + "')";

    query = db.exec(sql);

    if (query.isActive())
    {
        QMessageBox::information(this, tr("Succeed"), tr("Add data succeed."));
        ISBNLineEdit->clear();
        bookNameLineEdit->clear();
        authorLineEdit->clear();
        pagesSpinBox->setValue(0);
        priceDoubleSpinBox->setValue(0);
        publisherLineEdit->clear();
        QDate date = QDate::currentDate();
        pubdateDateEdit->setDate(date);
        summaryTextEdit->clear();
    }
    else
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
    }
}

void BookInfoDialog::init()
{
    QString sql = "select * from book where num='" + str + "'";
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);
    if (query.next())
    {
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
//        qDebug() << pubdate;
        pubdateDateEdit->setDate(pubdate);

        QString summary = query.value(8).toString();
        summaryTextEdit->setPlainText(summary);
    }
}

void BookInfoDialog::modifyClicked()
{
    QString ISBN = ISBNLineEdit->text();
    QString bookName = bookNameLineEdit->text();
    QString author = authorLineEdit->text();
    int pages = pagesSpinBox->value();
    double price = priceDoubleSpinBox->value();
    QString publisher = publisherLineEdit->text();
    QString pubdate = pubdateDateEdit->date().toString(Qt::ISODate);
    QString summary = summaryTextEdit->toPlainText();

    QString sql = "update book set ISBN='" + ISBN + "', book_name='" + bookName
            + "', author='" + author + "', pages='" + QString::number(pages) + "', price='"
            + QString::number(price) + "', publisher='" + publisher + "', pubdate='"
            + pubdate + "', summary='" + summary + "' where num='" + str + "'";

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

    sql = "insert into book_log_info(ID,book_ISBN,operation,operation_date) values('"
            + user_name + "','" + ISBN + "','update','" + QDateTime::currentDateTime().toString(Qt::ISODate)
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

void BookInfoDialog::getBookInfo()
{
    QString isbn = ISBNLineEdit->text();

    if (isbn.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Please input ISBN."));
        return;
    }

    getInfo.getFile(QUrl("http://api.douban.com/book/subject/isbn/" + isbn));
}

void BookInfoDialog::httpDone(const QString &fileName)
{

    QFile xmlFile(fileName);
    xmlFile.open(QIODevice::ReadOnly);
    QXmlStreamReader xmlReader(xmlFile.readAll());


    QString author;
    QDate date;
    QString tempDate;
    QString pages;
    QString price;
    while (!xmlReader.atEnd())
    {
        if (xmlReader.isStartElement())
        {
            if (xmlReader.name() == "title")
            {
                bookNameLineEdit->setText(xmlReader.readElementText());
            }
            else if (xmlReader.name() == "summary")
            {
                summaryTextEdit->setText(xmlReader.readElementText());
            }
            else if (xmlReader.name() == "attribute")
            {
                QStringRef str = xmlReader.attributes().at(0).value();
                if (str == "isbn13")
                    ISBNLineEdit->setText(xmlReader.readElementText());
                else if (str == "pages")
                    pages = xmlReader.readElementText();
                else if (str == "author")
                {
                    if (author.isEmpty())
                        author = xmlReader.readElementText();
                    else
                        author = author + " " + xmlReader.readElementText();
                }
                else if (str == "price")
                {
//                    qDebug() << xmlReader.readElementText();
                    price = xmlReader.readElementText();
                }
                else if (str == "publisher")
                    publisherLineEdit->setText(xmlReader.readElementText());
                else if (str == "pubdate")
                    tempDate = xmlReader.readElementText();

            }
        }
        else if(xmlReader.isEndElement())
        {
            xmlReader.readNext();
        }
        xmlReader.readNext();
    }

    int begin = price.indexOf(QRegExp("\\d"));
    int end = price.lastIndexOf(QRegExp("\\d"));
    QString trPrice = price.mid(begin, end - begin + 1);

    priceDoubleSpinBox->setValue(trPrice.toDouble());

    begin = pages.indexOf(QRegExp("\\d"));
    end = pages.lastIndexOf(QRegExp("\\d"));
    QString trPages = pages.mid(begin, end - begin + 1);

    pagesSpinBox->setValue(trPages.toInt());

//    qDebug() << tempDate;

    QStringList str = tempDate.split("-");
    if (str.size() == 1)
    {
        date.setDate(str[0].toInt(), 1, 1);
    }
    else if (str.size() == 2)
    {
        date.setDate(str[0].toInt(), str[1].toInt(), 1);
    }
    else
    {
        date.setDate(str[0].toInt(), str[1].toInt(), str[2].toInt());
    }

//    date = QDate::fromString(tempDate, Qt::ISODate);
    authorLineEdit->setText(author);
    pubdateDateEdit->setDate(date);
}
