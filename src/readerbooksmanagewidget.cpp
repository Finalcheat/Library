#include "readerbooksmanagewidget.h"
#include "returnbookinfodialog.h"
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QLabel>
#include <QTextDocument>
#include <QLineEdit>
#include <QString>

ReaderBooksManageWidget::ReaderBooksManageWidget(const QString &u, bool b, QWidget *parent) :
    QWidget(parent), user_name(u)
{
    typeComboBox = new QComboBox;
    typeComboBox->addItems(QStringList() << tr("Not return books") << tr("Has return books") << tr("All"));
    startLabel = new QLabel(tr("&Start time:"));
    startDateEdit = new QDateEdit;
    startLabel->setBuddy(startDateEdit);
    endLabel = new QLabel(tr("&End time:"));
    endDateEdit = new QDateEdit;
    endLabel->setBuddy(endDateEdit);
    queryButton = new QPushButton(tr("Query"));

    renewButton = new QPushButton(tr("Renew"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(typeComboBox);
    topLayout->addWidget(startLabel);
    topLayout->addWidget(startDateEdit);
    topLayout->addWidget(endLabel);
    topLayout->addWidget(endDateEdit);
    if (b)
    {
        IDLabel = new QLabel(tr("&ID:"));
        IDLineEdit = new QLineEdit;
        IDLabel->setBuddy(IDLineEdit);
        topLayout->addWidget(IDLabel);
        topLayout->addWidget(IDLineEdit);
    }
    topLayout->addWidget(queryButton);
    topLayout->addStretch();
    topLayout->addWidget(renewButton);

    tableView = new QTableView;
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


    model = new QSqlTableModel;

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableView->setModel(model);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(tableView);

    setLayout(mainLayout);

    if (b)
    {
        connect(queryButton, SIGNAL(clicked()), this, SLOT(adminQueryClicked()));
        connect(renewButton, SIGNAL(clicked()), this, SLOT(adminRenewClicked()));
    }
    else
    {
        connect(queryButton, SIGNAL(clicked()), this, SLOT(queryClicked()));
        connect(renewButton, SIGNAL(clicked()), this, SLOT(renewClicked()));
    }
}

void ReaderBooksManageWidget::adminQueryClicked()
{
    int index = typeComboBox->currentIndex();
    QDate startDate = startDateEdit->date();
    QDate endDate = endDateEdit->date();
    QString str;
    if (startDate < endDate)
    {
        str = " and borrow_book.lend_date>'" + startDate.toString(Qt::ISODate) + "' and borrow_book.lend_date<'"
                + endDate.toString(Qt::ISODate) + "'";
    }
    QString sql;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    QString ID = IDLineEdit->text();
    if (index == 0)
    {
        sql = "select borrow_book.num,book.num,book.ISBN,book.book_name,book.author,book.pages,book.price,book.publisher,book.pubdate,"
                "borrow_book.lend_date,borrow_book.should_return_date,borrow_book.renew_count from borrow_book,reader,book where borrow_book.book_num=book.num and "
                "borrow_book.reader_card_num=reader.card_num and reader.ID='" + ID + "' and borrow_book.return_date is NULL" + str;

        query = db.exec(sql);
        if (!query.isActive())
        {
            QMessageBox::information(this, tr("Erro"), query.lastError().text());
            return;
        }

        model->QSqlQueryModel::setQuery(query);
        initModel(false);
    }
    else if (index == 1)
    {
        sql = "select borrow_book.num,book.num,book.ISBN,book.book_name,book.author,book.pages,book.price,"
              "book.publisher,book.pubdate,borrow_book.lend_date,borrow_book.return_date,borrow_book.renew_count "
              "from borrow_book,book,reader where borrow_book.book_num=book.num and borrow_book.reader_card_num="
              "reader.card_num and reader.ID='" + ID + "' and borrow_book.return_date is not NULL" + str;

        query = db.exec(sql);
        if (!query.isActive())
        {
            QMessageBox::information(this, tr("Error"), query.lastError().text());
            return;
        }

        model->QSqlQueryModel::setQuery(query);
        initModel(true);
    }
    else
    {
        sql = "select borrow_book.num,book.num,book.ISBN,book.book_name,book.author,book.pages,book.price,"
              "book.publisher,book.pubdate,borrow_book.lend_date,borrow_book.should_return_date,borrow_book.return_date,"
              "borrow_book.renew_count from borrow_book,book,reader where borrow_book.book_num="
                "book.num and borrow_book.reader_card_num=reader.card_num and reader.ID='" + ID + "'" + str;

        query = db.exec(sql);
        if (!query.isActive())
        {
            QMessageBox::information(this, tr("Error"), query.lastError().text());
            return;
        }

        model->QSqlQueryModel::setQuery(query);
        initAllModel();
    }


    tableView->resizeColumnsToContents();
}

void ReaderBooksManageWidget::queryClicked()
{
    int index = typeComboBox->currentIndex();
    QDate startDate = startDateEdit->date();
    QDate endDate = endDateEdit->date();
    QString str;
    if (startDate < endDate)
    {
        str = " and borrow_book.lend_date>='" + startDate.toString(Qt::ISODate) + "' and borrow_book.lend_date<='"
                + endDate.toString(Qt::ISODate) + "'";
    }
    QString sql;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    if (index == 0)
    {
        sql = "select borrow_book.num,book.num,book.ISBN,book.book_name,book.author,book.pages,book.price,book.publisher,book.pubdate,"
                "borrow_book.lend_date,borrow_book.should_return_date,borrow_book.renew_count from borrow_book,reader,book where borrow_book.book_num=book.num and "
                "borrow_book.reader_card_num=reader.card_num and reader.ID='" + user_name + "' and borrow_book.return_date is NULL" + str;

        query = db.exec(sql);
        if (!query.isActive())
        {
            QMessageBox::information(this, tr("Error"), query.lastError().text());
            return;
        }

        model->QSqlQueryModel::setQuery(query);
        initModel(false);
    }
    else if (index == 1)
    {
        sql = "select borrow_book.num,book.num,book.ISBN,book.book_name,book.author,book.pages,book.price,"
              "book.publisher,book.pubdate,borrow_book.lend_date,borrow_book.return_date,borrow_book.renew_count "
              "from borrow_book,book,reader where borrow_book.book_num=book.num and borrow_book.reader_card_num="
              "reader.card_num and reader.ID='" + user_name + "' and borrow_book.return_date is not NULL" + str;

        query = db.exec(sql);
        if (!query.isActive())
        {
            QMessageBox::information(this, tr("Error"), query.lastError().text());
            return;
        }

        model->QSqlQueryModel::setQuery(query);
        initModel(true);
    }
    else
    {
        sql = "select borrow_book.num,book.num,book.ISBN,book.book_name,book.author,book.pages,book.price,"
              "book.publisher,book.pubdate,borrow_book.lend_date,borrow_book.should_return_date,borrow_book.return_date,"
              "borrow_book.renew_count from borrow_book,book,reader where borrow_book.book_num="
                "book.num and borrow_book.reader_card_num=reader.card_num and reader.ID='" + user_name + "'" + str;

        query = db.exec(sql);
        if (!query.isActive())
        {
            QMessageBox::information(this, tr("Error"), query.lastError().text());
            return;
        }

        model->QSqlQueryModel::setQuery(query);
        initAllModel();
    }

    tableView->resizeColumnsToContents();
}

QString ReaderBooksManageWidget::getModelData()
{
    QString str;
    for (int row = 0; row < model->rowCount(); ++row)
    {
        str += "<tr>";
        for (int column = 0; column < model->columnCount(); ++column)
        {
            str += "<td>";
            str += Qt::escape(model->data(model->index(row, column)).toString());
            str += "</td>";
        }
        str += "</tr>";
    }
    return str;
}

QString ReaderBooksManageWidget::getHeaderDate()
{
    QString str;
    if (model->columnCount())
    {
        str += "<tr>";
        for (int i = 0; i < model->columnCount(); ++i)
        {
            str += "<th>";
            str += Qt::escape(model->headerData(i, Qt::Horizontal).toString());
            str += "</th>";
        }
        str += "</tr>";
    }

    return str;
}

void ReaderBooksManageWidget::adminRenewClicked()
{
    QModelIndexList indexList = tableView->selectionModel()->selectedRows(0);
    if (indexList.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Please select a line"));
        return;
    }

    int row = tableView->selectionModel()->selectedRows(0).begin()->row();
    QString num = model->data(model->index(row, 0)).toString();
    QString sql = "select return_date from borrow_book where num=" + num;

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

    if (query.next())
    {
        if (!query.value(0).isNull())
        {
            QMessageBox::information(this, tr("Error"), tr("The Book has return."));
            return;
        }
    }

    QString ID = IDLineEdit->text();
    QString bookNum = model->data(model->index(row,1)).toString();
    ReturnBookInfoDialog temp(user_name, num, bookNum, ID, true);
    if (temp.exec())
    {
        adminQueryClicked();
    }
}

void ReaderBooksManageWidget::renewClicked()
{
    QModelIndexList indexList = tableView->selectionModel()->selectedRows(0);
    if (indexList.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Please select a line"));
        return;
    }

    int row = tableView->selectionModel()->selectedRows(0).begin()->row();
    QString num = model->data(model->index(row, 0)).toString();
    QString sql = "select return_date from borrow_book where num=" + num;

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

    if (query.next())
    {
        if (!query.value(0).isNull())
        {
            QMessageBox::information(this, tr("Error"), tr("The Book has return."));
            return;
        }
    }

//    QString num = model->data(model->index(row, 0)).toString();
    QString bookNum = model->data(model->index(row,1)).toString();
    ReturnBookInfoDialog temp(user_name, num, bookNum, user_name, true);
    if (temp.exec())
    {
        queryClicked();
    }
}

void ReaderBooksManageWidget::initModel(bool b)
{
    model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("借书编号"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("图书编号"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("ISBN"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("图书名字"));
    model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("作者"));
    model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("页数"));
    model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("价格"));
    model->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("出版社"));
    model->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("出版时间"));
    model->setHeaderData(9, Qt::Horizontal, QString::fromLocal8Bit("借出时间"));
    if (b)
    {
        model->setHeaderData(10, Qt::Horizontal, QString::fromLocal8Bit("实际归还时间"));
    }
    else
    {
        model->setHeaderData(10, Qt::Horizontal, QString::fromLocal8Bit("应该归还时间"));
    }
    model->setHeaderData(11, Qt::Horizontal, QString::fromLocal8Bit("续借次数"));
}

void ReaderBooksManageWidget::initAllModel()
{
    model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("借书编号"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("图书编号"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("ISBN"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("图书名字"));
    model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("作者"));
    model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("页数"));
    model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("价格"));
    model->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("出版社"));
    model->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("出版时间"));
    model->setHeaderData(9, Qt::Horizontal, QString::fromLocal8Bit("借出时间"));
    model->setHeaderData(10, Qt::Horizontal, QString::fromLocal8Bit("应该归还时间"));
    model->setHeaderData(11, Qt::Horizontal, QString::fromLocal8Bit("实际归还时间"));
    model->setHeaderData(12, Qt::Horizontal, QString::fromLocal8Bit("续借次数"));
}
