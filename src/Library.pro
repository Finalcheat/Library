#-------------------------------------------------
#
# Project created by QtCreator 2012-09-01T10:04:32
#
#-------------------------------------------------

QT += core gui
QT += sql
QT += xml
QT += network

TARGET = Library
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    userlogindialog.cpp \
    usermanagewidget.cpp \
    modifypassworddialog.cpp \
    bookmanagewidget.cpp \
    readmanagewidget.cpp \
    logmanagewidget.cpp \
    borrowbookwidget.cpp \
    returnbookswidget.cpp \
    renewbookwidget.cpp \
    statisticswidget.cpp \
    userdialog.cpp \
    bookinfodialog.cpp \
    readerinfodialog.cpp \
    borrowbookinfodialog.cpp \
    returnbookinfodialog.cpp \
    readerbooksmanagewidget.cpp \
    HttpGet.cpp \
    readerquerybookwidget.cpp \
    readerfineinfowidget.cpp \
    settingdialog.cpp

HEADERS  += mainwindow.h \
    userlogindialog.h \
    usermanagewidget.h \
    modifypassworddialog.h \
    bookmanagewidget.h \
    readmanagewidget.h \
    logmanagewidget.h \
    borrowbookwidget.h \
    returnbookswidget.h \
    renewbookwidget.h \
    statisticswidget.h \
    userdialog.h \
    bookinfodialog.h \
    readerinfodialog.h \
    borrowbookinfodialog.h \
    returnbookinfodialog.h \
    readerbooksmanagewidget.h \
    HttpGet.h \
    readerquerybookwidget.h \
    readerfineinfowidget.h \
    settingdialog.h

RESOURCES += \
    Library.qrc

FORMS +=

TRANSLATIONS = Library_zh.ts
