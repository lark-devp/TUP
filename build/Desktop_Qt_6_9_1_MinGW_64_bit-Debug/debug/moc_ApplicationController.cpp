/****************************************************************************
** Meta object code from reading C++ file 'ApplicationController.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../app/ApplicationController.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ApplicationController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
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
        "onAddTaskCancelled"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onLoginRequested'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::QString, 4 },
        }}),
        // Slot 'onTaskSelectedForTimer'
        QtMocHelpers::SlotData<void(const QString &)>(5, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Slot 'onStatisticsRequestedForTask'
        QtMocHelpers::SlotData<void(const QString &)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Slot 'onAllTasksStatisticsRequested'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSynchronizationRequested'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAddTaskRequested'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTimerClosed'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onStatisticsClosed'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAllTasksStatisticsClosed'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSynchronizationClosed'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAddTaskSaved'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(15, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 16 }, { QMetaType::QString, 17 },
        }}),
        // Slot 'onAddTaskCancelled'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
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
        case 1: _t->onTaskSelectedForTimer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->onStatisticsRequestedForTask((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->onAllTasksStatisticsRequested(); break;
        case 4: _t->onSynchronizationRequested(); break;
        case 5: _t->onAddTaskRequested(); break;
        case 6: _t->onTimerClosed(); break;
        case 7: _t->onStatisticsClosed(); break;
        case 8: _t->onAllTasksStatisticsClosed(); break;
        case 9: _t->onSynchronizationClosed(); break;
        case 10: _t->onAddTaskSaved((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 11: _t->onAddTaskCancelled(); break;
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
