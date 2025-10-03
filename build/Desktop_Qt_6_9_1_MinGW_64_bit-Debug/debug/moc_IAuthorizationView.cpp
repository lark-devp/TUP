/****************************************************************************
** Meta object code from reading C++ file 'IAuthorizationView.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/interfaces/IAuthorizationView.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'IAuthorizationView.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN18IAuthorizationViewE_t {};
} // unnamed namespace

template <> constexpr inline auto IAuthorizationView::qt_create_metaobjectdata<qt_meta_tag_ZN18IAuthorizationViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "IAuthorizationView",
        "loginRequested",
        "",
        "username",
        "password",
        "registrationRequested",
        "passwordRecoveryRequested"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'loginRequested'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::QString, 4 },
        }}),
        // Signal 'registrationRequested'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'passwordRecoveryRequested'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<IAuthorizationView, qt_meta_tag_ZN18IAuthorizationViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject IAuthorizationView::staticMetaObject = { {
    QMetaObject::SuperData::link<IView::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18IAuthorizationViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18IAuthorizationViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN18IAuthorizationViewE_t>.metaTypes,
    nullptr
} };

void IAuthorizationView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<IAuthorizationView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->loginRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->registrationRequested(); break;
        case 2: _t->passwordRecoveryRequested(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (IAuthorizationView::*)(const QString & , const QString & )>(_a, &IAuthorizationView::loginRequested, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (IAuthorizationView::*)()>(_a, &IAuthorizationView::registrationRequested, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (IAuthorizationView::*)()>(_a, &IAuthorizationView::passwordRecoveryRequested, 2))
            return;
    }
}

const QMetaObject *IAuthorizationView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IAuthorizationView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18IAuthorizationViewE_t>.strings))
        return static_cast<void*>(this);
    return IView::qt_metacast(_clname);
}

int IAuthorizationView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IView::qt_metacall(_c, _id, _a);
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
void IAuthorizationView::loginRequested(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void IAuthorizationView::registrationRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void IAuthorizationView::passwordRecoveryRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
