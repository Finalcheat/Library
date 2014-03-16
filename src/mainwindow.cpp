#include "mainwindow.h"
#include "userlogindialog.h"
#include "usermanagewidget.h"
#include "modifypassworddialog.h"
#include "bookmanagewidget.h"
#include "readmanagewidget.h"
#include "logmanagewidget.h"
#include "borrowbookwidget.h"
#include "renewbookwidget.h"
#include "returnbookswidget.h"
#include "statisticswidget.h"
#include "readerbooksmanagewidget.h"
#include "readerfineinfowidget.h"
#include "readerquerybookwidget.h"
#include "settingdialog.h"
#include <QMenu>
#include <QMenuBar>
#include <QTabWidget>
#include <QAction>
#include <QIcon>
#include <QToolBar>
#include <QDebug>
#include <QPrintDialog>
#include <QPrinter>
#include <QTextDocument>
#include <QPrintPreviewDialog>
#include <QMessageBox>
#include <QPainter>
#include <QInputDialog>
#include <QActionGroup>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), printer(QPrinter::HighResolution)
{
    createActions();
    createMenu();
    createToolBars();
    createStatusBar();

    tabWidget = new QTabWidget;
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    setCentralWidget(tabWidget);

    setLogout();
    setWindowTitle(tr("Library"));
    setWindowIcon(QIcon(":/images/library.png"));

    resize(1370, 750);


    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeWidget(int)));

}

MainWindow::~MainWindow()
{
//    qDebug() << "yes";
}

void MainWindow::createActions()
{
    userLoginAction = new QAction(tr("&User Login"), this);
    userLoginAction->setIcon(QIcon(":/images/user.png"));
    userLoginAction->setShortcut(tr("Ctrl+N"));
    userLoginAction->setStatusTip(tr("Library User Login"));
    connect(userLoginAction, SIGNAL(triggered()), this, SLOT(userLoginClicked()));

    userManageAction = new QAction(tr("&User Manage"), this);
    userManageAction->setIcon(QIcon(":/images/usermanage.png"));
    userManageAction->setStatusTip(tr("Library User Manage"));
    connect(userManageAction, SIGNAL(triggered()), this, SLOT(userManageClicked()));

    modifyPasswordAction = new QAction(tr("Mod&ify Password"), this);
    modifyPasswordAction->setIcon(QIcon(":/images/passwordmodify.png"));
    modifyPasswordAction->setStatusTip(tr("Modify User Login Password"));
    connect(modifyPasswordAction, SIGNAL(triggered()), this, SLOT(modifyPasswordClicked()));

    userLogoutAction = new QAction(tr("Use&r Logout"), this);
    userLogoutAction->setIcon(QIcon(":/images/logout.png"));
    userLogoutAction->setStatusTip(tr("Library User Logout"));
    connect(userLogoutAction, SIGNAL(triggered()), this, SLOT(userLogoutClicked()));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setIcon(QIcon(":/images/exit.png"));
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));


    bookManageAction = new QAction(tr("B&ook Manage"), this);
    bookManageAction->setIcon(QIcon(":/images/bookmanage.png"));
    bookManageAction->setStatusTip(tr("Library Book Manage"));
    connect(bookManageAction, SIGNAL(triggered()), this, SLOT(bookManageClicked()));

    readerManageAction = new QAction(tr("Re&ader Manage"), this);
    readerManageAction->setIcon(QIcon(":/images/readermanage.png"));
    readerManageAction->setStatusTip(tr("Library Reader Manage"));
    connect(readerManageAction, SIGNAL(triggered()), this, SLOT(readerManageClicked()));

    logManageAction = new QAction(tr("Log Manage"), this);
    logManageAction->setIcon(QIcon(":/images/logmanage.png"));
    logManageAction->setStatusTip(tr("Library System Log Manage"));
    connect(logManageAction, SIGNAL(triggered()), this, SLOT(logManageClicked()));

    setAction = new QAction(tr("Setting"), this);
    connect(setAction, SIGNAL(triggered()), this, SLOT(settingClicked()));

    borrowBookAction = new QAction(tr("Borrow Books"), this);
    borrowBookAction->setIcon(QIcon(":/images/borrowbooks.png"));
    borrowBookAction->setStatusTip(tr("Borrow Library Books"));
    connect(borrowBookAction, SIGNAL(triggered()), this, SLOT(borrowBooksClicked()));

    returnBookAction = new QAction(tr("Return Books"), this);
    returnBookAction->setIcon(QIcon(":/images/returnbooks.png"));
    returnBookAction->setStatusTip(tr("Return Books"));
    connect(returnBookAction, SIGNAL(triggered()), this, SLOT(returnBooksClicked()));

    renewBookAction = new QAction(tr("Renew Books"), this);
    renewBookAction->setIcon(QIcon(":/images/renewbooks.png"));
    renewBookAction->setStatusTip(tr("Renew Books"));
    connect(renewBookAction, SIGNAL(triggered()), this, SLOT(renewBooksClicked()));

    statisticsAction = new QAction(tr("Statistics"), this);
    statisticsAction->setIcon(QIcon(":/images/statistics.png"));
    statisticsAction->setStatusTip(tr("Statistics Query"));
    connect(statisticsAction, SIGNAL(triggered()), this, SLOT(statisticsClicked()));

    printAction = new QAction(tr("Print"), this);
    printAction->setIcon(QIcon(":/images/print.png"));
    printAction->setStatusTip(tr("Print Data"));
    connect(printAction, SIGNAL(triggered()), this, SLOT(print()));

    helpAction = new QAction(tr("Help"), this);
    helpAction->setStatusTip(tr("Help the user use library system"));

    aboutAction = new QAction(tr("Abou&t"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));


    readerQueryBookAction = new QAction(tr("Query Book"), this);
    readerQueryBookAction->setIcon(QIcon(":/images/bookmanage.png"));
    connect(readerQueryBookAction, SIGNAL(triggered()), this, SLOT(readerQueryBookClicked()));

    readerFineInfoAction = new QAction(tr("Fine Info"), this);
    readerFineInfoAction->setIcon(QIcon(":/images/logmanage.png"));
    connect(readerFineInfoAction, SIGNAL(triggered()), this, SLOT(readerFineInfoClicked()));

    readerRenewBookAction = new QAction(tr("Reader Book"), this);
    readerRenewBookAction->setIcon(QIcon(":/images/renewbooks.png"));
    connect(readerRenewBookAction, SIGNAL(triggered()), this, SLOT(readerRenewBookClicked()));


    actionGroup = new QActionGroup(this);

    //    qApp->setStyle("Plastique");
    actionGroup->addAction("Plastique")->setCheckable(true);
    actionGroup->addAction("Cleanlooks")->setCheckable(true);
    actionGroup->addAction("Windows")->setCheckable(true);
    actionGroup->addAction("WindowsXp")->setCheckable(true);
    QAction *windowsVistaAction = actionGroup->addAction("WindowsVista");
    windowsVistaAction->setCheckable(true);
    windowsVistaAction->setChecked(true);
    actionGroup->addAction("Motif")->setCheckable(true);
    actionGroup->addAction("CDE")->setCheckable(true);
    connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(styleChanged(QAction*)));
}

