/****************************************************************************
** Meta object code from reading C++ file 'ApplicationController.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../app/ApplicationController.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ApplicationController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN21ApplicationControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto ApplicationController::qt_create_metaobjectdata<qt_meta_tag_ZN21ApplicationControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ApplicationController",
        "onTaskSelectedForTimer",
        "",
        "taskId",
        "onStatisticsRequestedForTask",
        "onAllTasksStatisticsRequested",
        "onSynchronizationRequested",
        "onAddTaskRequested",
        "onTimerClosed",
        "onStatisticsClosed",
        "onAllTasksStatisticsClosed",
        "onSynchronizationClosed",
        "onAddTaskSaved",
        "title",
        "description",
        "onAddTaskCancelled",
        "onTimerStop",
        "onTimerTick",
        "onWeekChangeForStatisticsRequested",
        "weekStartDate",
        "onTweekConnectRequested",
        "email",
        "password",
        "onTweekAuthSuccess",
        "idToken",
        "refreshToken",
        "onTweekAuthFailed",
        "onTweekDisconnectRequested",
        "onCalendarsFetchSuccess",
        "QList<TweekCalendar>",
        "calendars",
        "onCalendarsFetchFailed",
        "onTasksFetchSuccess",
        "QList<TweekTask>",
        "tasks",
        "onTasksFetchFailed",
        "error",
        "onSyncTasksSelected",
        "selectedTasks",
        "onTimerModeSelected",
        "onPomodoroModeSelected",
        "workMinutes",
        "restMinutes",
        "sessionCount",
        "onSkipRestRequested",
        "onEditTaskRequested",
        "onEditTaskSaved",
        "onEditTaskDeleted",
        "onEditTaskCancelled",
        "onSyncSingleTaskToTweek",
        "onTweekTaskCreateSuccess",
        "localTaskId",
        "newTweekTaskId",
        "onTweekTaskCreateFailed",
        "onTweekTaskUpdateSuccess",
        "onTweekTaskUpdateFailed",
        "httpStatusCode"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onTaskSelectedForTimer'
        QtMocHelpers::SlotData<void(const QString &)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Slot 'onStatisticsRequestedForTask'
        QtMocHelpers::SlotData<void(const QString &)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Slot 'onAllTasksStatisticsRequested'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSynchronizationRequested'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAddTaskRequested'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTimerClosed'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onStatisticsClosed'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAllTasksStatisticsClosed'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSynchronizationClosed'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAddTaskSaved'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 13 }, { QMetaType::QString, 14 },
        }}),
        // Slot 'onAddTaskCancelled'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTimerStop'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTimerTick'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onWeekChangeForStatisticsRequested'
        QtMocHelpers::SlotData<void(const QDate &)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QDate, 19 },
        }}),
        // Slot 'onTweekConnectRequested'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 21 }, { QMetaType::QString, 22 },
        }}),
        // Slot 'onTweekAuthSuccess'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 24 }, { QMetaType::QString, 25 },
        }}),
        // Slot 'onTweekAuthFailed'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTweekDisconnectRequested'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCalendarsFetchSuccess'
        QtMocHelpers::SlotData<void(const QVector<TweekCalendar> &)>(28, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 29, 30 },
        }}),
        // Slot 'onCalendarsFetchFailed'
        QtMocHelpers::SlotData<void()>(31, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTasksFetchSuccess'
        QtMocHelpers::SlotData<void(const QVector<TweekTask> &)>(32, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 33, 34 },
        }}),
        // Slot 'onTasksFetchFailed'
        QtMocHelpers::SlotData<void(const QString &)>(35, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 36 },
        }}),
        // Slot 'onSyncTasksSelected'
        QtMocHelpers::SlotData<void(const QVector<TweekTask> &)>(37, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 33, 38 },
        }}),
        // Slot 'onTimerModeSelected'
        QtMocHelpers::SlotData<void()>(39, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onPomodoroModeSelected'
        QtMocHelpers::SlotData<void(int, int, int)>(40, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 41 }, { QMetaType::Int, 42 }, { QMetaType::Int, 43 },
        }}),
        // Slot 'onSkipRestRequested'
        QtMocHelpers::SlotData<void()>(44, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onEditTaskRequested'
        QtMocHelpers::SlotData<void(const QString &)>(45, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Slot 'onEditTaskSaved'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(46, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 13 }, { QMetaType::QString, 14 },
        }}),
        // Slot 'onEditTaskDeleted'
        QtMocHelpers::SlotData<void()>(47, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onEditTaskCancelled'
        QtMocHelpers::SlotData<void()>(48, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSyncSingleTaskToTweek'
        QtMocHelpers::SlotData<void(const QString &)>(49, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Slot 'onTweekTaskCreateSuccess'
        QtMocHelpers::SlotData<void(int, const QString &)>(50, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 51 }, { QMetaType::QString, 52 },
        }}),
        // Slot 'onTweekTaskCreateFailed'
        QtMocHelpers::SlotData<void(int, const QString &)>(53, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 51 }, { QMetaType::QString, 36 },
        }}),
        // Slot 'onTweekTaskUpdateSuccess'
        QtMocHelpers::SlotData<void(int)>(54, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 51 },
        }}),
        // Slot 'onTweekTaskUpdateFailed'
        QtMocHelpers::SlotData<void(int, const QString &, int)>(55, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 51 }, { QMetaType::QString, 36 }, { QMetaType::Int, 56 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ApplicationController, qt_meta_tag_ZN21ApplicationControllerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ApplicationController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21ApplicationControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21ApplicationControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN21ApplicationControllerE_t>.metaTypes,
    nullptr
} };

void ApplicationController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ApplicationController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onTaskSelectedForTimer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->onStatisticsRequestedForTask((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->onAllTasksStatisticsRequested(); break;
        case 3: _t->onSynchronizationRequested(); break;
        case 4: _t->onAddTaskRequested(); break;
        case 5: _t->onTimerClosed(); break;
        case 6: _t->onStatisticsClosed(); break;
        case 7: _t->onAllTasksStatisticsClosed(); break;
        case 8: _t->onSynchronizationClosed(); break;
        case 9: _t->onAddTaskSaved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 10: _t->onAddTaskCancelled(); break;
        case 11: _t->onTimerStop(); break;
        case 12: _t->onTimerTick(); break;
        case 13: _t->onWeekChangeForStatisticsRequested((*reinterpret_cast< std::add_pointer_t<QDate>>(_a[1]))); break;
        case 14: _t->onTweekConnectRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 15: _t->onTweekAuthSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 16: _t->onTweekAuthFailed(); break;
        case 17: _t->onTweekDisconnectRequested(); break;
        case 18: _t->onCalendarsFetchSuccess((*reinterpret_cast< std::add_pointer_t<QList<TweekCalendar>>>(_a[1]))); break;
        case 19: _t->onCalendarsFetchFailed(); break;
        case 20: _t->onTasksFetchSuccess((*reinterpret_cast< std::add_pointer_t<QList<TweekTask>>>(_a[1]))); break;
        case 21: _t->onTasksFetchFailed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 22: _t->onSyncTasksSelected((*reinterpret_cast< std::add_pointer_t<QList<TweekTask>>>(_a[1]))); break;
        case 23: _t->onTimerModeSelected(); break;
        case 24: _t->onPomodoroModeSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 25: _t->onSkipRestRequested(); break;
        case 26: _t->onEditTaskRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 27: _t->onEditTaskSaved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 28: _t->onEditTaskDeleted(); break;
        case 29: _t->onEditTaskCancelled(); break;
        case 30: _t->onSyncSingleTaskToTweek((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 31: _t->onTweekTaskCreateSuccess((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 32: _t->onTweekTaskCreateFailed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 33: _t->onTweekTaskUpdateSuccess((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 34: _t->onTweekTaskUpdateFailed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject *ApplicationController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ApplicationController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN21ApplicationControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ApplicationController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 35)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 35;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 35)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 35;
    }
    return _id;
}
QT_WARNING_POP
