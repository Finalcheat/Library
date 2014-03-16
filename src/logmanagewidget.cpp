#include "logmanagewidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QSqlTableModel>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QSqlQuery>
#include <QTextDocument>


LogManageWidget::LogManageWidget(QWidget *parent) :
    QWidget(parent)
{
    logTableLabel = new QLabel(tr("&Log Table:"));
    logTableComboBox = new QComboBox;
    logTableComboBox->addItems(QStringList() << tr("reader") << tr("book"));
    logTableLabel->setBuddy(logTableComboBox);
    IDLabel = new QLabel(tr("&ID:"));
    IDLineEdit = new QLineEdit;
    IDLabel->setBuddy(IDLineEdit);

    startDateTimeLabel = new QLabel(tr("&Start:"));
    startDateTimeEdit = new QDateTimeEdit;
    startDateTimeLabel->setBuddy(startDateTimeEdit);

    endDateTimeLabel = new QLabel(tr("&End:"));
    endDateTimeEdit = new QDateTimeEdit;
    endDateTimeLabel->setBuddy(endDateTimeEdit);

    queryButton = new QPushButton(tr("Quer&y"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(logTableLabel);
    topLayout->addWidget(logTableComboBox);
    topLayout->addWidget(IDLabel);
    topLayout->addWidget(IDLineEdit);
    topLayout->addWidget(startDateTimeLabel);
    topLayout->addWidget(startDateTimeEdit);
    topLayout->addWidget(endDateTimeLabel);
    topLayout->addWidget(endDateTimeEdit);
    topLayout->addWidget(queryButton);

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

    connect(queryButton, SIGNAL(clicked()), this, SLOT(queryClicked()));
}

void LogManageWidget::initModel(int index)
{
    if (index == 0)
    {
        model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("日志编号"));
        model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("操作用户"));
        model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("读者ID"));
        model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("操作类型"));
        model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("操作时间"));
    }
    else
    {
        model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("日志编号"));
        model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("操作用户"));
        model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("ISBN"));
        model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("操作类型"));
        model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("操作时间"));
    }
}

void LogManageWidget::queryClicked()
{
    int index = logTableComboBox->currentIndex();
    QString ID = IDLineEdit->text();
    if (ID.isEmpty())
    {
        ID = "%";
    }
    QDateTime startDateTime = startDateTimeEdit->dateTime();
    QDateTime endDateTime = endDateTimeEdit->dateTime();
    QString str;
    if (startDateTime < endDateTime)
    {
       str = " and operation_date >= '" + startDateTime.toString(Qt::ISODate)
                    + "' and operation_date <= '" + endDateTime.toString(Qt::ISODate) + "'";
    }
    QString tableName = "book_log_info";
    if (index == 0)
    {
        tableName = "reader_log_info";
    }

    QString sql = "select * from " + tableName + " where ID like '" + ID + "'" + str;

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query = db.exec(sql);

    model->QSqlQueryModel::setQuery(query);

    initModel(index);
    tableView->resizeColumnsToContents();
}

QString LogManageWidget::getModelData()
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

QString LogManageWidget::getHeaderDate()
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