void MainWindow::createMenu()
{
    systemMenu = menuBar()->addMenu(tr("&System"));
    systemMenu->addAction(userLoginAction);
    systemMenu->addAction(userManageAction);
    systemMenu->addAction(modifyPasswordAction);
    systemMenu->addAction(userLogoutAction);
    systemMenu->addAction(exitAction);

    dataMenu = menuBar()->addMenu(tr("&Data"));
    dataMenu->addAction(bookManageAction);
    dataMenu->addAction(readerManageAction);
    dataMenu->addAction(logManageAction);
    dataMenu->addAction(setAction);

    borrowrMenu = menuBar()->addMenu(tr("Bor&row"));
    borrowrMenu->addAction(borrowBookAction);
    borrowrMenu->addAction(returnBookAction);
    borrowrMenu->addAction(renewBookAction);
    borrowrMenu->addAction(statisticsAction);

    readerMenu = menuBar()->addMenu(tr("&Reader Operation"));
    readerMenu->addAction(readerQueryBookAction);
    readerMenu->addAction(readerFineInfoAction);
    readerMenu->addAction(readerRenewBookAction);

    helpMenu = menuBar()->addMenu(tr("He&lp"));
    helpMenu->addAction(printAction);
    helpMenu->addMenu(tr("&Style"))->addActions(actionGroup->actions());
    helpMenu->addAction(helpAction);
    helpMenu->addAction(aboutAction);
}

