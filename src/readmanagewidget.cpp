#include "readmanagewidget.h"
#include "readerinfodialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QSqlTableModel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QTextDocument>
#include <QAction>
#include <QMenu>

ReaderManageWidget::ReaderManageWidget(const QString &u, QWidget *parent) :
    QWidget(parent), user_name(u)
{
    comboBox = new QComboBox;
    comboBox->addItems(QStringList() << tr("card_num") << tr("ID") << tr("user_name") << tr("sex")
                       << tr("birthday") << tr("card_date") << tr("ID_card") << tr("phone")
                       << tr("state") << tr("type"));
    nameLineEdit = new QLineEdit;

    typeComboBox = new QComboBox;
    typeComboBox->addItems(QStringList() << tr("exact") << tr("vague"));
    queryButton = new QPushButton(tr("Quer&y"));

    displayButton = new QPushButton(tr("Display All"));
    addButton = new QPushButton(tr("Add"));
    modifyButton = new QPushButton(tr("Modify"));
    deleteButton = new QPushButton(tr("Delete"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(comboBox);
    topLayout->addWidget(nameLineEdit);
    topLayout->addWidget(typeComboBox);
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

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(tableView);

    setLayout(mainLayout);

    connect(displayButton, SIGNAL(clicked()), this, SLOT(displayClicked()));
    connect(addButton, SIGNAL(clicked()), this, SLOT(addClicked()));
    connect(queryButton, SIGNAL(clicked()), this, SLOT(queryClicked()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(modifyButton, SIGNAL(clicked()), this, SLOT(modifyClicked()));

    createTableViewMenu();

    connect(tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showTableViewMenu(QPoint)));
}

void ReaderManageWidget::createTableViewMenu()
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

void ReaderManageWidget::showTableViewMenu(QPoint)
{
    tableMenu->exec(QCursor::pos());
}

void ReaderManageWidget::displayClicked()
{
    model->setTable("reader");
    initModel();
    model->select();
    tableView->resizeColumnsToContents();
}

void ReaderManageWidget::initModel()
{
    model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("卡号"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("ID"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("姓名"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("性别"));
    model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("出生日期"));
    model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("发卡日期"));
    model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("有效日期"));
    model->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("身份证号"));
    model->setHeaderData(8, Qt::Horizontal, QString::fromLocal8Bit("电话"));
    model->setHeaderData(9, Qt::Horizontal, QString::fromLocal8Bit("状态"));
    model->setHeaderData(10, Qt::Horizontal, QString::fromLocal8Bit("类型"));
}

void ReaderManageWidget::addClicked()
{
    ReaderInfoDialog temp(user_name);
    temp.exec();
}

void ReaderManageWidget::queryClicked()
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
    case 2 :
        str = "user_name";
        break;
    case 3 :
        str = "sex";
        break;
    case 4 :
        str = "birthday";
        break;
    case 5 :
        str = "card_date";
        break;
    case 6 :
        str = "ID_card";
        break;
    case 7 :
        str = "phone";
        break;
    case 8 :
        str = "state";
        break;
    default :
        str = "type";
    }

    QString name = nameLineEdit->text();

    index = typeComboBox->currentIndex();
    if (index)
    {
        name = "%" + name + "%";
    }

    QString sql = tr("select * from reader where %1 like '%2'").arg(str).arg(name);

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

    model->QSqlQueryModel::setQuery(query);
    initModel();
    tableView->resizeColumnsToContents();
}

void ReaderManageWidget::deleteClicked()
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

        QString cardNum = index.data(Qt::DisplayRole).toString();
        QString sql = "delete from reader where card_num='" + cardNum + "'";


        QSqlQuery query = db.exec(sql);

        index = model->index(row, 1);
        QString ID = index.data(Qt::DisplayRole).toString();
        sql = "delete from admin where user_name='" + ID + "'";
        query.exec(sql);

//        if (!query.isActive())
//        {
//            QMessageBox::information(this, tr("Error"), query.lastError().text());
//            deleteBool = false;
//        }
        ++row;

        sql = "insert into reader_log_info(ID,reader_ID,operation,operation_date) values('"
                + user_name + "','" + ID + "','delete','" + QDateTime::currentDateTime().toString(Qt::ISODate)
                + "')";
        db.exec(sql);
    }

    if (deleteBool)
    {
//        db.commit();
        displayClicked();
        QMessageBox::information(this, tr("Succeed"), tr("Delete succeed"));
    }
}

void ReaderManageWidget::modifyClicked()
{
    QModelIndexList indexList = tableView->selectionModel()->selectedRows(0);
    if (indexList.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Please select a line"));
        return;
    }

    int row = tableView->selectionModel()->selectedRows(0).begin()->row();
    QString cardNum = model->data(model->index(row, 0)).toString();

    ReaderInfoDialog temp(user_name, cardNum);
    if (temp.exec())
    {
        displayClicked();
    }
}

QString ReaderManageWidget::getModelData()
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

QString ReaderManageWidget::getHeaderDate()
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


