#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
class QLabel;
class QLineEdit;

class SettingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingDialog(QWidget *parent = 0);
    
private slots:
    void okButtonClicked();

private:
    void initData();

private:
    QLabel *lendBookMaxLaebl;
    QLineEdit *lendBookMaxLineEdit;
    QLabel *renewBookMaxLabel;
    QLineEdit *renewBookMaxLineEdit;
    QLabel *vipLendBookMaxLabel;
    QLineEdit *vipLendBookMaxLineEdit;
    QLabel *vipRenewBookMaxLabel;
    QLineEdit *vipRenewBookMaxLineEdit;
    QLabel *lendBookDateLabel;
    QLineEdit *lendBookDateLineEdit;
    QLabel *damageMoneyLabel;
    QLineEdit *damageMoneyLineEdit;
    QLabel *dateMoneyLabel;
    QLineEdit *dateMoneyLineEdit;

    QPushButton *okButton;
    QPushButton *cancelButton;

    QString str;
};

#endif // SETTINGDIALOG_H
