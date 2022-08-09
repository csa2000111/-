QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clientwindow.cpp \
    clinetenquireform.cpp \
    clinetenquirewindow.cpp \
    enquirewindow.cpp \
    goodsstockform.cpp \
    goodswindow.cpp \
    invoiceform.cpp \
    main.cpp \
    loginwindow.cpp \
    purchaseform.cpp \
    purchasewindow.cpp \
    recordform.cpp \
    recordwindow.cpp \
    rootwindow.cpp \
    settlewindow.cpp \
    shoppingform.cpp \
    stockform.cpp \
    useritemform.cpp \
    userwindow.cpp

HEADERS += \
    clientwindow.h \
    clinetenquireform.h \
    clinetenquirewindow.h \
    enquirewindow.h \
    goodsstockform.h \
    goodswindow.h \
    invoiceform.h \
    loginwindow.h \
    purchaseform.h \
    purchasewindow.h \
    recordform.h \
    recordwindow.h \
    rootwindow.h \
    settlewindow.h \
    shoppingform.h \
    stockform.h \
    useritemform.h \
    userwindow.h

FORMS += \
    clientwindow.ui \
    clinetenquireform.ui \
    clinetenquirewindow.ui \
    enquirewindow.ui \
    goodsstockform.ui \
    goodswindow.ui \
    invoiceform.ui \
    loginwindow.ui \
    purchaseform.ui \
    purchasewindow.ui \
    recordform.ui \
    recordwindow.ui \
    rootwindow.ui \
    settlewindow.ui \
    shoppingform.ui \
    stockform.ui \
    useritemform.ui \
    userwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../image/image.qrc

RC_FILE = logo.rc
