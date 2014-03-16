#ifndef RETURNBOOKSWIDGET_H
#define RETURNBOOKSWIDGET_H

#include <QWidget>
class QComboBox;
class QLineEdit;
class QPushButton;
class QTableView;
class QSqlTableModel;

class ReturnBooksWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReturnBooksWidget(const QString &u, QWidget *parent = 0);

public:
    QString getModelData();
    QString getHeaderDate();

private slots:
    void displayClicked();
    void queryClicked();
    void returnClicked();

private:
    void initModel();
    
private:
    QComboBox *bookInfoComboBox;
    QLineEdit *bookInfoLineEdit;
    QComboBox *readerInfoComboBox;
    QLineEdit *readerLineEdit;
    QComboBox *typeComboBox;
    QPushButton *queryButton;
    
    QPushButton *returnButton;
    QPushButton *displayButton;

    QTableView *tableView;
    QSqlTableModel *model;

    const QString user_name;
};

#endif // RETURNBOOKSWIDGET_H
