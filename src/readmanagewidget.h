#ifndef READMANAGEWIDGET_H
#define READMANAGEWIDGET_H

#include <QWidget>
class QLabel;
class QLineEdit;
class QComboBox;
class QTableView;
class QPushButton;
class QSqlTableModel;
class QMenu;

class ReaderManageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReaderManageWidget(const QString &u, QWidget *parent = 0);

public:
    QString getModelData();
    QString getHeaderDate();

private slots:
    void displayClicked();
    void addClicked();
    void queryClicked();
    void deleteClicked();
    void modifyClicked();
    void showTableViewMenu(QPoint);

private:
    void initModel();
    void createTableViewMenu();
    
private:
    QComboBox *comboBox;
    QLineEdit *nameLineEdit;
    QComboBox *typeComboBox;

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

#endif // READMANAGEWIDGET_H
