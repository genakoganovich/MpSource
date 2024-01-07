#-------------------------------------------------
#
# Project created by QtCreator 2015-06-23T10:08:09
#
#-------------------------------------------------

QT       += widgets

TARGET = libCwp
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    cwp.cpp \
    pfafft.cpp \
    complex.cpp

HEADERS += \
    cwp.h \

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
