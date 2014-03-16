#include "borrowbookwidget.h"
#include "borrowbookinfodialog.h"
#include <QTableView>
#include <QSqlTableModel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTextDocument>

BorrowBookWidget::BorrowBookWidget(const QString &u, QWidget *parent) :
    QWidget(parent), user_name(u)
{
    comboBox = new QComboBox;
    comboBox->addItems(QStringList() << tr("num") << tr("ISBN") << tr("book_name") << tr("author") << tr("pages")
                       << tr("price") << tr("publisher") << tr("pubdate") << tr("summary"));
    lineEdit = new QLineEdit;
    queryTypeComboBox = new QComboBox;
    queryTypeComboBox->addItems(QStringList() << tr("exact") << tr("vague"));
    queryButton = new QPushButton(tr("Query"));

    borrowButton = new QPushButton(tr("Borrow Book"));
    displayButton = new QPushButton(tr("Display All"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(comboBox);
    topLayout->addWidget(lineEdit);
    topLayout->addWidget(queryTypeComboBox);
    topLayout->addWidget(queryButton);
    topLayout->addStretch();
    topLayout->addWidget(borrowButton);
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
    connect(borrowButton, SIGNAL(clicked()), this, SLOT(borrowBookClicked()));
    connect(queryButton, SIGNAL(clicked()), this, SLOT(queryClicked()));
}

void BorrowBookWidget::displayClicked()
{
    model->setTable("book_view");
    model->select();
    tableView->resizeColumnsToContents();
}

void BorrowBookWidget::initModel()
{
    model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("书籍编号"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("书名"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("作者"));
    model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("页数"));
    model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("价格"));
    model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("出版社"));
    model->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("出版日期"));
    model->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("简介"));
}

void BorrowBookWidget::borrowBookClicked()
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
    BorrowBookInfoDialog temp(user_name, num);
    if (temp.exec())
        displayClicked();
}

void BorrowBookWidget::queryClicked()
{
    int index = comboBox->currentIndex();
    QString str;
    switch (index)
    {
    case 0 :
        str = "num";
        break;
    case 1 :
        str = "ISBN";
        break;
    case 2 :
        str = "book_name";
        break;
    case 3 :
        str = "author";
        break;
    case 4 :
        str = "pages";
        break;
    case 5 :
        str = "price";
        break;
    case 6 :
        str = "publisher";
        break;
    case 7 :
        str = "pubdate";
        break;
    default :
        str = "summary";
    }

    QString name = lineEdit->text();
    if (name.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("%1 can not be empty.").arg(str));
        return;
    }

    index = queryTypeComboBox->currentIndex();
    if (index)
    {
        name = "%" + name + "%";
    }

    QString sql = tr("select num,ISBN,book_name,author,pages,price,publisher,pubdate from book where %1 like '%2' and state=1").arg(str).arg(name);

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

    model->QSqlQueryModel::setQuery(query);
    initModel();
    for (int i = 0; i < model->columnCount(); ++i)
        tableView->resizeColumnToContents(i);
}

QString BorrowBookWidget::getModelData()
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

QString BorrowBookWidget::getHeaderDate()
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
