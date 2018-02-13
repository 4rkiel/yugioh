/****************************************************************************
** Meta object code from reading C++ file 'introButt.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "introButt.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'introButt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Task[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      21,    5,    5,    5, 0x0a,
      40,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Task[] = {
    "Task\0\0workFinished()\0runButtonPressed()\0"
    "runButtonReleased()\0"
};

void Task::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Task *_t = static_cast<Task *>(_o);
        switch (_id) {
        case 0: _t->workFinished(); break;
        case 1: _t->runButtonPressed(); break;
        case 2: _t->runButtonReleased(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Task::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Task::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Task,
      qt_meta_data_Task, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Task::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Task::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Task::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Task))
        return static_cast<void*>(const_cast< Task*>(this));
    return QObject::qt_metacast(_clname);
}

int Task::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Task::workFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_IntroButt[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      27,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_IntroButt[] = {
    "IntroButt\0\0buttonPressed()\0buttonReleased()\0"
};

void IntroButt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IntroButt *_t = static_cast<IntroButt *>(_o);
        switch (_id) {
        case 0: _t->buttonPressed(); break;
        case 1: _t->buttonReleased(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData IntroButt::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IntroButt::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_IntroButt,
      qt_meta_data_IntroButt, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IntroButt::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IntroButt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IntroButt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IntroButt))
        return static_cast<void*>(const_cast< IntroButt*>(this));
    return QPushButton::qt_metacast(_clname);
}

int IntroButt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
