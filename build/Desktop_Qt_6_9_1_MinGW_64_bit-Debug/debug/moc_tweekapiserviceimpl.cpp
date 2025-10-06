/****************************************************************************
** Meta object code from reading C++ file 'TweekApiServiceImpl.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../calendar/TweekApiServiceImpl.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TweekApiServiceImpl.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN19TweekApiServiceImplE_t {};
} // unnamed namespace

template <> constexpr inline auto TweekApiServiceImpl::qt_create_metaobjectdata<qt_meta_tag_ZN19TweekApiServiceImplE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TweekApiServiceImpl",
        "onAuthenticationReplyFinished",
        "",
        "onRefreshTokenReplyFinished"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onAuthenticationReplyFinished'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onRefreshTokenReplyFinished'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TweekApiServiceImpl, qt_meta_tag_ZN19TweekApiServiceImplE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TweekApiServiceImpl::staticMetaObject = { {
    QMetaObject::SuperData::link<ITweekApiService::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19TweekApiServiceImplE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19TweekApiServiceImplE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN19TweekApiServiceImplE_t>.metaTypes,
    nullptr
} };

void TweekApiServiceImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TweekApiServiceImpl *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onAuthenticationReplyFinished(); break;
        case 1: _t->onRefreshTokenReplyFinished(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *TweekApiServiceImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TweekApiServiceImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19TweekApiServiceImplE_t>.strings))
        return static_cast<void*>(this);
    return ITweekApiService::qt_metacast(_clname);
}

int TweekApiServiceImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ITweekApiService::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
