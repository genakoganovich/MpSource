#-------------------------------------------------
#
# Project created by QtCreator 2013-10-14T17:36:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SegDSeeMp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    procparmdialog.cpp \
    readerthread.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    compatx.h \
    procparmdialog.h \
    readerthread.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    procparmdialog.ui \
    aboutdialog.ui

# ADD THIS LINE!
RC_FILE += app.rc

RESOURCES += \
    myrc.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GxLib/release/ -lGxLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GxLib/debug/ -lGxLib
else:unix: LIBS += -L$$OUT_PWD/../GxLib/ -lGxLib

INCLUDEPATH += $$PWD/../GxLib
DEPENDPATH += $$PWD/../GxLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../GxLib/release/libGxLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../GxLib/debug/libGxLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../GxLib/release/GxLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../GxLib/debug/GxLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../GxLib/libGxLib.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libSegD/release/ -llibSegD
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libSegD/debug/ -llibSegD
else:unix: LIBS += -L$$OUT_PWD/../libSegD/ -llibSegD

INCLUDEPATH += $$PWD/../libSegD
DEPENDPATH += $$PWD/../libSegD

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libSegD/release/liblibSegD.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libSegD/debug/liblibSegD.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libSegD/release/libSegD.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libSegD/debug/libSegD.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libSegD/liblibSegD.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libUtil2/release/ -llibUtil2
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libUtil2/debug/ -llibUtil2
else:unix: LIBS += -L$$OUT_PWD/../libUtil2/ -llibUtil2

INCLUDEPATH += $$PWD/../libUtil2
DEPENDPATH += $$PWD/../libUtil2

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libUtil2/release/liblibUtil2.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libUtil2/debug/liblibUtil2.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libUtil2/release/libUtil2.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libUtil2/debug/libUtil2.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libUtil2/liblibUtil2.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libCwp/release/ -llibCwp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libCwp/debug/ -llibCwp
else:unix: LIBS += -L$$OUT_PWD/../libCwp/ -llibCwp

INCLUDEPATH += $$PWD/../libCwp
DEPENDPATH += $$PWD/../libCwp

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libCwp/release/liblibCwp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libCwp/debug/liblibCwp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libCwp/release/libCwp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libCwp/debug/libCwp.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libCwp/liblibCwp.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libCwp/release/ -llibCwp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libCwp/debug/ -llibCwp
else:unix: LIBS += -L$$OUT_PWD/../libCwp/ -llibCwp

INCLUDEPATH += $$PWD/../libCwp
DEPENDPATH += $$PWD/../libCwp

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libCwp/release/liblibCwp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libCwp/debug/liblibCwp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libCwp/release/libCwp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libCwp/debug/libCwp.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libCwp/liblibCwp.a
