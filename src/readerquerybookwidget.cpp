#include "readerquerybookwidget.h"
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QTextDocument>

ReaderQueryBookWidget::ReaderQueryBookWidget(QWidget *parent) :
    QWidget(parent)
{
    comboBox = new QComboBox;
    comboBox->addItems(QStringList() << tr("num") << tr("ISBN") << tr("book_name") << tr("author") << tr("pages")
                       << tr("price") << tr("publisher") << tr("pubdate") << tr("summary"));
    lineEdit = new QLineEdit;
    queryTypeComboBox = new QComboBox;
    queryTypeComboBox->addItems(QStringList() << tr("exact") << tr("vague"));
    queryButton = new QPushButton(tr("Query"));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(comboBox);
    topLayout->addWidget(lineEdit);
    topLayout->addWidget(queryTypeComboBox);
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

    connect(queryButton, SIGNAL(clicked()), this, SLOT(queryClicked()));
}

void ReaderQueryBookWidget::initModel()
{
    model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("书籍编号"));
    model->setHeaderData(2, Qt::Horizontal, QString::fromLocal8Bit("书名"));
    model->setHeaderData(3, Qt::Horizontal, QString::fromLocal8Bit("作者"));
    model->setHeaderData(4, Qt::Horizontal, QString::fromLocal8Bit("页数"));
    model->setHeaderData(5, Qt::Horizontal, QString::fromLocal8Bit("价格"));
    model->setHeaderData(6, Qt::Horizontal, QString::fromLocal8Bit("出版社"));
    model->setHeaderData(7, Qt::Horizontal, QString::fromLocal8Bit("出版日期"));
}

void ReaderQueryBookWidget::queryClicked()
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
    tableView->resizeColumnsToContents();
}

QString ReaderQueryBookWidget::getModelData()
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

QString ReaderQueryBookWidget::getHeaderDate()
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
