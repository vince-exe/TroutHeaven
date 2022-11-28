QT     += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    application_utilities.cpp \
    home_page_dialog.cpp \
    main.cpp \
    login_window.cpp \
    score_board_dialog.cpp \
    stats_dialog.cpp

HEADERS += \
    application_utilities.h \
    home_page_dialog.h \
    login_window.h \
    score_board_dialog.h \
    stats_dialog.h

FORMS += \
    home_page_dialog.ui \
    login_window.ui \
    score_board_dialog.ui \
    stats_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
