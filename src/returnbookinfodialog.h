#ifndef RETURNBOOKINFODIALOG_H
#define RETURNBOOKINFODIALOG_H

#include <QDialog>
class QLabel;
class QLineEdit;
class QGroupBox;
class QComboBox;
class QDateEdit;
class QSpinBox;
class QDoubleSpinBox;

class ReturnBookInfoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ReturnBookInfoDialog(const QString &u, const QString &n, const QString &bookNum, const QString &ID, bool renew = false, QWidget *parent = 0);

private:
    void initBookInfo(const QString &bookNum);
    void initReaderInfo(const QString &ID);

private slots:
    void okButtonClicked();
    void renewClicked();

private:
    void returnBook();
    bool exceedTime();
    bool damage();
    void loseBook();

private:
    void normalClicked();
    void damageClicked();
    void loseClicked();
    
private:
    QGroupBox *bookInfoGroupBox;
    QLabel *bookNumLabel;
    QLineEdit *bookNumLineEdit;
    QLabel *ISBNLabel;
    QLineEdit *ISBNLineEdit;
    QLabel *bookNameLabel;
    QLineEdit *bookNameLineEdit;
    QLabel *authorLabel;
    QLineEdit *authorLineEdit;
    QLabel *pagesLabel;
    QSpinBox *pagesSpinBox;
    QLabel *priceLabel;
    QDoubleSpinBox *priceDoubleSpinBox;
    QLabel *publisherLabel;
    QLineEdit *publisherLineEdit;
    QLabel *pubdateLabel;
    QDateEdit *pubdateDateEdit;

    QGroupBox *readerGroupBox;
    QLabel *cardNumLabel;
    QLineEdit *cardNumLineEdit;
    QLabel *IDLabel;
    QLineEdit *IDLineEdit;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *sexLabel;
    QComboBox *sexComboBox;
    QLabel *birthdayLabel;
    QDateEdit *birthdayDateEdit;
    QLabel *cardDateLabel;
    QDateEdit *cardDateEdit;
    QLabel *IDCardLabel;
    QLineEdit *IDCardLineEdit;
    QLabel *phoneLabel;
    QLineEdit *phoneLineEdit;
    
    QLabel *stateLabel;
    QComboBox *stateComboBox;
    QPushButton *okButton;
    QPushButton *cancelButton;

    const QString &num;
    const QString &user_name;
};

#endif // RETURNBOOKINFODIALOG_H
