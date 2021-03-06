QT       += core gui svg xml sql

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

SOURCES += \
    CustomItem.cpp \
    bkgitem.cpp \
    main.cpp \
    mainwindow.cpp \
    svgitem.cpp

HEADERS += \
    CustomItem.h \
    bkgitem.h \
    mainwindow.h \
    svgitem.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc

win32
{
INCLUDEPATH += D:\ProgramData\OpenCV\opencv\buildForQt\install\include
INCLUDEPATH += D:\ProgramData\OpenCV\opencv\buildForQt\install\include\opencv2

LIBS += -LD:\ProgramData\OpenCV\opencv\buildForQt\install\x64\mingw\bin \
        -llibopencv_calib3d453 \
        -llibopencv_core453 \
        -llibopencv_dnn453 \
        -llibopencv_features2d453 \
        -llibopencv_flann453 \
        -llibopencv_gapi453 \
        -llibopencv_highgui453 \
        -llibopencv_imgcodecs453 \
        -llibopencv_imgproc453 \
        -llibopencv_ml453 \
        -llibopencv_objdetect453 \
        -llibopencv_photo453 \
        -llibopencv_stitching453 \
        -llibopencv_video453 \
        -llibopencv_videoio453\
}
INCLUDEPATH += -I E:\APP\anaconda3\include
LIBS += -LE:\APP\anaconda3\libs -lpython38
