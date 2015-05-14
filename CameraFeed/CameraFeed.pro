#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T19:28:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CameraFeed
TEMPLATE = app

SOURCES += main.cpp\
        camerafeed.cpp\
login.cpp \
    genlad.cpp

HEADERS  += camerafeed.h\
login.h \
    genlad.h

INCLUDEPATH += C:/opencv/build/include
#INCLUDEPATH += C:/Users/andreas/Documents/skole/PRJ3/Login_Qt4

LIBS += -LC:/opencv/build/x64/vc12/lib \
 -lopencv_calib3d2410 \
 -lopencv_contrib2410 \
 -lopencv_core2410 \
 -lopencv_features2d2410 \
 -lopencv_flann2410 \
 -lopencv_gpu2410 \
 -lopencv_highgui2410 \
 -lopencv_imgproc2410 \
 -lopencv_legacy2410 \
 -lopencv_ml2410 \
 -lopencv_nonfree2410 \
 -lopencv_objdetect2410 \
 -lopencv_ocl2410 \
 -lopencv_photo2410 \
 -lopencv_stitching2410 \
 -lopencv_superres2410 \
 -lopencv_ts2410 \
 -lopencv_video2410 \
 -lopencv_videostab2410
