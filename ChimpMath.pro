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
    src/utils/jsonparser.cpp \

HEADERS += \
    chimpmath.h \
    src/browse/browse.h \
    src/calculator/calculator.h \
    src/graph/graph.h \
    src/new/newwindow.h \
    src/utils/jsonparser.h

FORMS += \
    chimpmath.ui \
    src/browse/browse.ui \
    src/calculator/calculator.ui \
    src/graph/graph.ui \
    src/new/newwindow.ui

TRANSLATIONS += \
    ChimpMath_en_AS.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
