QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql network

CONFIG += c++17



SOURCES += \
    app/ApplicationController.cpp \
    calendar/TweekApiServiceImpl.cpp \
    db/SqliteDatabaseService.cpp \
    main.cpp \
    app/mainwindow.cpp \
    ui/theme/minimal/BarChartView.cpp \
    ui/theme/minimal/MinimalAddTaskView.cpp \
    ui/theme/minimal/MinimalAllTasksStatisticsView.cpp \
    ui/theme/minimal/MinimalAuthorizationView.cpp \
    ui/theme/minimal/MinimalEditTaskView.cpp \
    ui/theme/minimal/MinimalSingleTaskStatisticsView.cpp \
    ui/theme/minimal/MinimalSynchronizationView.cpp \
    ui/theme/minimal/MinimalTaskSelectionView.cpp \
    ui/theme/minimal/MinimalTimerView.cpp \
    ui/theme/minimal/MinimalUIFactory.cpp

HEADERS += \
    app/ApplicationController.h \
    app/mainwindow.h \
    calendar/ITweekApiService.h \
    calendar/TweekApiServiceImpl.h \
    db/IDatabaseService.h \
    db/SqliteDatabaseService.h \
    ui/interfaces/IAddTaskView.h \
    ui/interfaces/IAllTasksStatisticsView.h \
    ui/interfaces/IAuthorizationView.h \
    ui/interfaces/IEditTaskView.h \
    ui/interfaces/ISingleTaskStatisticsView.h \
    ui/interfaces/ISynchronizationView.h \
    ui/interfaces/ITaskSelectionView.h \
    ui/interfaces/ITimerView.h \
    ui/interfaces/IUIFactory.h \
    ui/interfaces/IView.h \
    ui/theme/minimal/BarChartView.h \
    ui/theme/minimal/MinimalAddTaskView.h \
    ui/theme/minimal/MinimalAllTasksStatisticsView.h \
    ui/theme/minimal/MinimalAuthorizationView.h \
    ui/theme/minimal/MinimalEditTaskView.h \
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
