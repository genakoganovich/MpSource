#-------------------------------------------------
#
# Project created by QtCreator 2013-10-14T17:36:40
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SeiSeeMp
TEMPLATE = app
CONFIG += warn_off

SOURCES += main.cpp\
    edithdrdialog.cpp \
    log.cpp \
        mainwindow.cpp \
    procparmdialog.cpp \
    aboutdialog.cpp \
    axisdialog.cpp \
    workthread.cpp \
    saveasdialog.cpp \
    xmlread.cpp

HEADERS  += mainwindow.h \
    edithdrdialog.h \
    log.h \
    procparmdialog.h \
    aboutdialog.h \
    axisdialog.h \
    workthread.h \
    saveasdialog.h \
    xmlread.h

FORMS    += mainwindow.ui \
    edithdrdialog.ui \
    procparmdialog.ui \
    aboutdialog.ui \
    axisdialog.ui \
    saveasdialog.ui

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libExprEval/release/ -llibExprEval
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libExprEval/debug/ -llibExprEval
else:unix: LIBS += -L$$OUT_PWD/../libExprEval/ -llibExprEval

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libExprEval/release/ -llibExprEval
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libExprEval/debug/ -llibExprEval
else:unix: LIBS += -L$$OUT_PWD/../libExprEval/ -llibExprEval

INCLUDEPATH += $$PWD/../libExprEval
DEPENDPATH += $$PWD/../libExprEval

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libExprEval/release/liblibExprEval.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libExprEval/debug/liblibExprEval.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libExprEval/release/libExprEval.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libExprEval/debug/libExprEval.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libExprEval/liblibExprEval.a
