/****************************************************************************
** Meta object code from reading C++ file 'ITaskSelectionWindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/interfaces/ITaskSelectionWindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ITaskSelectionWindow.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN20ITaskSelectionWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto ITaskSelectionWindow::qt_create_metaobjectdata<qt_meta_tag_ZN20ITaskSelectionWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ITaskSelectionWindow",
        "taskSelectedForExecution",
        "",
        "taskId",
        "taskSelectedForEdit",
        "newTaskRequested",
        "quickStartRequested"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'taskSelectedForExecution'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'taskSelectedForEdit'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'newTaskRequested'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'quickStartRequested'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ITaskSelectionWindow, qt_meta_tag_ZN20ITaskSelectionWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ITaskSelectionWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<IAppWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20ITaskSelectionWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20ITaskSelectionWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN20ITaskSelectionWindowE_t>.metaTypes,
    nullptr
} };

void ITaskSelectionWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ITaskSelectionWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->taskSelectedForExecution((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->taskSelectedForEdit((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->newTaskRequested(); break;
        case 3: _t->quickStartRequested(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ITaskSelectionWindow::*)(const QString & )>(_a, &ITaskSelectionWindow::taskSelectedForExecution, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITaskSelectionWindow::*)(const QString & )>(_a, &ITaskSelectionWindow::taskSelectedForEdit, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITaskSelectionWindow::*)()>(_a, &ITaskSelectionWindow::newTaskRequested, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITaskSelectionWindow::*)()>(_a, &ITaskSelectionWindow::quickStartRequested, 3))
            return;
    }
}

const QMetaObject *ITaskSelectionWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ITaskSelectionWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20ITaskSelectionWindowE_t>.strings))
        return static_cast<void*>(this);
    return IAppWindow::qt_metacast(_clname);
}

int ITaskSelectionWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ITaskSelectionWindow::taskSelectedForExecution(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ITaskSelectionWindow::taskSelectedForEdit(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void ITaskSelectionWindow::newTaskRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ITaskSelectionWindow::quickStartRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
