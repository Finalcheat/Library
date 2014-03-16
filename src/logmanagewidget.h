#ifndef LOGMANAGEWIDGET_H
#define LOGMANAGEWIDGET_H

#include <QWidget>
class QLabel;
class QLineEdit;
class QPushButton;
class QTableView;
class QSqlTableModel;
class QComboBox;
class QDateTimeEdit;

class LogManageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogManageWidget(QWidget *parent = 0);

public:
    QString getModelData();
    QString getHeaderDate();

private slots:
    void queryClicked();

private:
    void initModel(int);
    
private:
    QLabel *logTableLabel;
    QComboBox *logTableComboBox;
    QLabel *IDLabel;
    QLineEdit *IDLineEdit;
    QLabel *startDateTimeLabel;
    QDateTimeEdit *startDateTimeEdit;
    QLabel *endDateTimeLabel;
    QDateTimeEdit *endDateTimeEdit;
    QPushButton *queryButton;

    QTableView *tableView;
    QSqlTableModel *model;
};

#endif // LOGMANAGEWIDGET_H
