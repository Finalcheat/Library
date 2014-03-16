#ifndef READERFINEINFOWIDGET_H
#define READERFINEINFOWIDGET_H

#include <QWidget>
class QPushButton;
class QDateEdit;
class QTableView;
class QSqlTableModel;
class QLabel;
class QLineEdit;

class ReaderFineInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReaderFineInfoWidget(const QString &u, bool b = false, QWidget *parent = 0);

public:
    QString getModelData();
    QString getHeaderDate();

private slots:
    void queryClicked();
    void adminQueryClicked();

private:
    void initModel();
    
private:
    QLabel *startLabel;
    QDateEdit *startDateEdit;
    QLabel *endLabel;
    QDateEdit *endDateEdit;
    QLabel *IDLabel;
    QLineEdit *IDLineEdit;
    QPushButton *queryButton;

    QTableView *tableView;
    QSqlTableModel *model;
    
    const QString user_name;
};

#endif // READERFINEINFOWIDGET_H
