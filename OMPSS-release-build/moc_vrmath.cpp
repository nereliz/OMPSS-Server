/****************************************************************************
** Meta object code from reading C++ file 'vrmath.h'
**
** Created: Sat Mar 2 12:51:02 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../OMPSS/vrmath.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vrmath.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_vrMath[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,    8,    7,    7, 0x0a,
      49,   46,    7,    7, 0x0a,
      71,    7,    7,    7, 0x0a,
     104,   91,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_vrMath[] = {
    "vrMath\0\0name,id\0addActiveProcess(QString,int)\0"
    "id\0remActiveProcess(int)\0killActiveProcess()\0"
    "status,error\0dbStatus(int,QString)\0"
};

void vrMath::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        vrMath *_t = static_cast<vrMath *>(_o);
        switch (_id) {
        case 0: _t->addActiveProcess((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->remActiveProcess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->killActiveProcess(); break;
        case 3: _t->dbStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData vrMath::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject vrMath::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_vrMath,
      qt_meta_data_vrMath, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &vrMath::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *vrMath::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *vrMath::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_vrMath))
        return static_cast<void*>(const_cast< vrMath*>(this));
    return QObject::qt_metacast(_clname);
}

int vrMath::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
