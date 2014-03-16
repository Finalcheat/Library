#ifndef READERBOOKSMANAGEWIDGET_H
#define READERBOOKSMANAGEWIDGET_H

#include <QWidget>
class QComboBox;
class QPushButton;
class QDateEdit;
class QTableView;
class QSqlTableModel;
class QLabel;
class QLineEdit;

class ReaderBooksManageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReaderBooksManageWidget(const QString &u, bool b = false, QWidget *parent = 0);

public:
    QString getModelData();
    QString getHeaderDate();

private slots:
    void queryClicked();
    void adminQueryClicked();
    void renewClicked();
    void adminRenewClicked();

private:
    void initAllModel();
    void initModel(bool);
    
private:
    QComboBox *typeComboBox;
    QLabel *startLabel;
    QDateEdit *startDateEdit;
    QLabel *endLabel;
    QDateEdit *endDateEdit;
    QLabel *IDLabel;
    QLineEdit *IDLineEdit;
    QPushButton *queryButton;
    QPushButton *renewButton;

    QTableView *tableView;
    QSqlTableModel *model;

    const QString user_name;
};

#endif // READERBOOKSMANAGEWIDGET_H
