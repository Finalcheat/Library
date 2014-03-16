#include <QtCore>
#include <QtNetwork>
#include <QDebug>

#include "HttpGet.h"

HttpGet::HttpGet(QObject *parent)
    : QObject(parent)
{
    connect(&http, SIGNAL(done(bool)), this, SLOT(httpDone(bool)));
    QDir temp;
    temp.mkdir("temp");
}

bool HttpGet::getFile(const QUrl &url)
{
    if (!url.isValid()) {
        qDebug() << "Error: Invalid URL" << endl;
        return false;
    }

    if (url.scheme() != "http") {
        qDebug() << "Error: URL must start with 'http:'" << endl;
        return false;
    }

    if (url.path().isEmpty()) {
        qDebug() << "Error: URL has no path" << endl;
        return false;
    }

    QString localFileName = QFileInfo(url.path()).fileName();
    if (localFileName.isEmpty())
        localFileName = "httpget.out";

    QDir::setCurrent(QDir::currentPath() + "/temp");
    file.setFileName(localFileName + ".xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error: Cannot write file ";
//                  << qPrintable(file.fileName()) << ": "
//                  << qPrintable(file.errorString()) << std::endl;
        return false;
    }

    http.setHost(url.host(), url.port(80));
    http.get(url.path(), &file);
    http.close();
    return true;
}

void HttpGet::httpDone(bool error)
{
    QString fileName = file.fileName();
    file.close();
    if (!error)
    {
        emit done(fileName);
    }
}
