/****************************************************************************
** Meta object code from reading C++ file 'ISingleTaskStatisticsView.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/interfaces/ISingleTaskStatisticsView.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ISingleTaskStatisticsView.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN25ISingleTaskStatisticsViewE_t {};
} // unnamed namespace

template <> constexpr inline auto ISingleTaskStatisticsView::qt_create_metaobjectdata<qt_meta_tag_ZN25ISingleTaskStatisticsViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ISingleTaskStatisticsView",
        "dateRangeChanged",
        "",
        "from",
        "to",
        "closeRequested"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'dateRangeChanged'
        QtMocHelpers::SignalData<void(const QDate &, const QDate &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QDate, 3 }, { QMetaType::QDate, 4 },
        }}),
        // Signal 'closeRequested'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ISingleTaskStatisticsView, qt_meta_tag_ZN25ISingleTaskStatisticsViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ISingleTaskStatisticsView::staticMetaObject = { {
    QMetaObject::SuperData::link<IView::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN25ISingleTaskStatisticsViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN25ISingleTaskStatisticsViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN25ISingleTaskStatisticsViewE_t>.metaTypes,
    nullptr
} };

void ISingleTaskStatisticsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ISingleTaskStatisticsView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->dateRangeChanged((*reinterpret_cast< std::add_pointer_t<QDate>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QDate>>(_a[2]))); break;
        case 1: _t->closeRequested(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ISingleTaskStatisticsView::*)(const QDate & , const QDate & )>(_a, &ISingleTaskStatisticsView::dateRangeChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ISingleTaskStatisticsView::*)()>(_a, &ISingleTaskStatisticsView::closeRequested, 1))
            return;
    }
}

const QMetaObject *ISingleTaskStatisticsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ISingleTaskStatisticsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN25ISingleTaskStatisticsViewE_t>.strings))
        return static_cast<void*>(this);
    return IView::qt_metacast(_clname);
}

int ISingleTaskStatisticsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IView::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void ISingleTaskStatisticsView::dateRangeChanged(const QDate & _t1, const QDate & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1, _t2);
}

// SIGNAL 1
void ISingleTaskStatisticsView::closeRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
