/****************************************************************************
** Meta object code from reading C++ file 'ITaskExecutionWindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/interfaces/ITaskExecutionWindow.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ITaskExecutionWindow.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN20ITaskExecutionWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto ITaskExecutionWindow::qt_create_metaobjectdata<qt_meta_tag_ZN20ITaskExecutionWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ITaskExecutionWindow",
        "timerStarted",
        "",
        "timerPaused",
        "timerStopped",
        "taskCompleted",
        "backToTaskSelection"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'timerStarted'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'timerPaused'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'timerStopped'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'taskCompleted'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'backToTaskSelection'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ITaskExecutionWindow, qt_meta_tag_ZN20ITaskExecutionWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ITaskExecutionWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<IAppWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20ITaskExecutionWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20ITaskExecutionWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN20ITaskExecutionWindowE_t>.metaTypes,
    nullptr
} };

void ITaskExecutionWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ITaskExecutionWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->timerStarted(); break;
        case 1: _t->timerPaused(); break;
        case 2: _t->timerStopped(); break;
        case 3: _t->taskCompleted(); break;
        case 4: _t->backToTaskSelection(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ITaskExecutionWindow::*)()>(_a, &ITaskExecutionWindow::timerStarted, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITaskExecutionWindow::*)()>(_a, &ITaskExecutionWindow::timerPaused, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITaskExecutionWindow::*)()>(_a, &ITaskExecutionWindow::timerStopped, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITaskExecutionWindow::*)()>(_a, &ITaskExecutionWindow::taskCompleted, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITaskExecutionWindow::*)()>(_a, &ITaskExecutionWindow::backToTaskSelection, 4))
            return;
    }
}

const QMetaObject *ITaskExecutionWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ITaskExecutionWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20ITaskExecutionWindowE_t>.strings))
        return static_cast<void*>(this);
    return IAppWindow::qt_metacast(_clname);
}

int ITaskExecutionWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IAppWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ITaskExecutionWindow::timerStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ITaskExecutionWindow::timerPaused()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ITaskExecutionWindow::timerStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ITaskExecutionWindow::taskCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ITaskExecutionWindow::backToTaskSelection()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
