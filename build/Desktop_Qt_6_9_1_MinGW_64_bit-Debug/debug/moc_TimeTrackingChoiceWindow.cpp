/****************************************************************************
** Meta object code from reading C++ file 'TimeTrackingChoiceWindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/themes/minimal/TimeTrackingChoiceWindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TimeTrackingChoiceWindow.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN24TimeTrackingChoiceWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto TimeTrackingChoiceWindow::qt_create_metaobjectdata<qt_meta_tag_ZN24TimeTrackingChoiceWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TimeTrackingChoiceWindow",
        "singleTaskStatsRequested",
        "",
        "allTasksStatsRequested",
        "onSingleTaskStats",
        "onAllTasksStats"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'singleTaskStatsRequested'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'allTasksStatsRequested'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onSingleTaskStats'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAllTasksStats'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TimeTrackingChoiceWindow, qt_meta_tag_ZN24TimeTrackingChoiceWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TimeTrackingChoiceWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<IAppWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN24TimeTrackingChoiceWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN24TimeTrackingChoiceWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN24TimeTrackingChoiceWindowE_t>.metaTypes,
    nullptr
} };

void TimeTrackingChoiceWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TimeTrackingChoiceWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->singleTaskStatsRequested(); break;
        case 1: _t->allTasksStatsRequested(); break;
        case 2: _t->onSingleTaskStats(); break;
        case 3: _t->onAllTasksStats(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TimeTrackingChoiceWindow::*)()>(_a, &TimeTrackingChoiceWindow::singleTaskStatsRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (TimeTrackingChoiceWindow::*)()>(_a, &TimeTrackingChoiceWindow::allTasksStatsRequested, 1))
            return;
    }
}

const QMetaObject *TimeTrackingChoiceWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TimeTrackingChoiceWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN24TimeTrackingChoiceWindowE_t>.strings))
        return static_cast<void*>(this);
    return IAppWindow::qt_metacast(_clname);
}

int TimeTrackingChoiceWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IAppWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TimeTrackingChoiceWindow::singleTaskStatsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TimeTrackingChoiceWindow::allTasksStatsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
