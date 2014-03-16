#include "usermanagewidget.h"
#include "userdialog.h"
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTableView>
#include <QSqlTableModel>
#include <QSplitter>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDate>
#include <QSqlError>
#include <QTextDocument>
#include <QAction>
#include <QMenu>

UserManageWidget::UserManageWidget(const QString &u, QWidget *parent) :
    QWidget(parent), user_name(u)
{
    queryUserNameLabel = new QLabel(tr("User N&ame:"));
    queryUserNameLineEdit = new QLineEdit;
    queryUserNameLabel->setBuddy(queryUserNameLineEdit);
    queryTypeComboBox = new QComboBox;
    queryTypeComboBox->addItems(QStringList() << tr("exact") << tr("vague"));
    queryButton = new QPushButton(tr("Quer&y"));
    displayAllButton = new QPushButton(tr("Display All"));
    addButton = new QPushButton(tr("Add"));
    modifyButton = new QPushButton(tr("Modify"));
    deleteButton = new QPushButton(tr("Delete"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(queryUserNameLabel);
    topLayout->addWidget(queryUserNameLineEdit);
    topLayout->addWidget(queryTypeComboBox);
    topLayout->addWidget(queryButton);

    topLayout->addStretch();
    topLayout->addWidget(displayAllButton);
    topLayout->addWidget(addButton);
    topLayout->addWidget(modifyButton);
    topLayout->addWidget(deleteButton);

    tableView = new QTableView;
//    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    model = new QSqlTableModel;

    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableView->setModel(model);

    createTableViewMenu();

//    tableView->setColumnHidden(1, true);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(tableView);

    setLayout(mainLayout);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addUser()));
    connect(displayAllButton, SIGNAL(clicked()), this, SLOT(displayAllClicked()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));
    connect(modifyButton, SIGNAL(clicked()), this, SLOT(modifyClicked()));
    connect(queryButton, SIGNAL(clicked()), this, SLOT(queryClicked()));

    connect(tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showTableViewMenu(QPoint)));
}

void UserManageWidget::createTableViewMenu()
{
    tableMenu = new QMenu(tableView);

    QAction *addNewAction = new QAction(tr("Add"), this);
    addNewAction->setIcon(QIcon(":/images/add.png"));
    connect(addNewAction, SIGNAL(triggered()), this, SLOT(addUser()));

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

void UserManageWidget::addUser()
{
    UserDialog temp(user_name);
    if (temp.exec())
        displayAllClicked();
}

void UserManageWidget::displayAllClicked()
{
    model->setTable("admin_view");
    model->select();
    tranModel();
    tableView->resizeColumnsToContents();
}

void UserManageWidget::tranModel()
{
    for (int i = 0; i < model->rowCount(); ++i)
    {
        QModelIndex modeIndex = model->index(i, 1);
        model->setData(modeIndex, "*********");

//        modeIndex = model->index(i, 2);
//        int power = modeIndex.data(Qt::EditRole).toInt();
//        qDebug() << modeIndex.data(Qt::EditRole) << power;
//        QString str;
//        switch (power)
//        {
//        case 0 :
//            str = tr("Reader");
//            break;
//        case 1 :
//            str = tr("Operator");
//            break;
//        default :
//            str = tr("Administrator");
//        }
//        model->setData(modeIndex, str);

//        modeIndex = model->index(i, 3);
//        int state = modeIndex.data(Qt::DisplayRole).toInt();
//        if (state)
//        {
//            str = tr("Ban");
//        }
//        else
//        {
//            str = tr("Normal");
//        }
//        model->setData(modeIndex, str);
    }
}

void UserManageWidget::deleteClicked()
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
    bool insertBool = true;
    QSqlDatabase db = QSqlDatabase::database();
//    db.transaction();
    for (int i = 0; i < rowCount; ++i)
    {
        QModelIndex index = model->index(row, 0);
        QString userName = index.data(Qt::DisplayRole).toString();

        QModelIndex powerIndex = model->index(row, 2);
        int powerStr = powerIndex.data(Qt::DisplayRole).toInt();
        if (powerStr == 2 && userName != user_name)
        {
            QMessageBox::information(this, tr("Error"), tr("Administrator Can't delete."));
            return;
        }

        QString sql = "delete from admin where user_name='" + userName + "'";


        QSqlQuery query = db.exec(sql);

        sql = "delete from reader where ID='" + userName + "'";
        query = db.exec(sql);

        if (!query.isActive())
        {
            QMessageBox::information(this, tr("Error"), query.lastError().text());
            insertBool = false;
        }

        sql = "insert into reader_log_info(ID,reader_ID,operation,operation_date) values('"
                + user_name + "','" + userName + "','delete','" + QDateTime::currentDateTime().toString(Qt::ISODate)
                + "')";
        db.exec(sql);

        ++row;
    }

    if (insertBool)
    {
//        db.commit();
        QMessageBox::information(this, tr("Succeed"), tr("Delete succeed"));
        displayAllClicked();
    }
}

void UserManageWidget::modifyClicked()
{
    QModelIndexList indexList = tableView->selectionModel()->selectedRows(0);
    if (indexList.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("Please select a line"));
        return;
    }

    int row = tableView->selectionModel()->selectedRows(0).begin()->row();
    QString userName = model->data(model->index(row, 0)).toString();
    int powerStr = model->data(model->index(row, 2)).toInt();
    if (powerStr == 2 && userName != user_name)
    {
        QMessageBox::information(this, tr("Error"), tr("Administrator Can't modify."));
        return;
    }

    UserDialog temp(user_name, userName);
    if (temp.exec())
    {
        displayAllClicked();
    }
}

void UserManageWidget::queryClicked()
{
    QString userName = queryUserNameLineEdit->text();
    if (userName.isEmpty())
    {
        QMessageBox::information(this, tr("Error"), tr("User name can not be empty."));
        return;
    }
    int type = queryTypeComboBox->currentIndex();
    if (type)
    {
        userName = "%" + userName + "%";
    }
    QString sql = "select * from admin where user_name like '" + userName + "'";

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);
    model->QSqlQueryModel::setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("用户名"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("密码"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("权限"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("状态"));
    tranModel();
    tableView->resizeColumnsToContents();
}

QString UserManageWidget::getModelData()
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

QString UserManageWidget::getHeaderDate()
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

void UserManageWidget::showTableViewMenu(QPoint)
{
    tableMenu->exec(QCursor::pos());
}
