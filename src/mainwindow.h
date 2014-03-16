#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "userlogindialog.h"
#include <QtGui/QMainWindow>
#include <QSqlDatabase>
#include <QPrinter>

class QAction;
class QMenu;
class QToolBar;
class QActionGroup;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void userLoginClicked();
    void userManageClicked();
    void modifyPasswordClicked();
    void userLogoutClicked();
    void bookManageClicked();
    void readerManageClicked();
    void logManageClicked();
    void borrowBooksClicked();
    void returnBooksClicked();
    void renewBooksClicked();
    void statisticsClicked();
    void print();
    void printPreview(QPrinter *printer);
    void readerQueryBookClicked();
    void readerFineInfoClicked();
    void readerRenewBookClicked();
    void settingClicked();

private slots:
    void closeWidget(int);
    void styleChanged(QAction*);

private:
    void createActions();
    void createMenu();
    void createToolBars();
    void createStatusBar();
    bool isExist(const QString &str) const;
    void setNormalAction();
    void setOpAction();
    void setAdAction();
    void setLogout();

private:
    QMenu *systemMenu;
    QToolBar *systemToolBar;
    QAction *userLoginAction;
    QAction *userManageAction;
    QAction *modifyPasswordAction;
    QAction *userLogoutAction;
    QAction *exitAction;

    QMenu *dataMenu;
    QToolBar *dataToolBar;
    QAction *bookManageAction;
    QAction *readerManageAction;
    QAction *logManageAction;
    QAction *setAction;

    QMenu *borrowrMenu;
    QToolBar *borrowrToolBar;
    QAction *borrowBookAction;
    QAction *returnBookAction;
    QAction *renewBookAction;
    QAction *statisticsAction;

    QMenu *readerMenu;
    QToolBar *readerToolBar;
    QAction *readerQueryBookAction;
    QAction *readerFineInfoAction;
    QAction *readerRenewBookAction;

    QMenu *helpMenu;
    QToolBar *helpToolBar;
    QActionGroup *actionGroup;
    QAction *helpAction;
    QAction *aboutAction;

    QTabWidget *tabWidget;

    UserLoginDialog userLoginDialog;

    QAction *printAction;

    QPrinter printer;

    int power;
};

#endif // MAINWINDOW_H
