#ifndef RENEWBOOKWIDGET_H
#define RENEWBOOKWIDGET_H

#include <QWidget>
class QComboBox;
class QLineEdit;
class QPushButton;
class QTableView;
class QSqlTableModel;

class RenewBookWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RenewBookWidget(const QString &u, QWidget *parent = 0);

public:
    QString getModelData();
    QString getHeaderDate();

private slots:
    void displayClicked();
    void queryClicked();
    void renewClicked();

private:
    void initModel();
    
private:
    QComboBox *bookInfoComboBox;
    QLineEdit *bookInfoLineEdit;
    QComboBox *readerInfoComboBox;
    QLineEdit *readerLineEdit;
    QComboBox *typeComboBox;
    QPushButton *queryButton;

    QPushButton *renewButton;
    QPushButton *displayButton;

    QTableView *tableView;
    QSqlTableModel *model;

    const QString user_name;
};

#endif // RENEWBOOKWIDGET_H
