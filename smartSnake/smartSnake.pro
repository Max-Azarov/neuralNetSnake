QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#TEMPLATE = app

SOURCES += \
    game/game.cpp \
    logOut.cpp \
    main.cpp \
    neuroNet/biasNeuron.cpp \
    neuroNet/hiddenNeuron.cpp \
    neuroNet/inputNeuron.cpp \
    neuroNet/net.cpp \
    neuroNet/neuron.cpp \
    neuroNet/outputNeuron.cpp \
    neuroNet/parameters.cpp \
    neuroNet/synapse.cpp \
    neuroNet/training.cpp \
    snake/choiseDirection.cpp \
    snake/learning.cpp \
    snake/snake.cpp \
    snake/writeInputData.cpp

HEADERS += \
    game/game.h \
    logOut.h \
    neuroNet/_neuronet.h \
    neuroNet/biasNeuron.h \
    neuroNet/factory.h \
    neuroNet/hiddenNeuron.h \
    neuroNet/inputNeuron.h \
    neuroNet/net.h \
    neuroNet/neuron.h \
    neuroNet/outputNeuron.h \
    neuroNet/parameters.h \
    neuroNet/synapse.h \
    neuroNet/training.h \
    snake/choiseDirection.h \
    snake/enums.h \
    snake/learning.h \
    snake/snake.h \
    snake/writeInputData.h

FORMS += resources/mainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    snake/source/body.png \
    snake/source/fruit.png \
    snake/source/head.png \
    snake/source/wall.png
