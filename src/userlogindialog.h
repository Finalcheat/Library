#ifndef USERLOGINDIALOG_H
#define USERLOGINDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
class QLabel;
class QLineEdit;
class QGroupBox;
class QComboBox;

class UserLoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UserLoginDialog(QWidget *parent = 0);

public:
    QSqlDatabase getDB();
    int getPower() const;
    void clear();
    QString getUserName() const;

private slots:
    void loginButtonClicked();

private:
    QGroupBox *groupBox;
    QLabel *userNameLabel;
    QLineEdit *userNameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *userTypeLabel;
    QComboBox *userTypeComboBox;

    QPushButton *loginButton;
    QPushButton *cancelButton;

    QSqlDatabase db;

    int power;
};

#endif // USERLOGINDIALOG_H
