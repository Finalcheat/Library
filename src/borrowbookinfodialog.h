#ifndef BORROWBOOKINFODIALOG_H
#define BORROWBOOKINFODIALOG_H

#include <QDialog>
class QLabel;
class QLineEdit;
class QGroupBox;
class QComboBox;
class QDateEdit;
class QSpinBox;
class QDoubleSpinBox;

class BorrowBookInfoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BorrowBookInfoDialog(const QString &u, const QString &num, QWidget *parent = 0);

private slots:
    void queryClicked();
    void okButtonClicked();

private:
    void initBookInfo(const QString &num);
    
private:
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QPushButton *queryButton;

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

    QPushButton *okButton;
    QPushButton *cancelButton;

    const QString &user_name;
};

#endif // BORROWBOOKINFODIALOG_H
