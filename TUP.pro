QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    app/ApplicationController.cpp \
    main.cpp \
    app/mainwindow.cpp \
    ui/theme/minimal/MinimalAddTaskView.cpp \
    ui/theme/minimal/MinimalAllTasksStatisticsView.cpp \
    ui/theme/minimal/MinimalAuthorizationView.cpp \
    ui/theme/minimal/MinimalSingleTaskStatisticsView.cpp \
    ui/theme/minimal/MinimalSynchronizationView.cpp \
    ui/theme/minimal/MinimalTaskSelectionView.cpp \
    ui/theme/minimal/MinimalTimerView.cpp \
    ui/theme/minimal/MinimalUIFactory.cpp

HEADERS += \
    app/ApplicationController.h \
    app/mainwindow.h \
    calendar/ICalendarService.h \
    db/IDatabaseService.h \
    ui/interfaces/IAddTaskView.h \
    ui/interfaces/IAllTasksStatisticsView.h \
    ui/interfaces/IAuthorizationView.h \
    ui/interfaces/ISingleTaskStatisticsView.h \
    ui/interfaces/ISynchronizationView.h \
    ui/interfaces/ITaskSelectionView.h \
    ui/interfaces/ITimerView.h \
    ui/interfaces/IUIFactory.h \
    ui/interfaces/IView.h \
    ui/theme/minimal/MinimalAddTaskView.h \
    ui/theme/minimal/MinimalAllTasksStatisticsView.h \
    ui/theme/minimal/MinimalAuthorizationView.h \
    ui/theme/minimal/MinimalSingleTaskStatisticsView.h \
    ui/theme/minimal/MinimalSynchronizationView.h \
    ui/theme/minimal/MinimalTaskSelectionView.h \
    ui/theme/minimal/MinimalTimerView.h \
    ui/theme/minimal/MinimalUIFactory.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
