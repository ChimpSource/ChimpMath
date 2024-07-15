QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    chimpmath.cpp \
    src/browse/browse.cpp \
    src/calculator/calculator.cpp \
    src/graph/graph.cpp \
    src/new/newwindow.cpp \
    src/settings/settings.cpp \
    src/utils/math/math.cpp \
    tests/TestLib/test.cpp \
    tests/math/testmath.cpp \
    tests/unittests.cpp

HEADERS += \
    chimpmath.h \
    src/browse/browse.h \
    src/calculator/calculator.h \
    src/graph/graph.h \
    src/new/newwindow.h \
    src/settings/settings.h \
    src/utils/math/math.h \
    tests/TestLib/test.h \
    tests/math/testmath.h \
    tests/unittests.h

FORMS += \
    chimpmath.ui \
    src/browse/browse.ui \
    src/calculator/calculator.ui \
    src/graph/graph.ui \
    src/new/newwindow.ui \
    src/settings/settings.ui

TRANSLATIONS += \
    ChimpMath_en_AS.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
