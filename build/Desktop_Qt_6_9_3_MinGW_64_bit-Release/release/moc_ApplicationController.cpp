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
        "onLoginRequested",
        "",
        "username",
        "password",
        "onRegistrationSubmitted",
        "email",
        "onBackToLoginRequested",
        "onTaskSelectedForTimer",
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
        "onTweekAuthSuccess",
        "idToken",
        "refreshToken",
        "onTweekAuthFailed",
        "error",
        "onTweekDisconnectRequested",
        "onCalendarsFetchSuccess",
        "QList<TweekCalendar>",
        "calendars",
        "onCalendarsFetchFailed",
        "onTasksFetchSuccess",
        "QList<TweekTask>",
        "tasks",
        "onTasksFetchFailed",
        "onSyncTasksSelected",
        "selectedTasks",
        "onTimerModeSelected",
        "onPomodoroModeSelected",
        "workMinutes",
        "restMinutes",
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
        "tweekTaskId",
        "onTweekTaskUpdateFailed",
        "onLogoutRequested"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onLoginRequested'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::QString, 4 },
        }}),
        // Slot 'onRegistrationSubmitted'
        QtMocHelpers::SlotData<void(const QString &, const QString &, const QString &)>(5, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::QString, 6 }, { QMetaType::QString, 4 },
        }}),
        // Slot 'onBackToLoginRequested'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTaskSelectedForTimer'
        QtMocHelpers::SlotData<void(const QString &)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'onStatisticsRequestedForTask'
        QtMocHelpers::SlotData<void(const QString &)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'onAllTasksStatisticsRequested'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSynchronizationRequested'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAddTaskRequested'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTimerClosed'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onStatisticsClosed'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAllTasksStatisticsClosed'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSynchronizationClosed'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAddTaskSaved'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 19 }, { QMetaType::QString, 20 },
        }}),
        // Slot 'onAddTaskCancelled'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTimerStop'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTimerTick'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onWeekChangeForStatisticsRequested'
        QtMocHelpers::SlotData<void(const QDate &)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QDate, 25 },
        }}),
        // Slot 'onTweekConnectRequested'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(26, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 6 }, { QMetaType::QString, 4 },
        }}),
        // Slot 'onTweekAuthSuccess'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(27, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 28 }, { QMetaType::QString, 29 },
        }}),
        // Slot 'onTweekAuthFailed'
        QtMocHelpers::SlotData<void(const QString &)>(30, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 31 },
        }}),
        // Slot 'onTweekDisconnectRequested'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCalendarsFetchSuccess'
        QtMocHelpers::SlotData<void(const QVector<TweekCalendar> &)>(33, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 34, 35 },
        }}),
        // Slot 'onCalendarsFetchFailed'
        QtMocHelpers::SlotData<void(const QString &)>(36, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 31 },
        }}),
        // Slot 'onTasksFetchSuccess'
        QtMocHelpers::SlotData<void(const QVector<TweekTask> &)>(37, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 38, 39 },
        }}),
        // Slot 'onTasksFetchFailed'
        QtMocHelpers::SlotData<void(const QString &)>(40, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 31 },
        }}),
        // Slot 'onSyncTasksSelected'
        QtMocHelpers::SlotData<void(const QVector<TweekTask> &)>(41, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 38, 42 },
        }}),
        // Slot 'onTimerModeSelected'
        QtMocHelpers::SlotData<void()>(43, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onPomodoroModeSelected'
        QtMocHelpers::SlotData<void(int, int)>(44, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 45 }, { QMetaType::Int, 46 },
        }}),
        // Slot 'onEditTaskRequested'
        QtMocHelpers::SlotData<void(const QString &)>(47, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'onEditTaskSaved'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(48, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 19 }, { QMetaType::QString, 20 },
        }}),
        // Slot 'onEditTaskDeleted'
        QtMocHelpers::SlotData<void()>(49, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onEditTaskCancelled'
        QtMocHelpers::SlotData<void()>(50, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSyncSingleTaskToTweek'
        QtMocHelpers::SlotData<void(const QString &)>(51, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 9 },
        }}),
        // Slot 'onTweekTaskCreateSuccess'
        QtMocHelpers::SlotData<void(int, const QString &)>(52, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 53 }, { QMetaType::QString, 54 },
        }}),
        // Slot 'onTweekTaskCreateFailed'
        QtMocHelpers::SlotData<void(int, const QString &)>(55, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 53 }, { QMetaType::QString, 31 },
        }}),
        // Slot 'onTweekTaskUpdateSuccess'
        QtMocHelpers::SlotData<void(const QString &)>(56, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 57 },
        }}),
        // Slot 'onTweekTaskUpdateFailed'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(58, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 57 }, { QMetaType::QString, 31 },
        }}),
        // Slot 'onLogoutRequested'
        QtMocHelpers::SlotData<void()>(59, 2, QMC::AccessPrivate, QMetaType::Void),
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
        case 0: _t->onLoginRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->onRegistrationSubmitted((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 2: _t->onBackToLoginRequested(); break;
        case 3: _t->onTaskSelectedForTimer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->onStatisticsRequestedForTask((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->onAllTasksStatisticsRequested(); break;
        case 6: _t->onSynchronizationRequested(); break;
        case 7: _t->onAddTaskRequested(); break;
        case 8: _t->onTimerClosed(); break;
        case 9: _t->onStatisticsClosed(); break;
        case 10: _t->onAllTasksStatisticsClosed(); break;
        case 11: _t->onSynchronizationClosed(); break;
        case 12: _t->onAddTaskSaved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 13: _t->onAddTaskCancelled(); break;
        case 14: _t->onTimerStop(); break;
        case 15: _t->onTimerTick(); break;
        case 16: _t->onWeekChangeForStatisticsRequested((*reinterpret_cast< std::add_pointer_t<QDate>>(_a[1]))); break;
        case 17: _t->onTweekConnectRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 18: _t->onTweekAuthSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 19: _t->onTweekAuthFailed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->onTweekDisconnectRequested(); break;
        case 21: _t->onCalendarsFetchSuccess((*reinterpret_cast< std::add_pointer_t<QList<TweekCalendar>>>(_a[1]))); break;
        case 22: _t->onCalendarsFetchFailed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 23: _t->onTasksFetchSuccess((*reinterpret_cast< std::add_pointer_t<QList<TweekTask>>>(_a[1]))); break;
        case 24: _t->onTasksFetchFailed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 25: _t->onSyncTasksSelected((*reinterpret_cast< std::add_pointer_t<QList<TweekTask>>>(_a[1]))); break;
        case 26: _t->onTimerModeSelected(); break;
        case 27: _t->onPomodoroModeSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 28: _t->onEditTaskRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 29: _t->onEditTaskSaved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 30: _t->onEditTaskDeleted(); break;
        case 31: _t->onEditTaskCancelled(); break;
        case 32: _t->onSyncSingleTaskToTweek((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 33: _t->onTweekTaskCreateSuccess((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 34: _t->onTweekTaskCreateFailed((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 35: _t->onTweekTaskUpdateSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 36: _t->onTweekTaskUpdateFailed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 37: _t->onLogoutRequested(); break;
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
        if (_id < 38)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 38;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 38)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 38;
    }
    return _id;
}
QT_WARNING_POP
