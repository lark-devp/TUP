/****************************************************************************
** Meta object code from reading C++ file 'ITaskSelectionView.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ui/interfaces/ITaskSelectionView.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ITaskSelectionView.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN18ITaskSelectionViewE_t {};
} // unnamed namespace

template <> constexpr inline auto ITaskSelectionView::qt_create_metaobjectdata<qt_meta_tag_ZN18ITaskSelectionViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ITaskSelectionView",
        "taskSelectedForTimer",
        "",
        "taskId",
        "statisticsRequestedForTask",
        "allTasksStatisticsRequested",
        "addTaskRequested",
        "synchronizationRequested",
        "refreshRequested"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'taskSelectedForTimer'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'statisticsRequestedForTask'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'allTasksStatisticsRequested'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'addTaskRequested'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'synchronizationRequested'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'refreshRequested'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ITaskSelectionView, qt_meta_tag_ZN18ITaskSelectionViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ITaskSelectionView::staticMetaObject = { {
    QMetaObject::SuperData::link<IView::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18ITaskSelectionViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18ITaskSelectionViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN18ITaskSelectionViewE_t>.metaTypes,
    nullptr
} };

void ITaskSelectionView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ITaskSelectionView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->taskSelectedForTimer((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->statisticsRequestedForTask((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->allTasksStatisticsRequested(); break;
        case 3: _t->addTaskRequested(); break;
        case 4: _t->synchronizationRequested(); break;
        case 5: _t->refreshRequested(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ITaskSelectionView::*)(const QString & )>(_a, &ITaskSelectionView::taskSelectedForTimer, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITaskSelectionView::*)(const QString & )>(_a, &ITaskSelectionView::statisticsRequestedForTask, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITaskSelectionView::*)()>(_a, &ITaskSelectionView::allTasksStatisticsRequested, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITaskSelectionView::*)()>(_a, &ITaskSelectionView::addTaskRequested, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITaskSelectionView::*)()>(_a, &ITaskSelectionView::synchronizationRequested, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ITaskSelectionView::*)()>(_a, &ITaskSelectionView::refreshRequested, 5))
            return;
    }
}

const QMetaObject *ITaskSelectionView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ITaskSelectionView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN18ITaskSelectionViewE_t>.strings))
        return static_cast<void*>(this);
    return IView::qt_metacast(_clname);
}

int ITaskSelectionView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = IView::qt_metacall(_c, _id, _a);
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
void ITaskSelectionView::taskSelectedForTimer(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ITaskSelectionView::statisticsRequestedForTask(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void ITaskSelectionView::allTasksStatisticsRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ITaskSelectionView::addTaskRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ITaskSelectionView::synchronizationRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ITaskSelectionView::refreshRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
