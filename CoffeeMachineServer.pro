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
    buttonsWidgetsCpp/lookWidgetsCpp/alldrinkswidget.cpp \
    buttonsWidgetsCpp/lookWidgetsCpp/allsyrupswidget.cpp \
    main.cpp \
    coffeemachine.cpp \
    order.cpp

HEADERS += \
    buttonsWidgetsHeader/addWidgetsHeader/newdrinkwidget.h \
    buttonsWidgetsHeader/addWidgetsHeader/newsyrupwidget.h \
    buttonsWidgetsHeader/changeWidgetsHeader/changepricedrinkwidget.h \
    buttonsWidgetsHeader/changeWidgetsHeader/changepricesyrupwidget.h \
    buttonsWidgetsHeader/deleteWidgetsHeader/deletesomedrinkwidget.h \
    buttonsWidgetsHeader/deleteWidgetsHeader/deletesomesyrupwidget.h \
    buttonsWidgetsHeader/lookWidgetsHeader/alldrinkswidget.h \
    buttonsWidgetsHeader/lookWidgetsHeader/allsyrupswidget.h \
    coffeemachine.h \
    order.h

FORMS += \
    buttonsWidgetsUi/addWidgetsUi/newdrinkwidget.ui \
    buttonsWidgetsUi/addWidgetsUi/newsyrupwidget.ui \
    buttonsWidgetsUi/changeWidgetsUi/changepricedrinkwidget.ui \
    buttonsWidgetsUi/changeWidgetsUi/changepricesyrupwidget.ui \
    buttonsWidgetsUi/deleteWidgetsUi/deletesomedrinkwidget.ui \
    buttonsWidgetsUi/deleteWidgetsUi/deletesomesyrupwidget.ui \
    buttonsWidgetsUi/lookWidgetsUi/alldrinkswidget.ui \
    buttonsWidgetsUi/lookWidgetsUi/allsyrupswidget.ui \
    coffeemachine.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
