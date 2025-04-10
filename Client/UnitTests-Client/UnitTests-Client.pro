QT -= gui
QT += core network testlib widgets svg

# Since UnitTests-Client is inside the Client folder,
# set the include path to the parent directory.
INCLUDEPATH += $$PWD/..
DEPENDPATH += $$PWD/..

# Add the client header so that qmake runs moc on it.
HEADERS += $$PWD/../client.h

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += $$PWD/../client.cpp \
           tst_clienttests.cpp
