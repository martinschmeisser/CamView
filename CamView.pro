
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CamView
TEMPLATE = app

unix {
                message("unix build")
                PYLON_ROOT	= /opt/pylon4
                GENICAM_ROOT	= $${PYLON_ROOT}/genicam

                INCLUDEPATH += $${GENICAM_ROOT}/library/CPP/include $${PYLON_ROOT}/include ../PylonProxy
                LIBS += -L$${PYLON_ROOT}/lib -L$${GENICAM_ROOT}/bin/Linux32_ARM -L$${GENICAM_ROOT}/bin/Linux32_ARM/GenApi/Generic -Wl,-E
                LIBS += -lpylonbase -lpylonutility -lGenApi_gcc43_v2_3 -lGCBase_gcc43_v2_3 -lLog_gcc43_v2_3 -lMathParser_gcc43_v2_3 -lXerces-C_gcc43_v2_7_1 -llog4cpp_gcc43_v2_3
                include(/usr/share/qt4/mkspecs/features/qwt.prf )
}

win32 {

    ## Windows common build here

#    !contains(QMAKE_TARGET.arch, "64") {
#       message("x86 build")
#
#                ##### use this on x32 Win with Qt 5.2.0 and pylon 3.2 #####
#                INCLUDEPATH = "C:\Program Files\Basler\pylon 3.2\pylon\include" "C:\Program Files\Basler\pylon 3.2\genicam\library\cpp\include"
#                LIBS += -L"C:\Program Files\Basler\pylon 3.2\genicam\library\cpp\lib\win32_i86" -L"C:\Program Files\Basler\pylon 3.2\pylon\lib\Win32" -lGCBase_MD_VC100_v2_3 -lGenApi_MD_VC100_v2_3 -lPylonBase_MD_VC100 -lPylonGigE_MD_VC100_TL
#                include(C:\Qt\Qt5.2.0\5.2.0\Src\qtimageformats\src\3rdparty\libtiff.pri )
#                include(C:\Qwt-6.1.0\features\qwt.prf )
#
#    } else {
                message("win x86_64 build")

                PYLON_ROOT	= C:\Program Files\Basler\pylon 4
                GENICAM_ROOT	= $${PYLON_ROOT}\genicam

                ##### use this on x64 Win with Qt 5.3 and pylon 4#####
                INCLUDEPATH += "$${PYLON_ROOT}\pylon\include" "$${GENICAM_ROOT}\library\cpp\include"
                LIBS += -L"$${GENICAM_ROOT}\library\cpp\lib\win64_x64" -L"$${PYLON_ROOT}\pylon\lib\x64" -lGCBase_MD_VC100_v2_3 -lGenApi_MD_VC100_v2_3 -lPylonBase_MD_VC100 -lPylonGigE_MD_VC100_TL
                include(libtiff.pri)
                include(PylonProxy.pri)
                include(C:\qwt-6.1.1_msvc13_64\features\qwt.prf )
#    }
}


SOURCES += main.cpp\
           camview.cpp \
           imagewidget.cpp \
           WorkerThread.cpp

HEADERS  += camview.h \
            imagewidget.h \
            WorkerThread.h

FORMS    += camview.ui

DEFINES  += USE_GIGE NEED_LIBPORT QWT_DLL
