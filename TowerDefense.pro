QT       += core gui widgets multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AmareloIcone.cpp \
    AmareloTorre.cpp \
    AzulIcone.cpp \
    AzulTorre.cpp \
    Chefao.cpp \
    CianoIcone.cpp \
    CianoTorre.cpp \
    Dinheiro.cpp \
    Game.cpp \
    Inimigo.cpp \
    LaranjaIcone.cpp \
    LaranjaTorre.cpp \
    Projetil.cpp \
    Score.cpp \
    Torre.cpp \
    Vida.cpp \
    main.cpp

HEADERS += \
    AmareloIcone.h \
    AmareloTorre.h \
    AzulIcone.h \
    AzulTorre.h \
    Chefao.h \
    CianoIcone.h \
    CianoTorre.h \
    Dinheiro.h \
    Game.h \
    Inimigo.h \
    LaranjaIcone.h \
    LaranjaTorre.h \
    Projetil.h \
    Score.h \
    Torre.h \
    Vida.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
