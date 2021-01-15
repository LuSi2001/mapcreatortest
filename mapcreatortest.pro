#-------------------------------------------------
#
# Project created by QtCreator 2021-01-11T09:33:55
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mapcreatortest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        autoplungeritem.cpp \
        ballcounterfield.cpp \
        ballcounthandler.cpp \
        ballitem.cpp \
        binaryreader.cpp \
        boardlistgroupbox.cpp \
        bumperitem.cpp \
        circleitem.cpp \
        coinitem.cpp \
        collisionengine.cpp \
        compoundobjectitem.cpp \
        editorscene.cpp \
        endzone.cpp \
        fielditem.cpp \
        fieldlistgroupbox.cpp \
        flipperitem.cpp \
        flipperleftitem.cpp \
        flipperlistgroupbox.cpp \
        flipperrightitem.cpp \
        geometrylib.cpp \
        itembox.cpp \
        itemfactory.cpp \
        itemlistgroupbox.cpp \
        itemsgroupbox.cpp \
        main.cpp \
        mainwindow.cpp \
        physicformulas.cpp \
        pinballitem.cpp \
        plungeritem.cpp \
        plungerlistgroupbox.cpp \
        pointmultiplierzone.cpp \
        polygonitem.cpp \
        readerproxy.cpp \
        scorefielditem.cpp \
        scorehandler.cpp \
        slingshotitem.cpp \
        timerfielditem.cpp \
        velocityengine.cpp \
        view.cpp \
        wallitem.cpp \
        xmlreader.cpp \
        zone.cpp \
        zonelistgroupbox.cpp

HEADERS += \
        autoplungeritem.h \
        ballcounterfield.h \
        ballcounthandler.h \
        ballitem.h \
        binaryreader.h \
        boardlistgroupbox.h \
        bumperitem.h \
        circleitem.h \
        coinitem.h \
        collisionengine.h \
        compoundobjectitem.h \
        constants.h \
        editorscene.h \
        endzone.h \
        fielditem.h \
        fieldlistgroupbox.h \
        flipperitem.h \
        flipperleftitem.h \
        flipperlistgroupbox.h \
        flipperrightitem.h \
        geometrylib.h \
        itembox.h \
        itemfactory.h \
        itemlistgroupbox.h \
        itemsgroupbox.h \
        mainwindow.h \
        physicformulas.h \
        pinballitem.h \
        plungeritem.h \
        plungerlistgroupbox.h \
        pointmultiplierzone.h \
        polygonitem.h \
        readerproxy.h \
        scorefielditem.h \
        scorehandler.h \
        slingshotitem.h \
        stringeditor.h \
        timeconverter.h \
        timerfielditem.h \
        utils.h \
        vector.h \
        velocityengine.h \
        view.h \
        wallitem.h \
        xmlreader.h \
        zone.h \
        zonelistgroupbox.h

FORMS += \
        boardlistgroupbox.ui \
        fieldlistgroupbox.ui \
        flipperlistgroupbox.ui \
        itemlistgroupbox.ui \
        itemsgroupbox.ui \
        mainwindow.ui \
        plungerlistgroupbox.ui \
        zonelistgroupbox.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    item_config.xml
