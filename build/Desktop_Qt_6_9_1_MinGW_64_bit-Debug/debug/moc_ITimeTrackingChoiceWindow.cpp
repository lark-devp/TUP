/****************************************************************************
** Meta object code from reading C++ file 'ITimeTrackingChoiceWindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/interfaces/ITimeTrackingChoiceWindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ITimeTrackingChoiceWindow.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN25ITimeTrackingChoiceWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto ITimeTrackingChoiceWindow::qt_create_metaobjectdata<qt_meta_tag_ZN25ITimeTrackingChoiceWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ITimeTrackingChoiceWindow",
        "singleTaskStatsRequested",
        "",
        "taskId",
        "allTasksStatsRequested",
        "dateRangeStatsRequested",
        "start",
        "end"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'singleTaskStatsRequested'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'allTasksStatsRequested'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'dateRangeStatsRequested'
        QtMocHelpers::SignalData<void(const QDate &, const QDate &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QDate, 6 }, { QMetaType::QDate, 7 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ITimeTrackingChoiceWindow, qt_meta_tag_ZN25ITimeTrackingChoiceWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ITimeTrackingChoiceWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<IAppWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN25ITimeTrackingChoiceWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN25ITimeTrackingChoiceWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN25ITimeTrackingChoiceWindowE_t>.metaTypes,
    nullptr
} };

void ITimeTrackingChoiceWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ITimeTrackingChoiceWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->singleTaskStatsRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->allTasksStatsRequested(); break;
        case 2: _t->dateRangeStatsRequested((*reinterpret_cast< std::add_pointer_t<QDate>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QDate>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ITimeTrackingChoiceWindow::*)(const QString & )>(_a, &ITimeTrackingChoiceWindow::singleTaskStatsRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITimeTrackingChoiceWindow::*)()>(_a, &ITimeTrackingChoiceWindow::allTasksStatsRequested, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITimeTrackingChoiceWindow::*)(const QDate & , const QDate & )>(_a, &ITimeTrackingChoiceWindow::dateRangeStatsRequested, 2))
            return;
    }
}

const QMetaObject *ITimeTrackingChoiceWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ITimeTrackingChoiceWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN25ITimeTrackingChoiceWindowE_t>.strings))
        return static_cast<void*>(this);
    return IAppWindow::qt_metacast(_clname);
}

int ITimeTrackingChoiceWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IAppWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ITimeTrackingChoiceWindow::singleTaskStatsRequested(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ITimeTrackingChoiceWindow::allTasksStatsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ITimeTrackingChoiceWindow::dateRangeStatsRequested(const QDate & _t1, const QDate & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2);
}
QT_WARNING_POP
