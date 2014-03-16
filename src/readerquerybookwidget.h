#ifndef READERQUERYBOOKWIDGET_H
#define READERQUERYBOOKWIDGET_H

#include <QWidget>
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QTableView;
class QSqlTableModel;

class ReaderQueryBookWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReaderQueryBookWidget(QWidget *parent = 0);

public:
    QString getModelData();
    QString getHeaderDate();

private slots:
    void queryClicked();

private:
    void initModel();
    
private:
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QComboBox *queryTypeComboBox;
    QPushButton *queryButton;

    QTableView *tableView;
    QSqlTableModel *model;
    
};

#endif // READERQUERYBOOKWIDGET_H
