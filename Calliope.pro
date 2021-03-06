QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    UnitTests/Test_ConfigAndSessionData.cpp \
    UnitTests/Test_FolderStructurePersistence.cpp \
    UnitTests/Test_PageSaveAndLoad.cpp \
    UnitTests/Test_TempDataPersistence.cpp \
    folder.cpp \
    folderptrlist.cpp \
    main.cpp \
    mainwindow.cpp \
    menubar.cpp \
    notebook.cpp \
    page.cpp \
    pageeditview.cpp \
    pageptrlist.cpp \
    pagerecord.cpp \
    sessiondatamanager.cpp \
    workspaceview.cpp

HEADERS += \
    Helpers/fileoperationshelper.h \
    folder.h \
    folderptrlist.h \
    folders.h \
    foldervectorinterface.h \
    mainwindow.h \
    menubar.h \
    notebook.h \
    osdefines.h \
    page.h \
    pageeditview.h \
    pageptrlist.h \
    pagerecord.h \
    pages.h \
    sessiondatamanager.h \
    workspaceview.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