void MainWindow::createToolBars()
{
    systemToolBar = addToolBar(tr("&systemToolBar"));
    systemToolBar->addAction(userLoginAction);
    systemToolBar->addAction(userManageAction);
    systemToolBar->addAction(modifyPasswordAction);
    systemToolBar->addAction(userLogoutAction);

    dataToolBar = addToolBar(tr("dataToolBar"));
    dataToolBar->addAction(bookManageAction);
    dataToolBar->addAction(readerManageAction);
    dataToolBar->addAction(logManageAction);

    borrowrToolBar = addToolBar(tr("borrowrToolBar"));
    borrowrToolBar->addAction(borrowBookAction);
    borrowrToolBar->addAction(returnBookAction);
    borrowrToolBar->addAction(renewBookAction);
    borrowrToolBar->addAction(statisticsAction);

    readerToolBar = addToolBar(tr("readerToolBar"));
    readerToolBar->addAction(readerQueryBookAction);
    readerToolBar->addAction(readerFineInfoAction);
    readerToolBar->addAction(readerRenewBookAction);

    helpToolBar = addToolBar(tr("helpToolBar"));
    helpToolBar->addAction(printAction);
}

void MainWindow::createStatusBar()
{
    statusBar();
}

void MainWindow::closeWidget(int index)
{
    delete tabWidget->widget(index);
}

void MainWindow::userLoginClicked()
{
    if (userLoginDialog.exec())
    {
//        db = temp.getDB();
        power = userLoginDialog.getPower();
//        qDebug() << power;
        if (power == 0)
        {
            setNormalAction();
        }
        else if (power == 1)
        {
            setOpAction();
        }
        else
        {
            setAdAction();
        }
//        user_name = userLoginDialog.getUserName();
    }
}

void MainWindow::userLogoutClicked()
{
    userLoginDialog.clear();
    setLogout();
}

void MainWindow::setLogout()
{
//    for (int i = 0; i < tabWidget->count(); ++i)
//    {
//        delete tabWidget->widget(i);
//    }

    tabWidget->clear();

    userLoginAction->setEnabled(true);
    userManageAction->setVisible(false);
    modifyPasswordAction->setVisible(false);
    userLogoutAction->setEnabled(false);

    dataMenu->menuAction()->setVisible(false);
    dataToolBar->setVisible(false);

    borrowrMenu->menuAction()->setVisible(false);
    borrowrToolBar->setVisible(false);

    readerMenu->menuAction()->setVisible(false);
    readerToolBar->setVisible(false);
}

void MainWindow::setNormalAction()
{
    userLoginAction->setEnabled(false);
    userManageAction->setVisible(false);
    userLogoutAction->setEnabled(true);
    modifyPasswordAction->setVisible(true);

    dataMenu->menuAction()->setVisible(false);
    dataToolBar->setVisible(false);

    borrowrMenu->menuAction()->setVisible(false);
    borrowrToolBar->setVisible(false);

    readerMenu->menuAction()->setVisible(true);
    readerToolBar->setVisible(true);
}

void MainWindow::setOpAction()
{
    userLoginAction->setEnabled(false);
    userManageAction->setVisible(false);
    userLogoutAction->setEnabled(true);
    modifyPasswordAction->setVisible(true);

    dataMenu->menuAction()->setVisible(true);
    dataToolBar->setVisible(true);
    bookManageAction->setVisible(false);
    readerManageAction->setVisible(true);
    logManageAction->setVisible(false);
    setAction->setVisible(false);

    borrowrMenu->menuAction()->setVisible(true);
    borrowrToolBar->setVisible(true);
    statisticsAction->setVisible(false);

    readerMenu->menuAction()->setVisible(false);
    readerToolBar->setVisible(false);
}

void MainWindow::setAdAction()
{
    userLoginAction->setEnabled(false);
    userManageAction->setVisible(true);
    userLogoutAction->setEnabled(true);
    modifyPasswordAction->setVisible(true);

    dataMenu->menuAction()->setVisible(true);
    dataToolBar->setVisible(true);
    bookManageAction->setVisible(true);
    logManageAction->setVisible(true);
    setAction->setVisible(true);

    borrowrMenu->menuAction()->setVisible(true);
    borrowrToolBar->setVisible(true);
    statisticsAction->setVisible(true);

    readerMenu->menuAction()->setVisible(true);
    readerToolBar->setVisible(true);
}

bool MainWindow::isExist(const QString &str) const
{
    for (int i = 0; i < tabWidget->count(); ++i)
    {
        if (tabWidget->tabText(i) == str)
        {
            tabWidget->setCurrentIndex(i);
            return true;
        }
    }
    return false;
}

