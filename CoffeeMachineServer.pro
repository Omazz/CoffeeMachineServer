QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buttonsWidgetsCpp/addWidgetsCpp/newdrinkwidget.cpp \
    buttonsWidgetsCpp/addWidgetsCpp/newsyrupwidget.cpp \
    buttonsWidgetsCpp/changeWidgetsCpp/changepricedrinkwidget.cpp \
    buttonsWidgetsCpp/changeWidgetsCpp/changepricesyrupwidget.cpp \
    buttonsWidgetsCpp/deleteWidgetsCpp/deletesomedrinkwidget.cpp \
    buttonsWidgetsCpp/deleteWidgetsCpp/deletesomesyrupwidget.cpp \
    main.cpp \
    coffeemachine.cpp \
    order.cpp

HEADERS += \
    changepricedrinkwidget.h \
    changepricesyrupwidget.h \
    coffeemachine.h \
    deletesomedrinkwidget.h \
    deletesomesyrupwidget.h \
    newdrinkwidget.h \
    newsyrupwidget.h \
    order.h

FORMS += \
    changepricedrinkwidget.ui \
    changepricesyrupwidget.ui \
    coffeemachine.ui \
    deletesomedrinkwidget.ui \
    deletesomesyrupwidget.ui \
    newdrinkwidget.ui \
    newsyrupwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
