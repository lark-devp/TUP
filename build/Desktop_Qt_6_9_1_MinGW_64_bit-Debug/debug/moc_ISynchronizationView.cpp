/****************************************************************************
** Meta object code from reading C++ file 'ISynchronizationView.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/interfaces/ISynchronizationView.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ISynchronizationView.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN20ISynchronizationViewE_t {};
} // unnamed namespace

template <> constexpr inline auto ISynchronizationView::qt_create_metaobjectdata<qt_meta_tag_ZN20ISynchronizationViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ISynchronizationView",
        "closeRequested",
        "",
        "connectRequested",
        "email",
        "password",
        "calendarsRequested",
        "tasksRequested",
        "calendarId",
        "tasksSelected",
        "QList<TweekTask>",
        "selectedTasks"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'closeRequested'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'connectRequested'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 4 }, { QMetaType::QString, 5 },
        }}),
        // Signal 'calendarsRequested'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'tasksRequested'
        QtMocHelpers::SignalData<void(const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Signal 'tasksSelected'
        QtMocHelpers::SignalData<void(const QVector<TweekTask> &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ISynchronizationView, qt_meta_tag_ZN20ISynchronizationViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ISynchronizationView::staticMetaObject = { {
    QMetaObject::SuperData::link<IView::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20ISynchronizationViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20ISynchronizationViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN20ISynchronizationViewE_t>.metaTypes,
    nullptr
} };

void ISynchronizationView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ISynchronizationView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->closeRequested(); break;
        case 1: _t->connectRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 2: _t->calendarsRequested(); break;
        case 3: _t->tasksRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->tasksSelected((*reinterpret_cast< std::add_pointer_t<QList<TweekTask>>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ISynchronizationView::*)()>(_a, &ISynchronizationView::closeRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ISynchronizationView::*)(const QString & , const QString & )>(_a, &ISynchronizationView::connectRequested, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ISynchronizationView::*)()>(_a, &ISynchronizationView::calendarsRequested, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ISynchronizationView::*)(const QString & )>(_a, &ISynchronizationView::tasksRequested, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ISynchronizationView::*)(const QVector<TweekTask> & )>(_a, &ISynchronizationView::tasksSelected, 4))
            return;
    }
}

const QMetaObject *ISynchronizationView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ISynchronizationView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN20ISynchronizationViewE_t>.strings))
        return static_cast<void*>(this);
    return IView::qt_metacast(_clname);
}

int ISynchronizationView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ISynchronizationView::closeRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ISynchronizationView::connectRequested(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}

// SIGNAL 2
void ISynchronizationView::calendarsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ISynchronizationView::tasksRequested(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void ISynchronizationView::tasksSelected(const QVector<TweekTask> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}
QT_WARNING_POP
