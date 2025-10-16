/****************************************************************************
** Meta object code from reading C++ file 'ITweekApiService.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../calendar/ITweekApiService.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ITweekApiService.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN16ITweekApiServiceE_t {};
} // unnamed namespace

template <> constexpr inline auto ITweekApiService::qt_create_metaobjectdata<qt_meta_tag_ZN16ITweekApiServiceE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ITweekApiService",
        "authenticationSuccess",
        "",
        "idToken",
        "refreshToken",
        "authenticationFailed",
        "errorMessage",
        "calendarsFetchSuccess",
        "QList<TweekCalendar>",
        "calendars",
        "calendarsFetchFailed",
        "tasksFetchSuccess",
        "QList<TweekTask>",
        "tasks",
        "tasksFetchFailed"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'authenticationSuccess'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 }, { QMetaType::QString, 4 },
        }}),
        // Signal 'authenticationFailed'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'calendarsFetchSuccess'
        QtMocHelpers::SignalData<void(const QVector<TweekCalendar> &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 8, 9 },
        }}),
        // Signal 'calendarsFetchFailed'
        QtMocHelpers::SignalData<void(const QString &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Signal 'tasksFetchSuccess'
        QtMocHelpers::SignalData<void(const QVector<TweekTask> &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 13 },
        }}),
        // Signal 'tasksFetchFailed'
        QtMocHelpers::SignalData<void(const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ITweekApiService, qt_meta_tag_ZN16ITweekApiServiceE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ITweekApiService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ITweekApiServiceE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ITweekApiServiceE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16ITweekApiServiceE_t>.metaTypes,
    nullptr
} };

void ITweekApiService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ITweekApiService *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->authenticationSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 1: _t->authenticationFailed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->calendarsFetchSuccess((*reinterpret_cast< std::add_pointer_t<QList<TweekCalendar>>>(_a[1]))); break;
        case 3: _t->calendarsFetchFailed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->tasksFetchSuccess((*reinterpret_cast< std::add_pointer_t<QList<TweekTask>>>(_a[1]))); break;
        case 5: _t->tasksFetchFailed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ITweekApiService::*)(const QString & , const QString & )>(_a, &ITweekApiService::authenticationSuccess, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITweekApiService::*)(const QString & )>(_a, &ITweekApiService::authenticationFailed, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITweekApiService::*)(const QVector<TweekCalendar> & )>(_a, &ITweekApiService::calendarsFetchSuccess, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITweekApiService::*)(const QString & )>(_a, &ITweekApiService::calendarsFetchFailed, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITweekApiService::*)(const QVector<TweekTask> & )>(_a, &ITweekApiService::tasksFetchSuccess, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITweekApiService::*)(const QString & )>(_a, &ITweekApiService::tasksFetchFailed, 5))
            return;
    }
}

const QMetaObject *ITweekApiService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ITweekApiService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16ITweekApiServiceE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ITweekApiService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ITweekApiService::authenticationSuccess(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void ITweekApiService::authenticationFailed(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void ITweekApiService::calendarsFetchSuccess(const QVector<TweekCalendar> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void ITweekApiService::calendarsFetchFailed(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void ITweekApiService::tasksFetchSuccess(const QVector<TweekTask> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void ITweekApiService::tasksFetchFailed(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}
QT_WARNING_POP
