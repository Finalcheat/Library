#ifndef BOOKMANAGEWIDGET_H
#define BOOKMANAGEWIDGET_H

#include <QWidget>
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QTableView;
class QSqlTableModel;
class QMenu;

class BookManageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BookManageWidget(const QString &u, QWidget *parent = 0);

public:
    QString getModelData();
    QString getHeaderDate();

private slots:
    void displayClicked();
    void queryClicked();
    void addClicked();
    void modifyClicked();
    void deleteClicked();
    void showTableViewMenu(QPoint);

private:
    void initModel();
    void createTableViewMenu();
    
private:
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QComboBox *queryTypeComboBox;
    QPushButton *queryButton;

    QPushButton *displayButton;
    QPushButton *addButton;
    QPushButton *modifyButton;
    QPushButton *deleteButton;

    QTableView *tableView;
    QSqlTableModel *model;

    const QString user_name;

    QMenu *tableMenu;
};

#endif // BOOKMANAGEWIDGET_H
