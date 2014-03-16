#ifndef READERINFODIALOG_H
#define READERINFODIALOG_H

#include <QDialog>
class QLabel;
class QLineEdit;
class QComboBox;
class QDateEdit;
class QGroupBox;

class ReaderInfoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ReaderInfoDialog(const QString &u, const QString &num = "", QWidget *parent = 0);

private slots:
    void okButtonClicked();
    void modifyClicked();
    void queryClicked();

private:
    void init();
    
private:
    QGroupBox *groupBox;

    QLabel *IDLabel;
    QLineEdit *IDLineEdit;
    QPushButton *queryButton;

    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *againPasswordLabel;
    QLineEdit *againPasswordLineEdit;

    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    
    QLabel *sexLabel;
    QComboBox *sexComboBox;

    QLabel *birthdayLabel;
    QDateEdit *birthdayDateEdit;

    QLabel *cardDateLabel;
    QDateEdit *cardDateEdit;

    QLabel *validDateLabel;
    QDateEdit *validDateEdit;

    QLabel *IDCardLabel;
    QLineEdit *IDCardLineEdit;

    QLabel *phoneLabel;
    QLineEdit *phoneLineEdit;

    QLabel *stateLabel;
    QComboBox *stateComboBox;

    QLabel *typeLabel;
    QComboBox *typeComboBox;

    QPushButton *okButton;
    QPushButton *cancelButton;

    const QString &str;
    const QString &user_name;
};

#endif // READERINFODIALOG_H
