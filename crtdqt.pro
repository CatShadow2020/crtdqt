##pragma "$Id$"

TARGET = crtdqt 
CONFIG += debug \
          warn_off \
          qt \
          thread \
QT += gui
QT += widgets
           
HEADERS += nrtschaninfo.h \
           nrtsinfo.h \
           nrtsstainfo.h \
           set_all_parameters.h \
           DataBlock.h \
           MainFrame.h \
           Preview.h \
           CRTDglob.h \
           QmyToolBar.h \
           RTDisplay.h \
           StopAcquisitionThread.h \
           GettingDataThread.h \
           DrawWaveformThread.h \ 
           IsiInterruptThread.cpp

SOURCES += datablock.cpp \
           main.cpp \
           nrtschaninfo.cpp \
           nrtsinfo.cpp \
           nrtsstainfo.cpp \
           set_all_parameters.cpp \
           thread.cpp \
           MainFrame.cpp \
           MWindow.cpp \
           Preview.cpp \
           CRTDglob.cpp \
           QmyToolBar.cpp \
           RTDisplay.cpp \
           StopAcquisitionThread.cpp \
           GettingDataThread.cpp \
           DrawWaveformThread.cpp \
           IsiInterruptThread.cpp



macx{
LIBS    = -L/Volumes/code/lib/$(PLATFORM)
LIBS   += -lc
LIBS   += -lmseed
LIBS   += -ldmc
LIBS   += -lisidb
LIBS   += -lutil
LIBS   += -lcssio
LIBS   += -lz
LIBS   += -lm
LIBS   += -lisi
LIBS   += -liacp
LIBS   += -llogio
LIBS   += -lida10
#LIBS   += $(MTLIBS)
#LIBS   += $(POSIX4LIB)
LIBS   += -lstdc++
LIBS   += -lutil
LIBS   += -lliss
LIBS   += -lcssio
LIBS   += -lida
LIBS   += -lisidb
LIBS   += -ldbio
LIBS   += -lutil
LIBS   += -lc

DEFINES += $(OSNAME)
DEFINES += $(PLATFORM)
DEFINES += $(MACHINE)
DEFINES += BSD
INCLUDEPATH = /Volumes/code/src/include
INCLUDEPATH += /Volumes/code/src/include/dmc
#QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11
QMAKE_CFLAGS += -Wall
QMAKE_CXXFLAGS += -Wall
#QMAKE_CFLAGS -= -mmacosx-version-min=10.9
#QMAKE_CFLAGS += -mmacosx-version-min=10.12
QMAKE_LFLAGS -= -mmacosx-version-min=10.12
QMAKE_LFLAGS += -mmacosx-version-min=10.12
QMAKE_LFLAGS += -v

QT += widgets
}

#win32 {
#LIBS    = -L /Users/dauerbach/cvs/lib/$(PLATFORM)
#LIBS   += -lisidb
#LIBS   += -lcssio
#LIBS   += -lutil
#LIBS   += -lz
#LIBS   += -lm
#LIBS   += -lisi
#LIBS   += -liacp
#LIBS   += -llogio
#LIBS   += -lida10
#LIBS   += -lstdc++
#LIBS   += -lutil
#LIBS   += -lcssio
#LIBS   += -lida
#LIBS   += -lisidb
#LIBS   += -ldbio
#LIBS   += -lutil
#LIBS   += -lws2_32



#INCLUDEPATH = /Users/dauerbach/cvs/src/include
#QMAKE_CFLAGS += -W
#QMAKE_CXXFLAGS += -W
#QT += widgets
#}

##win32 {
##
##
##CONFIG(debug, debug|release) {
##        LIBS +=   ..\..\windows\lib\util\Debug\util.lib   ..\..\windows\lib\cssio\Debug\cssio.lib ..\..\windows\lib\win32\Debug\win32.lib
##        LIBS +=   ..\..\windows\lib\isi\Debug\isi.lib     ..\..\windows\lib\ida\Debug\ida.lib ..\..\windows\lib\logio\Debug\logio.lib
##        LIBS +=   ..\..\windows\lib\ida10\Debug\ida10.lib ..\..\windows\lib\iacp\Debug\iacp.lib
##        LIBS +=   ..\..\windows\lib\liss\Debug\liss.lib   ..\..\windows\lib\isidb\Debug\isidb.lib
##        LIBS +=   ..\..\windows\lib\dbio\Debug\dbio.lib   ..\..\windows\lib\mysql\opt\libmysql.lib
####        LIBS += ws2_32.lib
##        LIBS += libws2_32
##	}
##
##CONFIG(release, debug|release) { CONFIG += staticlib
##  LIBS +=   ..\..\windows\lib\util\Release\util.lib ..\..\windows\lib\cssio\Release\cssio.lib ..\..\windows\lib\win32\Release\win32.lib
##  }
##
##INCLUDEPATH = ..\..\include ..\..\..\include
##DEFINES += _CRT_SECURE_NO_DEPRECATE
## }

RESOURCES += \
    crtdqt-isi.qrc

##/*-----------------------------------------------------------------------+
## |                                                                       |
## | Copyright (C) 2016 Regents of the University of California            |
## |                                                                       |
## | This software is provided 'as-is', without any express or implied     |
## | warranty.  In no event will the authors be held liable for any        |
## | damages arising from the use of this software.                        |
## |                                                                       |
## | Permission is granted to anyone to use this software for any purpose, |
## | including commercial applications, and to alter it and redistribute   |
## | it freely, subject to the following restrictions:                     |
## |                                                                       |
## | 1. The origin of this software must not be misrepresented; you must   |
## |    not claim that you wrote the original software. If you use this    |
## |    software in a product, an acknowledgment in the product            |
## |    documentation of the contribution by Project IDA, UCSD would be    |
## |    appreciated but is not required.                                   |
## | 2. Altered source versions must be plainly marked as such, and must   |
## |    not be misrepresented as being the original software.              |
## | 3. This notice may not be removed or altered from any source          |
## |    distribution.                                                      |
## |                                                                       |
## +-----------------------------------------------------------------------*/
##/* Revision History
## *
## * $Log$
## */	