void MainWindow::userManageClicked()
{
    if (isExist(tr("User Manage")))
        return;

    UserManageWidget *widget = new UserManageWidget(userLoginDialog.getUserName());
    tabWidget->addTab(widget, tr("User Manage"));
    tabWidget->setCurrentWidget(widget);
}

void MainWindow::modifyPasswordClicked()
{
    QString userName = userLoginDialog.getUserName();
    ModifyPasswordDialog temp(userName);
    temp.exec();
}

void MainWindow::bookManageClicked()
{
    if (isExist(tr("Book Manage")))
        return;

    BookManageWidget *widget = new BookManageWidget(userLoginDialog.getUserName());
    tabWidget->addTab(widget, tr("Book Manage"));
    tabWidget->setCurrentWidget(widget);
}

void MainWindow::readerManageClicked()
{
    if (isExist(tr("Reader Manage")))
        return;

    ReaderManageWidget *widget = new ReaderManageWidget(userLoginDialog.getUserName());
    tabWidget->addTab(widget, tr("Reader Manage"));
    tabWidget->setCurrentWidget(widget);
}

void MainWindow::logManageClicked()
{
    if (isExist(tr("Log Manage")))
        return;

    LogManageWidget *widget = new LogManageWidget;
    tabWidget->addTab(widget, tr("Log Manage"));
    tabWidget->setCurrentWidget(widget);
}

void MainWindow::borrowBooksClicked()
{
    if (isExist(tr("Borrow Books")))
        return;

    BorrowBookWidget *widget = new BorrowBookWidget(userLoginDialog.getUserName());
    tabWidget->addTab(widget, tr("Borrow Books"));
    tabWidget->setCurrentWidget(widget);
}

void MainWindow::returnBooksClicked()
{
    if (isExist(tr("Return Books")))
        return;

    ReturnBooksWidget *widget = new ReturnBooksWidget(userLoginDialog.getUserName());
    tabWidget->addTab(widget, tr("Return Books"));
    tabWidget->setCurrentWidget(widget);
}

void MainWindow::renewBooksClicked()
{
    if(isExist(tr("Renew Books")))
        return;

    RenewBookWidget *widget = new RenewBookWidget(userLoginDialog.getUserName());
    tabWidget->addTab(widget, tr("Renew Books"));
    tabWidget->setCurrentWidget(widget);
}

void MainWindow::statisticsClicked()
{
    if (isExist(tr("Statistics")))
        return;

    StatisticsWidget *widget = new StatisticsWidget;
    tabWidget->addTab(widget, tr("Statistics"));
    tabWidget->setCurrentWidget(widget);
}

void MainWindow::print()
{

//    QPrintDialog printDialog(&printer, this);

//    if (preview.exec())
//    {
//        QTextDocument textDocument;
//        textDocument.setHtml("00");
//        textDocument.print(&printer);
//    }

    QPrintPreviewDialog preview(&printer,this);
//    preview.setWindowFlags(Qt::WindowMinimizeButtonHint);
    preview.resize(1000, 750);
    preview.setWindowTitle(QString::fromLocal8Bit("¥Ú”°‘§¿¿"));

    connect(&preview, SIGNAL(paintRequested(QPrinter *)),this,SLOT(printPreview(QPrinter *)));
    preview.exec();

}

