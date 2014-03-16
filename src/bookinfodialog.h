#ifndef BOOKINFODIALOG_H
#define BOOKINFODIALOG_H

#include "HttpGet.h"

#include <QDialog>
class QLabel;
class QLineEdit;
class QDateEdit;
class QSpinBox;
class QDoubleSpinBox;
class QTextEdit;
class QGroupBox;
class QMenu;

class BookInfoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit BookInfoDialog(const QString &u, const QString &num = "", QWidget *parent = 0);

private slots:
    void okClicked();
    void modifyClicked();


private slots:
    void getBookInfo();
    void httpDone(const QString &fileName);
    void textChanged();

private:
    void init();

    
private:
    QGroupBox *groupBox;

    QLabel *ISBNLabel;
    QLineEdit *ISBNLineEdit;
    QPushButton *ISBNButton;

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

    QLabel *summaryLabel;
    QTextEdit *summaryTextEdit;

    QPushButton *okButton;
    QPushButton *cancelButton;

    HttpGet getInfo;

    const QString &str;
    const QString &user_name;
};

#endif // BOOKINFODIALOG_H
