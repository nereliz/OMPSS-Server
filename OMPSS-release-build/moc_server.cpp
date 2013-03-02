/****************************************************************************
** Meta object code from reading C++ file 'server.h'
**
** Created: Sat Mar 2 12:51:00 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../OMPSS/server.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'server.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_server[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      30,   26,    7,    7, 0x05,
      58,   26,    7,    7, 0x05,
      93,   26,    7,    7, 0x05,
     126,   26,    7,    7, 0x05,
     153,   26,    7,    7, 0x05,
     183,   26,    7,    7, 0x05,
     225,  217,    7,    7, 0x05,
     260,  257,    7,    7, 0x05,
     299,  286,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
     322,    7,    7,    7, 0x08,
     352,    7,    7,    7, 0x08,
     382,    7,    7,    7, 0x08,
     406,    7,    7,    7, 0x08,
     431,    7,    7,    7, 0x08,
     472,    7,    7,    7, 0x08,
     500,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_server[] = {
    "server\0\0clientConnected()\0cnt\0"
    "activeProcessCntChange(int)\0"
    "activeCompileProcessCntChange(int)\0"
    "activeProcessCntTotalChange(int)\0"
    "processCntTotalChange(int)\0"
    "processCntExeTotalChange(int)\0"
    "processCntCompileTotalChange(int)\0"
    "name,id\0activeProcessAdded(QString,int)\0"
    "id\0activeProcessRemoved(int)\0status,error\0"
    "dbConnect(int,QString)\0"
    "increaseActiveExeProcessCnt()\0"
    "decreaseActiveExeProcessCnt()\0"
    "finishedExeProgram(int)\0"
    "finishedCompProgram(int)\0"
    "errorCompProgram(QProcess::ProcessError)\0"
    "executeProgram(QStringList)\0"
    "compileProgram(QStringList)\0"
};

void server::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        server *_t = static_cast<server *>(_o);
        switch (_id) {
        case 0: _t->clientConnected(); break;
        case 1: _t->activeProcessCntChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->activeCompileProcessCntChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->activeProcessCntTotalChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->processCntTotalChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->processCntExeTotalChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->processCntCompileTotalChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->activeProcessAdded((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->activeProcessRemoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->dbConnect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->increaseActiveExeProcessCnt(); break;
        case 11: _t->decreaseActiveExeProcessCnt(); break;
        case 12: _t->finishedExeProgram((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->finishedCompProgram((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->errorCompProgram((*reinterpret_cast< QProcess::ProcessError(*)>(_a[1]))); break;
        case 15: _t->executeProgram((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 16: _t->compileProgram((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData server::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject server::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_server,
      qt_meta_data_server, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &server::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *server::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *server::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_server))
        return static_cast<void*>(const_cast< server*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int server::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void server::clientConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void server::activeProcessCntChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void server::activeCompileProcessCntChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void server::activeProcessCntTotalChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void server::processCntTotalChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void server::processCntExeTotalChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void server::processCntCompileTotalChange(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void server::activeProcessAdded(QString _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void server::activeProcessRemoved(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void server::dbConnect(int _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE
