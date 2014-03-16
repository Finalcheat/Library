#include "returnbookswidget.h"
#include "returnbookinfodialog.h"
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QSqlTableModel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTextDocument>

ReturnBooksWidget::ReturnBooksWidget(const QString &u, QWidget *parent) :
    QWidget(parent), user_name(u)
{
    bookInfoComboBox = new QComboBox;
    bookInfoComboBox->addItems(QStringList() << tr("num") << tr("ISBN") << tr("book_name") << tr("author") << tr("pages")
                       << tr("price") << tr("publisher") << tr("pubdate") << tr("summary"));
    bookInfoLineEdit = new QLineEdit;

    readerInfoComboBox = new QComboBox;
    readerInfoComboBox->addItems(QStringList() << tr("card_num") << tr("ID") << tr("user_name") << tr("sex")
                                 << tr("birthday") << tr("card_date") << tr("ID_card") << tr("phone")
                                 << tr("state") << tr("type"));
    readerLineEdit = new QLineEdit;

    typeComboBox = new QComboBox;
    typeComboBox->addItems(QStringList() << tr("exact") << tr("vague"));
    queryButton = new QPushButton(tr("Query"));

    returnButton = new QPushButton(tr("Return Book"));
    displayButton = new QPushButton(tr("Display All"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(bookInfoComboBox);
    topLayout->addWidget(bookInfoLineEdit);
    topLayout->addWidget(readerInfoComboBox);
    topLayout->addWidget(readerLineEdit);
    topLayout->addWidget(typeComboBox);
    topLayout->addWidget(queryButton);
    topLayout->addStretch();
    topLayout->addWidget(returnButton);
    topLayout->addWidget(displayButton);

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

    connect(displayButton, SIGNAL(clicked()), this, SLOT(displayClicked()));
    connect(queryButton, SIGNAL(clicked()), this, SLOT(queryClicked()));
    connect(returnButton, SIGNAL(clicked()), this, SLOT(returnClicked()));
}

void ReturnBooksWidget::displayClicked()
{
    model->setTable("borrow_view");
    initModel();
    model->select();
    tableView->resizeColumnsToContents();
}

void ReturnBooksWidget::initModel()
{
    model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("借书编号"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("图书编号"));
    model->setHeaderData(2, Qt::Horizontal, "ISBN");
    model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("书名"));
    model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("作者"));
    model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("页数"));
    model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("价格"));
    model->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("出版社"));
    model->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("出版日期"));
    model->setHeaderData(9, Qt::Horizontal, QString::fromLocal8Bit("读者ID"));
    model->setHeaderData(10, Qt::Horizontal, QString::fromLocal8Bit("读者姓名"));
    model->setHeaderData(11, Qt::Horizontal, QString::fromLocal8Bit("读者性别"));
    model->setHeaderData(12, Qt::Horizontal, QString::fromLocal8Bit("读者身份证号"));
    model->setHeaderData(13, Qt::Horizontal, QString::fromLocal8Bit("读者电话号码"));
    model->setHeaderData(14, Qt::Horizontal, QString::fromLocal8Bit("借出日期"));
    model->setHeaderData(15, Qt::Horizontal, QString::fromLocal8Bit("应还日期"));
    model->setHeaderData(16, Qt::Horizontal, QString::fromLocal8Bit("续借次数"));
}

void ReturnBooksWidget::queryClicked()
{
    QString bookInfo = bookInfoLineEdit->text();
    QString readerInfo = readerLineEdit->text();

    if (bookInfo.isEmpty() && readerInfo.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Information Empty!"));
        return;
    }

    int index = bookInfoComboBox->currentIndex();
    QString bookStr;
    switch (index)
    {
    case 0 :
        bookStr = "num";
        break;
    case 1 :
        bookStr = "ISBN";
        break;
    case 2 :
        bookStr = "book_name";
        break;
    case 3 :
        bookStr = "author";
        break;
    case 4 :
        bookStr = "pages";
        break;
    case 5 :
        bookStr = "price";
        break;
    case 6 :
        bookStr = "publisher";
        break;
    case 7 :
        bookStr = "pubdate";
        break;
    default :
        bookStr = "summary";
    }


    index = readerInfoComboBox->currentIndex();
    QString readerStr;
    switch (index)
    {
    case 0 :
        readerStr = "card_num";
        break;
    case 1 :
        readerStr = "ID";
        break;
    case 2 :
        readerStr = "user_name";
        break;
    case 3 :
        readerStr = "sex";
        break;
    case 4 :
        readerStr = "birthday";
        break;
    case 5 :
        readerStr = "card_date";
        break;
    case 6 :
        readerStr = "ID_card";
        break;
    case 7 :
        readerStr = "phone";
        break;
    case 8 :
        readerStr = "state";
        break;
    default :
        readerStr = "type";
    }

    int type = typeComboBox->currentIndex();
    if (type)
    {
        bookInfo = "%" + bookInfo + "%";
        readerInfo = "%" + readerInfo + "%";
    }
    else
    {
        if (bookInfo.isEmpty())
            bookInfo = "%";

        if (readerInfo.isEmpty())
            readerInfo = "%";
    }

    QString sql = "select borrow_book.num,borrow_book.book_num,borrow_book.book_ISBN, book.book_name,"
            "book.author, book.pages,book.price,book.publisher,book.pubdate,reader.ID,"
            "reader.user_name,reader.sex,reader.ID_card,reader.phone,borrow_book.lend_date,borrow_book.should_return_date,"
            "borrow_book.renew_count "
            "from reader,borrow_book,book where borrow_book.book_ISBN=book.ISBN and "
            "borrow_book.reader_card_num=reader.card_num and borrow_book.return_date is NULL"
            " and book." + bookStr + " like '" + bookInfo
            + "' and reader." + readerStr + " like '" + readerInfo + "'";

//    qDebug() << sql;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

    if (query.isActive())
    {
        model->QSqlQueryModel::setQuery(query);
        initModel();
        tableView->resizeColumnsToContents();
    }
    else
    {
        QMessageBox::information(this, tr("Error"), query.lastError().text());
    }
}

void ReturnBooksWidget::returnClicked()
{
    QModelIndexList indexList = tableView->selectionModel()->selectedRows(0);
    if (indexList.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Please select line"));
        return;
    }

//    const int rowCount = tableView->selectionModel()->selectedRows(0).count();
    int row = tableView->selectionModel()->selectedRows(0).begin()->row();
    QString num = model->data(model->index(row, 0)).toString();
    QString bookNum = model->data(model->index(row,1)).toString();
    QString ID = model->data(model->index(row, 9)).toString();

    ReturnBookInfoDialog temp(user_name, num, bookNum, ID);
    if (temp.exec())
    {
        displayClicked();
    }
}

QString ReturnBooksWidget::getModelData()
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

QString ReturnBooksWidget::getHeaderDate()
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
