#ifndef MODIFYPASSWORDDIALOG_H
#define MODIFYPASSWORDDIALOG_H

#include <QDialog>
class QLabel;
class QLineEdit;

class ModifyPasswordDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ModifyPasswordDialog(const QString &name, QWidget *parent = 0);

private slots:
    void okButtonClicked();
    
private:
    QLabel *originalPasswordLabel;
    QLineEdit *originalPasswordLineEdit;
    QLabel *targetPasswordLabel;
    QLineEdit *targetPasswordLineEdit;
    QLabel *atargetPasswordLabel;
    QLineEdit *atargetPasswordLineEdit;

    QPushButton *okButton;
    QPushButton *cancelButton;

    const QString &userName;
};

#endif // MODIFYPASSWORDDIALOG_H
