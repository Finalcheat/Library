#include "statisticswidget.h"
#include <QComboBox>
#include <QPushButton>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QTextDocument>
#include <QDebug>

StatisticsWidget::StatisticsWidget(QWidget *parent) :
    QWidget(parent)
{
    readerTypeComboBox = new QComboBox;
    readerTypeComboBox->addItems(QStringList() << tr("Readers number") << tr("Borrow the accumulated amount"));
    readerButton = new QPushButton(tr("&Query"));

    QGridLayout *readerLayout = new QGridLayout;
    readerLayout->addWidget(readerTypeComboBox, 0, 0, 1, 3);
    readerLayout->addWidget(readerButton, 1, 0, 1, 1);

    readerInfoGroupBox = new QGroupBox(tr("&Reader Information"));
    readerInfoGroupBox->setLayout(readerLayout);

    bookTypeComboBox = new QComboBox;
    bookTypeComboBox->addItems(QStringList() << tr("Loan number") << tr("Publisher") << tr("Author"));
    bookButton = new QPushButton(tr("Quer&y"));

    QGridLayout *bookLayout = new QGridLayout;
    bookLayout->addWidget(bookTypeComboBox, 0, 0, 1, 3);
    bookLayout->addWidget(bookButton, 1, 0, 1, 1);

    bookInfoGroupBox = new QGroupBox(tr("Book Information"));
    bookInfoGroupBox->setLayout(bookLayout);

    fineTypeComboBox = new QComboBox;
    fineTypeComboBox->addItems(QStringList() << tr("Fine readers") << tr("Fine books"));
    fineButton = new QPushButton(tr("&Query"));

    QGridLayout *fineLayout = new QGridLayout;
    fineLayout->addWidget(fineTypeComboBox, 0, 0, 1, 3);
    fineLayout->addWidget(fineButton, 1, 0, 1, 1);

    fineInfoGroupBox = new QGroupBox(tr("Fine Information"));
    fineInfoGroupBox->setLayout(fineLayout);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(readerInfoGroupBox);
//    leftLayout->addStretch();
    leftLayout->addWidget(bookInfoGroupBox);
//    leftLayout->addStretch();
    leftLayout->addWidget(fineInfoGroupBox);


    tableView = new QTableView;

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


    model = new QSqlTableModel;

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableView->setModel(model);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(tableView);

    setLayout(mainLayout);

    connect(readerButton, SIGNAL(clicked()), this, SLOT(readerButtonClicked()));
    connect(bookButton, SIGNAL(clicked()), this, SLOT(bookButtonClicked()));
    connect(fineButton, SIGNAL(clicked()), this, SLOT(fineButtonClicked()));
}

void StatisticsWidget::readerButtonClicked()
{
    int index = readerTypeComboBox->currentIndex();
    QSqlDatabase db = QSqlDatabase::database();
    QString sql;
    QSqlQuery query;
    if (index)
    {
//        model->setTable("admin_view");
//        model->select();
        sql = "select COUNT(borrow_book.num) count_num,reader.card_num,reader.ID,reader.user_name,"
               "reader.sex,reader.birthday,reader.card_date,reader.valid_date,reader.ID_card,"
               "reader.phone,reader.state,reader.type from borrow_book,reader where "
               "reader.card_num=borrow_book.reader_card_num group by borrow_book.reader_card_num,"
               "reader.card_num,reader.ID,reader.user_name,reader.sex,reader.birthday,reader.card_date,"
               "reader.valid_date,reader.ID_card,reader.phone,reader.state,reader.type";
        query = db.exec(sql);
        model->QSqlQueryModel::setQuery(query);
        initReaderInfo(true);
        tableView->resizeColumnsToContents();
//        int row = 0;
//        while (query.next())
//        {
//            QString readerNum = query.value(0).toString();
//            int count = query.value(1).toInt();

//            qDebug() << readerNum << count;
//            sql = "select * from reader where card_num='" + readerNum + "'";
//            QSqlQuery temp = db.exec(sql);
//            while (temp.next())
//            {
//                qDebug() << "yes";

//                model->setData(model->index(row, 0), count);
//                model->setData(model->index(row, 1), temp.value(0).toString());
//                model->setData(model->index(row, 2), temp.value(1).toString());
//                model->setData(model->index(row, 3), temp.value(2).toString());
//                model->setData(model->index(row, 4), temp.value(3).toString());
//                model->setData(model->index(row, 5), temp.value(4).toString());
//                model->setData(model->index(row, 6), temp.value(5).toString());
//                model->setData(model->index(row, 7), temp.value(6).toString());
//                model->setData(model->index(row, 8), temp.value(7).toString());
//                model->setData(model->index(row, 9), temp.value(8).toString());
//                model->setData(model->index(row, 10), temp.value(9).toString());
//                model->setData(model->index(row, 11), temp.value(10).toString());

//                ++row;
//            }
//        }
    }
    else
    {
        sql = "select type,count(card_num) count_num from reader group by type";
        query = db.exec(sql);
        if (query.isActive())
        {
            model->QSqlQueryModel::setQuery(query);
            initReaderInfo(false);
//            tableView->resizeColumnsToContents();
        }
        else
        {
            QMessageBox::information(this, tr("Error"), query.lastError().text());
        }
    }
}

