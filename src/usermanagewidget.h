#ifndef USERMANAGEWIDGET_H
#define USERMANAGEWIDGET_H

#include <QWidget>
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QTableView;
class QSqlTableModel;
class QGroupBox;
class QMenu;

class UserManageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UserManageWidget(const QString &u, QWidget *parent = 0);

public:
    QString getModelData();
    QString getHeaderDate();

private slots:
    void addUser();
    void displayAllClicked();
    void deleteClicked();
    void modifyClicked();
    void queryClicked();
    void showTableViewMenu(QPoint);

private:
    void tranModel();
    void createTableViewMenu();

private:
    QLabel *queryUserNameLabel;
    QLineEdit *queryUserNameLineEdit;
    QComboBox *queryTypeComboBox;
    QPushButton *queryButton;
    QPushButton *displayAllButton;

    QTableView *tableView;
    QSqlTableModel *model;

    QPushButton *modifyButton;
    QPushButton *deleteButton;

    QPushButton *addButton;

    QMenu *tableMenu;

    const QString user_name;
};

#endif // USERMANAGEWIDGET_H
