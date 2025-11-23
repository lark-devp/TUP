/****************************************************************************
** Meta object code from reading C++ file 'ITimerView.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/interfaces/ITimerView.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ITimerView.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10ITimerViewE_t {};
} // unnamed namespace

template <> constexpr inline auto ITimerView::qt_create_metaobjectdata<qt_meta_tag_ZN10ITimerViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ITimerView",
        "stopClicked",
        "",
        "closeRequested",
        "timerModeSelected",
        "pomodoroModeSelected",
        "workMinutes",
        "restMinutes",
        "sessionCount",
        "skipRestRequested"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'stopClicked'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'closeRequested'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'timerModeSelected'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'pomodoroModeSelected'
        QtMocHelpers::SignalData<void(int, int, int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 }, { QMetaType::Int, 7 }, { QMetaType::Int, 8 },
        }}),
        // Signal 'skipRestRequested'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ITimerView, qt_meta_tag_ZN10ITimerViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ITimerView::staticMetaObject = { {
    QMetaObject::SuperData::link<IView::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ITimerViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ITimerViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10ITimerViewE_t>.metaTypes,
    nullptr
} };

void ITimerView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ITimerView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->stopClicked(); break;
        case 1: _t->closeRequested(); break;
        case 2: _t->timerModeSelected(); break;
        case 3: _t->pomodoroModeSelected((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 4: _t->skipRestRequested(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ITimerView::*)()>(_a, &ITimerView::stopClicked, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITimerView::*)()>(_a, &ITimerView::closeRequested, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITimerView::*)()>(_a, &ITimerView::timerModeSelected, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITimerView::*)(int , int , int )>(_a, &ITimerView::pomodoroModeSelected, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITimerView::*)()>(_a, &ITimerView::skipRestRequested, 4))
            return;
    }
}

const QMetaObject *ITimerView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ITimerView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ITimerViewE_t>.strings))
        return static_cast<void*>(this);
    return IView::qt_metacast(_clname);
}

int ITimerView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IView::qt_metacall(_c, _id, _a);
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
void ITimerView::stopClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ITimerView::closeRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ITimerView::timerModeSelected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ITimerView::pomodoroModeSelected(int _t1, int _t2, int _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1, _t2, _t3);
}

// SIGNAL 4
void ITimerView::skipRestRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
