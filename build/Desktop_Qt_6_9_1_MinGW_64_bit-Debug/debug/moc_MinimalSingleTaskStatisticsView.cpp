/****************************************************************************
** Meta object code from reading C++ file 'MinimalSingleTaskStatisticsView.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/theme/minimal/MinimalSingleTaskStatisticsView.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MinimalSingleTaskStatisticsView.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN31MinimalSingleTaskStatisticsViewE_t {};
} // unnamed namespace

template <> constexpr inline auto MinimalSingleTaskStatisticsView::qt_create_metaobjectdata<qt_meta_tag_ZN31MinimalSingleTaskStatisticsViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MinimalSingleTaskStatisticsView",
        "onPrevWeekClicked",
        "",
        "onNextWeekClicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onPrevWeekClicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onNextWeekClicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MinimalSingleTaskStatisticsView, qt_meta_tag_ZN31MinimalSingleTaskStatisticsViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MinimalSingleTaskStatisticsView::staticMetaObject = { {
    QMetaObject::SuperData::link<ISingleTaskStatisticsView::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN31MinimalSingleTaskStatisticsViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN31MinimalSingleTaskStatisticsViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN31MinimalSingleTaskStatisticsViewE_t>.metaTypes,
    nullptr
} };

void MinimalSingleTaskStatisticsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MinimalSingleTaskStatisticsView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onPrevWeekClicked(); break;
        case 1: _t->onNextWeekClicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *MinimalSingleTaskStatisticsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MinimalSingleTaskStatisticsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN31MinimalSingleTaskStatisticsViewE_t>.strings))
        return static_cast<void*>(this);
    return ISingleTaskStatisticsView::qt_metacast(_clname);
}

int MinimalSingleTaskStatisticsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ISingleTaskStatisticsView::qt_metacall(_c, _id, _a);
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
