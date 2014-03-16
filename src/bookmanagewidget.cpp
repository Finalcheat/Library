#include "bookmanagewidget.h"
#include "bookinfodialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QSqlTableModel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QString>
#include <QTextDocument>
#include <QMenu>
#include <QAction>

BookManageWidget::BookManageWidget(const QString &u, QWidget *parent) :
    QWidget(parent), user_name(u)
{
    comboBox = new QComboBox;
    comboBox->addItems(QStringList() << tr("num") << tr("ISBN") << tr("book_name") << tr("author") << tr("pages")
                       << tr("price") << tr("publisher") << tr("pubdate") << tr("summary"));
    lineEdit = new QLineEdit;
    queryTypeComboBox = new QComboBox;
    queryTypeComboBox->addItems(QStringList() << tr("exact") << tr("vague"));
    queryButton = new QPushButton(tr("Query"));

    displayButton = new QPushButton(tr("Display All"));
    addButton = new QPushButton(tr("Add"));
    modifyButton = new QPushButton(tr("Modify"));
    deleteButton = new QPushButton(tr("Delete"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(comboBox);
    topLayout->addWidget(lineEdit);
    topLayout->addWidget(queryTypeComboBox);
    topLayout->addWidget(queryButton);
    topLayout->addStretch();
    topLayout->addWidget(displayButton);
    topLayout->addWidget(addButton);
    topLayout->addWidget(modifyButton);
    topLayout->addWidget(deleteButton);


    tableView = new QTableView;

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


    model = new QSqlTableModel;

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableView->setModel(model);

//    tableView->setSortingEnabled(true);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(tableView);

    setLayout(mainLayout);

    connect(displayButton, SIGNAL(clicked()), this, SLOT(displayClicked()));
    connect(queryButton, SIGNAL(clicked()), this, SLOT(queryClicked()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addClicked()));
    connect(modifyButton, SIGNAL(clicked()), this, SLOT(modifyClicked()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));

    createTableViewMenu();

    connect(tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showTableViewMenu(QPoint)));
}

void BookManageWidget::createTableViewMenu()
{
    tableMenu = new QMenu(tableView);

    QAction *addNewAction = new QAction(tr("Add"), this);
    addNewAction->setIcon(QIcon(":/images/add.png"));
    connect(addNewAction, SIGNAL(triggered()), this, SLOT(addClicked()));

    QAction *modifyAction = new QAction(tr("Modify"), this);
    modifyAction->setIcon(QIcon(":/images/modify.png"));
    connect(modifyAction, SIGNAL(triggered()), this, SLOT(modifyClicked()));

    QAction *deleteAction = new QAction(tr("Delete"), this);
    deleteAction->setIcon(QIcon(":/images/delete.png"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteClicked()));

    tableMenu->addAction(addNewAction);
    tableMenu->addAction(modifyAction);
    tableMenu->addAction(deleteAction);

    tableView->setContextMenuPolicy(Qt::CustomContextMenu);
}

void BookManageWidget::displayClicked()
{
    model->setTable("book_view");
    model->select();
    tableView->resizeColumnsToContents();
}

void BookManageWidget::initModel()
{
    model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("书籍编号"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("书名"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("作者"));
    model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("页数"));
    model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("价格"));
    model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("出版社"));
    model->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("出版日期"));
//    model->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("简介"));
}

void BookManageWidget::queryClicked()
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
//    for (int i = 0; i < model->columnCount(); ++i)
//        tableView->resizeColumnToContents(i);
    tableView->resizeColumnsToContents();
}

void BookManageWidget::modifyClicked()
{
    QModelIndexList indexList = tableView->selectionModel()->selectedRows(0);
    if (indexList.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Please select a line"));
        return;
    }

    int row = tableView->selectionModel()->selectedRows(0).begin()->row();
    QString num = model->data(model->index(row, 0)).toString();

    BookInfoDialog temp(user_name, num);
    if (temp.exec())
    {
//        displayAllClicked();
    }
}

void BookManageWidget::addClicked()
{
    BookInfoDialog temp(user_name);
    if (temp.exec())
    {
        displayClicked();
    }
}

void BookManageWidget::deleteClicked()
{
    QModelIndexList indexList = tableView->selectionModel()->selectedRows(0);
    if (indexList.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Please select line"));
        return;
    }

    int r = QMessageBox::warning(this, QString::fromLocal8Bit("删除数据"),
                                 QString::fromLocal8Bit("确定要删除选定的数据吗？"),
                                         QMessageBox::Yes | QMessageBox::Default,
                                         QMessageBox::No,
                                         QMessageBox::Cancel | QMessageBox::Escape);

    if (r == QMessageBox::No || r == QMessageBox::Cancel)
    {
        return;
    }

    const int rowCount = tableView->selectionModel()->selectedRows(0).count();
    int row = tableView->selectionModel()->selectedRows(0).begin()->row();
    bool deleteBool = true;
    QSqlDatabase db = QSqlDatabase::database();
//    db.transaction();
    for (int i = 0; i < rowCount; ++i)
    {
        QModelIndex index = model->index(row, 0);

        QString num = index.data(Qt::DisplayRole).toString();
        QString sql = "delete from book where num='" + num + "'";


        QSqlQuery query = db.exec(sql);
        if (!query.isActive())
        {
            QMessageBox::information(this, tr("Error"), query.lastError().text());
            deleteBool = false;
        }

        index = model->index(row, 1);
        QString ISBN = index.data(Qt::DisplayRole).toString();

        sql = "insert into book_log_info(ID,book_ISBN,operation,operation_date) values('"
                + user_name + "','" + ISBN + "','delete','" + QDateTime::currentDateTime().toString(Qt::ISODate)
                + "')";

        query = db.exec(sql);
    }

    if (deleteBool)
    {
//        db.commit();
        displayClicked();
        QMessageBox::information(this, tr("Succeed"), tr("Delete succeed"));
    }
}

QString BookManageWidget::getModelData()
{
//    QStringList strList;

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

QString BookManageWidget::getHeaderDate()
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

void BookManageWidget::showTableViewMenu(QPoint)
{
    tableMenu->exec(QCursor::pos());
}
