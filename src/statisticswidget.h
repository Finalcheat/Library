#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QWidget>
class QComboBox;
class QPushButton;
class QTableView;
class QSqlTableModel;
class QGroupBox;

class StatisticsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatisticsWidget(QWidget *parent = 0);

public:
    QString getModelData();
    QString getHeaderDate();

private slots:
    void readerButtonClicked();
    void bookButtonClicked();
    void fineButtonClicked();

private:
    void initReaderInfo(bool);
    void initBookInfo(int);
    void initFineInfo(bool);
    
private:
    QGroupBox *readerInfoGroupBox;
    QComboBox *readerTypeComboBox;
    QPushButton *readerButton;

    QGroupBox *bookInfoGroupBox;
    QComboBox *bookTypeComboBox;
    QPushButton *bookButton;

    QGroupBox *fineInfoGroupBox;
    QComboBox *fineTypeComboBox;
    QPushButton *fineButton;

    QTableView *tableView;
    QSqlTableModel *model;
};

#endif // STATISTICSWIDGET_H
