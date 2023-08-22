QT       += core gui widgets
CONFIG   += c++11

SOURCES += gameboard.cpp \
           main.cpp \
           mainwindow.cpp

HEADERS += gameboard.hh \
           mainwindow.hh

FORMS   += mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += mainwindow.qrc
