QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    home_screen.cpp \
    login_screen.cpp \
    main.cpp \
    quiz_screen.cpp

HEADERS += \
    home_screen.h \
    login_screen.h \
    quiz_screen.h

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