void StatisticsWidget::bookButtonClicked()
{
    int index = bookTypeComboBox->currentIndex();
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    QString sql;
    if (index == 0)
    {
        sql = "select count(borrow_book.num) count_num,book.num,book.ISBN,book.book_name,"
                "book.author,book.pages,book.price,book.publisher,book.pubdate "
                "from borrow_book,book "
                "where borrow_book.book_num=book.num "
                "group by book_num,book.num,book.ISBN,book.book_name,book.author,"
                "book.pages,book.price,book.publisher,book.pubdate";

        query = db.exec(sql);

        if (query.isActive())
        {
            model->QSqlQueryModel::setQuery(query);
            initBookInfo(0);
            tableView->resizeColumnsToContents();
        }
        else
        {
            QMessageBox::information(this, tr("Error"), query.lastError().text());
        }

    }
    else if (index == 1)
    {
        sql = "select COUNT(num) count_num,publisher from book group by publisher";

        query = db.exec(sql);

        if (query.isActive())
        {
            model->QSqlQueryModel::setQuery(query);
            initBookInfo(1);
            tableView->resizeColumnsToContents();
        }
        else
        {
            QMessageBox::information(this, tr("Error"), query.lastError().text());
        }
    }
    else
    {
        sql = "select COUNT(num) count_num,author from book group by author";

        query = db.exec(sql);

        if (query.isActive())
        {
            model->QSqlQueryModel::setQuery(query);
            initBookInfo(2);
            tableView->resizeColumnsToContents();
        }
        else
        {
            QMessageBox::information(this, tr("Error"), query.lastError().text());
        }
    }
}

void StatisticsWidget::fineButtonClicked()
{
    int index = fineTypeComboBox->currentIndex();
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    QString sql;
    if (index == 0)
    {
        sql = "select COUNT(num) count_num,reader.card_num,reader.ID,reader.user_name,"
              "reader.sex,reader.birthday,reader.card_date,reader.valid_date,reader.ID_card,"
              "reader.phone,reader.state,reader.type from fine_info,reader where reader.ID=fine_info.ID "
              "group by reader.ID,reader.card_num,reader.user_name,reader.sex,reader.birthday,"
              "reader.card_date,reader.valid_date,reader.ID_card,reader.phone,reader.state,"
              "reader.type";

        query = db.exec(sql);
        if (query.isActive())
        {
            model->QSqlQueryModel::setQuery(query);
            initFineInfo(false);
            tableView->resizeColumnsToContents();
        }
        else
        {
            QMessageBox::information(this, tr("Error"), query.lastError().text());
        }
    }
    else
    {
        sql = "select COUNT(fine_info.num) count_num,book.num,book.ISBN,book.book_name,"
                "book.author,book.pages,book.price,book.publisher,book.pubdate from fine_info"
                ",book where book.ISBN=fine_info.ISBN group by book.num,book.ISBN,"
                "book.book_name,book.author,book.pages,book.price,book.publisher,book.pubdate";

        query = db.exec(sql);
        if (query.isActive())
        {
            model->QSqlQueryModel::setQuery(query);
            initFineInfo(true);
            tableView->resizeColumnsToContents();
        }
        else
        {
            QMessageBox::information(this, tr("Error"), query.lastError().text());
        }
    }
}

QString StatisticsWidget::getModelData()
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

QString StatisticsWidget::getHeaderDate()
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

void StatisticsWidget::initReaderInfo(bool b)
{
    if (b)
    {
        model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("借书总次数"));
        model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("读者编号"));
        model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("读者ID"));
        model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("读者姓名"));
        model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("读者性别"));
        model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("出生日期"));
        model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("办卡日期"));
        model->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("有效日期"));
        model->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("身份证号"));
        model->setHeaderData(9, Qt::Horizontal, QString::fromLocal8Bit("电话号码"));
        model->setHeaderData(10, Qt::Horizontal, QString::fromLocal8Bit("状态"));
        model->setHeaderData(11, Qt::Horizontal, QString::fromLocal8Bit("类型"));
    }
    else
    {
        model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("读者类型"));
        model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("总人数"));
    }
}

void StatisticsWidget::initBookInfo(int value)
{
    switch (value)
    {
    case 0 :
        model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("借书总次数"));
        model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("书籍编号"));
        model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("ISBN"));
        model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("书名"));
        model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("作者"));
        model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("页数"));
        model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("价格"));
        model->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("出版社"));
        model->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("出版日期"));
        break;
    case 1 :
        model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("总数"));
        model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("出版社"));
        break;
    default :
        model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("总数"));
        model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("作者"));
    }
}

void StatisticsWidget::initFineInfo(bool b)
{
    if (b)
    {
        model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("罚款总次数"));
        model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("书籍编号"));
        model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("ISBN"));
        model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("书名"));
        model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("作者"));
        model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("页数"));
        model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("价格"));
        model->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("出版社"));
        model->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("出版日期"));
    }
    else
    {
        model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("罚款总次数"));
        model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("读者编号"));
        model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("读者ID"));
        model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("读者姓名"));
        model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("读者性别"));
        model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("出生日期"));
        model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("办卡日期"));
        model->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("有效日期"));
        model->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("身份证号"));
        model->setHeaderData(9, Qt::Horizontal, QString::fromLocal8Bit("电话号码"));
        model->setHeaderData(10, Qt::Horizontal, QString::fromLocal8Bit("状态"));
        model->setHeaderData(11, Qt::Horizontal, QString::fromLocal8Bit("类型"));
    }
}
