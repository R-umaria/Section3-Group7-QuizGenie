QT       += core gui
QT += svg
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x060000 # disables all APIs deprecated in Qt 6.0.0 and earlier

# Input
QT += core gui widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    home_screen.cpp \
    login_screen.cpp \
    main.cpp \
    quiz_screen.cpp \
    client.cpp

HEADERS += \
    home_screen.h \
    login_screen.h \
    quiz_screen.h \
    client.h

FORMS += \
    home_screen.ui \
    login_screen.ui \
    quiz_screen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# New project name
TARGET = Client

RESOURCES += \
    resources.qrc

# Ensure the CSV file is included in the project
DISTFILES += UploadedPDFs/mcq_output.csv
