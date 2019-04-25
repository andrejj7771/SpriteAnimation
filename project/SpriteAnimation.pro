QT += gui widgets

CONFIG += c++17 app_bundle

TARGET = SpriteAnimation
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = $$PWD/../bin

INCLUDEPATH += $$PWD/../include

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += $$PWD/../src/main.cpp

SOURCES += $$PWD/../src/Animation/Frame.cpp
SOURCES += $$PWD/../src/Animation/Animation.cpp
SOURCES += $$PWD/../src/Animation/AnimationController.cpp

SOURCES += $$PWD/../src/Scene/Viewport.cpp
SOURCES += $$PWD/../src/Scene/Scene.cpp
SOURCES += $$PWD/../src/Scene/AnimationScene.cpp

SOURCES += $$PWD/../src/Widgets/AnimationWidget/AnimationWidget.cpp

HEADERS += $$PWD/../include/Animation/Frame.h
HEADERS += $$PWD/../include/Animation/Animation.h
HEADERS += $$PWD/../include/Animation/AnimationController.h

HEADERS += $$PWD/../include/Scene/Scene.h
HEADERS += $$PWD/../include/Scene/Viewport.h
HEADERS += $$PWD/../include/Scene/AnimationScene.h

HEADERS += $$PWD/../include/Widgets/AnimationWidget/AnimationWidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += $$PWD/../ui/AnimationWidget/AnimationWidget.ui

RESOURCES += $$PWD/../resources/res.qrc
