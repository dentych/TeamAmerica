#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T19:28:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CameraFeed
TEMPLATE = app

SOURCES += \
    camerafeed.cpp \
    genlad.cpp \
    login.cpp \
    main.cpp \
    ../Joystick/Joystick.cpp \
    ../Log/Log.cpp \
    ../Matrix/MatrixKeyboard.cpp \
    ../Protocol/Protocol.cpp \
    ../SPI/SensorsSPI.cpp \
    ../UART/UART.cpp

HEADERS  += \
    camerafeed.h \
    genlad.h \
    login.h \
    ../Joystick/Joystick.h \
    ../Log/Log.h \
    ../Matrix/MatrixKeyboard.h \
    ../Protocol/Protocol.h \
    ../SPI/SensorsSPI.h \
    ../UART/UART.h

INCLUDEPATH += /home/pi/projekt
#INCLUDEPATH += C:/Users/andreas/Documents/skole/PRJ3/Login_Qt4

LIBS += -L/usr/local/lib \
 -lopencv_calib3d \
 -lopencv_contrib \
 -lopencv_core \
 -lopencv_features2d \
 -lopencv_flann \
 -lopencv_gpu \
 -lopencv_highgui \
 -lopencv_imgproc \
 -lopencv_legacy \
 -lopencv_ml \
 -lopencv_nonfree \
 -lopencv_objdetect \
 -lopencv_ocl \
 -lopencv_photo \
 -lopencv_stitching \
 -lopencv_superres \
 #-lopencv_ts \
 -lopencv_video \
 -lopencv_videostab \
 -lwiringPi
