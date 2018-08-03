/****************************************************************************
** Meta object code from reading C++ file 'RTDisplay.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RTDisplay.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RTDisplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CRTDisplay_t {
    QByteArrayData data[12];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CRTDisplay_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CRTDisplay_t qt_meta_stringdata_CRTDisplay = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CRTDisplay"
QT_MOC_LITERAL(1, 11, 11), // "setTimeInfo"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 17), // "drawPreviewSignal"
QT_MOC_LITERAL(4, 42, 15), // "autoScaleSignal"
QT_MOC_LITERAL(5, 58, 17), // "drawWaveformsSlot"
QT_MOC_LITERAL(6, 76, 13), // "autoScaleSlot"
QT_MOC_LITERAL(7, 90, 5), // "nType"
QT_MOC_LITERAL(8, 96, 14), // "expandVertSlot"
QT_MOC_LITERAL(9, 111, 16), // "contractVertSlot"
QT_MOC_LITERAL(10, 128, 15), // "shiftUpDownSlot"
QT_MOC_LITERAL(11, 144, 10) // "nDirection"

    },
    "CRTDisplay\0setTimeInfo\0\0drawPreviewSignal\0"
    "autoScaleSignal\0drawWaveformsSlot\0"
    "autoScaleSlot\0nType\0expandVertSlot\0"
    "contractVertSlot\0shiftUpDownSlot\0"
    "nDirection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CRTDisplay[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       3,    0,   57,    2, 0x06 /* Public */,
       4,    1,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   61,    2, 0x0a /* Public */,
       6,    1,   62,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    1,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void CRTDisplay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CRTDisplay *_t = static_cast<CRTDisplay *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setTimeInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->drawPreviewSignal(); break;
        case 2: _t->autoScaleSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->drawWaveformsSlot(); break;
        case 4: _t->autoScaleSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->expandVertSlot(); break;
        case 6: _t->contractVertSlot(); break;
        case 7: _t->shiftUpDownSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CRTDisplay::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CRTDisplay::setTimeInfo)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CRTDisplay::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CRTDisplay::drawPreviewSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CRTDisplay::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CRTDisplay::autoScaleSignal)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject CRTDisplay::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CRTDisplay.data,
      qt_meta_data_CRTDisplay,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CRTDisplay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CRTDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CRTDisplay.stringdata0))
        return static_cast<void*>(const_cast< CRTDisplay*>(this));
    return QWidget::qt_metacast(_clname);
}

int CRTDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CRTDisplay::setTimeInfo(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CRTDisplay::drawPreviewSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void CRTDisplay::autoScaleSignal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
