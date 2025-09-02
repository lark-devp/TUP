QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MultiTaskAnalyticsWindow.cpp \
    SingleTaskAnalyticsWindow.cpp \
    TaskEditorWindow.cpp \
    TaskSelectorWindow.cpp \
    TaskTimerWindow.cpp \
    db/DBManager.cpp \
    main.cpp \
    mainwindow.cpp \
    models/Task.cpp \
    repository/TaskRepository.cpp

HEADERS += \
    MultiTaskAnalyticsWindow.h \
    SingleTaskAnalyticsWindow.h \
    TaskEditorWindow.h \
    TaskSelectorWindow.h \
    TaskTimerWindow.h \
    db/DBManager.h \
    mainwindow.h \
    models/Task.h \
    models/TimeEntry.h \
    models/User.h \
    repository/TaskRepository.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    img/selectorImg.png
