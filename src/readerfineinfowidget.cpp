#include "readerfineinfowidget.h"
#include <QLabel>
#include <QDateEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QSqlTableModel>
#include <QPushButton>
#include <QSqlQuery>
#include <QLineEdit>
#include <QTextDocument>

ReaderFineInfoWidget::ReaderFineInfoWidget(const QString &u, bool b, QWidget *parent) :
    QWidget(parent), user_name(u)
{
    startLabel = new QLabel(tr("&Start time:"));
    startDateEdit = new QDateEdit;
    startLabel->setBuddy(startDateEdit);
    endLabel = new QLabel(tr("&End time:"));
    endDateEdit = new QDateEdit;
    endLabel->setBuddy(endDateEdit);
    queryButton = new QPushButton(tr("Query"));

    QHBoxLayout *topLayout = new QHBoxLayout;
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
    }
    else
    {
        connect(queryButton, SIGNAL(clicked()), this, SLOT(queryClicked()));
    }
}

void ReaderFineInfoWidget::adminQueryClicked()
{
    QDate startDate = startDateEdit->date();
    QDate endDate = endDateEdit->date();
    QString str;
    if (startDate < endDate)
    {
        str = " and fine_info.fine_date>='" + startDate.toString(Qt::ISODate) + "' and fine_info.fine_date<='"
                + endDate.toString(Qt::ISODate) + "'";
    }
    QString sql;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    QString ID = IDLineEdit->text();

    sql = "select * from fine_info where ID='" + ID + "'" + str;
    query = db.exec(sql);

    if (query.isActive())
    {
        model->QSqlQueryModel::setQuery(query);
        initModel();
        tableView->resizeColumnsToContents();
    }
}

void ReaderFineInfoWidget::queryClicked()
{
    QDate startDate = startDateEdit->date();
    QDate endDate = endDateEdit->date();
    QString str;
    if (startDate < endDate)
    {
        str = " and fine_info.fine_date>'" + startDate.toString(Qt::ISODate) + "' and fine_info.fine_date<'"
                + endDate.toString(Qt::ISODate) + "'";
    }
    QString sql;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

    sql = "select * from fine_info where ID='" + user_name + "'" + str;
    query = db.exec(sql);

    if (query.isActive())
    {
        model->QSqlQueryModel::setQuery(query);
        initModel();
        tableView->resizeColumnsToContents();
    }
}

void ReaderFineInfoWidget::initModel()
{
    model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("罚款编号"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("ISBN"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("读者ID"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("罚款日期"));
    model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("罚款钱数"));
    model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("罚款原因"));
}

QString ReaderFineInfoWidget::getModelData()
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

QString ReaderFineInfoWidget::getHeaderDate()
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
