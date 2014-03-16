#ifndef BORROWBOOKWIDGET_H
#define BORROWBOOKWIDGET_H

#include <QWidget>
class QComboBox;
class QLineEdit;
class QPushButton;
class QTableView;
class QSqlTableModel;

class BorrowBookWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BorrowBookWidget(const QString &u, QWidget *parent = 0);

public:
    QString getModelData();
    QString getHeaderDate();

private slots:
    void displayClicked();
    void borrowBookClicked();
    void queryClicked();

private:
    void initModel();
    
private:
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QComboBox *queryTypeComboBox;

    QPushButton *queryButton;

    QPushButton *borrowButton;
    QPushButton *displayButton;

    QTableView *tableView;
    QSqlTableModel *model;

    const QString user_name;
};

#endif // BORROWBOOKWIDGET_H
