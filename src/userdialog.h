#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>

class QGroupBox;
class QLabel;
class QLineEdit;
class QComboBox;

class UserDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UserDialog(const QString &u,const QString &name = "", QWidget *parent = 0);

private slots:
    void okButtonClicked();
    void modifyClicked();

private:
    void init();
    
private:
    QGroupBox *groupBox;
    QLabel *userNameLabel;
    QLineEdit *userNameLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *userTypeLabel;
    QComboBox *userTypeComboBox;
    QLabel *stateLabel;
    QComboBox *stateComboBox;

    QPushButton *okButton;
    QPushButton *cancelButton;

    const QString &str;
    const QString &user_name;
};

#endif // ADDUSER_H