void MainWindow::printPreview(QPrinter *printer)
{
//    QString html = "<table width=\"100%\" align=center border=1 cellspacing=0>\n"
//            "<tr><td bgcolor=\"lightgray\"><font size=\"+4\">"
//            "<b><i>title</i></b></font>\n<tr><td>body\n</table>\n<br>\n";

//    QString html = "<table border=\"1\">"
//            "<tr>"
//            "<td>row 1, cell 1</td>"
//            "<td>row 1, cell 2</td>"
//            "</tr>"
//            "<tr>"
//            "<td>row 2, cell 1</td>"
//            "<td>&nbsp;</td>"
//            "</tr>"
//            "</table>";

    QString html = "<table border=\"3\" width=\"100%\" cellpadding=\"5\">";
    QWidget *widget = tabWidget->currentWidget();

    if (!widget)
    {
        QTextDocument textDocument;
        textDocument.setHtml(html);
        textDocument.print(printer);
        return;
    }

//    bool ok = false;
//    QString caption = QInputDialog::getText(this, tr("Please input caption"),
//                                                 tr("Save new table name:"),
//                                                 QLineEdit::Normal, tr("Caption Name"),
//                                                 &ok, 0, Qt::ImhNoPredictiveText);

//    ok = !caption.isEmpty() && ok;
//    if (ok)
//    {
//        html += "<caption align=center cellspacing=5>";
//        html += Qt::escape(caption);
//        html += "</caption>";
//    }

    QString className = widget->metaObject()->className();
//    qDebug() << className;
    if (className == "ReaderBooksManageWidget")
    {
        html += static_cast<ReaderBooksManageWidget*>(widget)->getHeaderDate();
        html += static_cast<ReaderBooksManageWidget*>(widget)->getModelData();
        html += "</table>";
    }
    else if (className == "ReaderFineInfoWidget")
    {
        html += static_cast<ReaderFineInfoWidget*>(widget)->getHeaderDate();
        html += static_cast<ReaderFineInfoWidget*>(widget)->getModelData();
        html += "</table>";
    }
    else if (className == "ReaderQueryBookWidget")
    {
        html += static_cast<ReaderQueryBookWidget*>(widget)->getHeaderDate();
        html += static_cast<ReaderQueryBookWidget*>(widget)->getModelData();
        html += "</table>";
    }
    else if (className == "BookManageWidget")
    {
        html += static_cast<BookManageWidget*>(widget)->getHeaderDate();
        html += static_cast<BookManageWidget*>(widget)->getModelData();
        html += "</table>";
//        qDebug() << html;
    }
    else if (className == "BorrowBookWidget")
    {
        html += static_cast<BorrowBookWidget*>(widget)->getHeaderDate();
        html += static_cast<BorrowBookWidget*>(widget)->getModelData();
        html += "</table>";
    }
    else if (className == "LogManageWidget")
    {
        html += static_cast<LogManageWidget*>(widget)->getHeaderDate();
        html += static_cast<LogManageWidget*>(widget)->getModelData();
        html += "</table>";
    }
    else if (className == "ReaderManageWidget")
    {
        html += static_cast<ReaderManageWidget*>(widget)->getHeaderDate();
        html += static_cast<ReaderManageWidget*>(widget)->getModelData();
        html += "</table>";
    }
    else if (className == "RenewBookWidget")
    {
        html += static_cast<RenewBookWidget*>(widget)->getHeaderDate();
        html += static_cast<RenewBookWidget*>(widget)->getModelData();
        html += "</table>";
    }
    else if (className == "ReturnBooksWidget")
    {
        html += static_cast<ReturnBooksWidget*>(widget)->getHeaderDate();
        html += static_cast<ReturnBooksWidget*>(widget)->getModelData();
        html += "</table>";
    }
    else if (className == "StatisticsWidget")
    {
        html += static_cast<StatisticsWidget*>(widget)->getHeaderDate();
        html += static_cast<StatisticsWidget*>(widget)->getModelData();
        html += "</table>";
    }
    else
    {
        html += static_cast<UserManageWidget*>(widget)->getHeaderDate();
        html += static_cast<UserManageWidget*>(widget)->getModelData();
        html += "</table>";
    }

    QTextDocument textDocument;
    textDocument.setHtml(html);
    textDocument.print(printer);

}

void MainWindow::readerQueryBookClicked()
{
    if (isExist(tr("Query Books")))
        return;

    ReaderQueryBookWidget *widget = new ReaderQueryBookWidget;
    tabWidget->addTab(widget, tr("Query Books"));
    tabWidget->setCurrentWidget(widget);
}

void MainWindow::readerFineInfoClicked()
{
    if (isExist(tr("Fine Information")))
        return;

    ReaderFineInfoWidget *widget = new ReaderFineInfoWidget(userLoginDialog.getUserName(), power);
    tabWidget->addTab(widget, tr("Fine Information"));
    tabWidget->setCurrentWidget(widget);
}

void MainWindow::readerRenewBookClicked()
{
    if (isExist(tr("Reader Books")))
        return;

    ReaderBooksManageWidget *widget = new ReaderBooksManageWidget(userLoginDialog.getUserName(), power);
    tabWidget->addTab(widget, tr("Reader Books"));
    tabWidget->setCurrentWidget(widget);
}

void MainWindow::settingClicked()
{
    SettingDialog temp;
    temp.exec();
}

void MainWindow::styleChanged(QAction *a)
{
    QApplication::setStyle(a->text());
}
