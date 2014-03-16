#include <QtGui/QApplication>
#include <QFile>
#include <QTranslator>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load( ":/translations/Library_zh.qm", "." );
    a.installTranslator( &translator );

    QFile file(":/qss/library.qss");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());

    MainWindow w;
    w.show();
    
    return a.exec();
}
