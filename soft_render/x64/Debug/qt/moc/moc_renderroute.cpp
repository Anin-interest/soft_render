/****************************************************************************
** Meta object code from reading C++ file 'renderroute.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../renderroute.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'renderroute.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSRenderRouteENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSRenderRouteENDCLASS = QtMocHelpers::stringData(
    "RenderRoute",
    "frameOut",
    "",
    "uchar*",
    "image",
    "loop",
    "loop_3d",
    "loop_scene",
    "loop_model",
    "loop_light"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSRenderRouteENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[12];
    char stringdata1[9];
    char stringdata2[1];
    char stringdata3[7];
    char stringdata4[6];
    char stringdata5[5];
    char stringdata6[8];
    char stringdata7[11];
    char stringdata8[11];
    char stringdata9[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSRenderRouteENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSRenderRouteENDCLASS_t qt_meta_stringdata_CLASSRenderRouteENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "RenderRoute"
        QT_MOC_LITERAL(12, 8),  // "frameOut"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 6),  // "uchar*"
        QT_MOC_LITERAL(29, 5),  // "image"
        QT_MOC_LITERAL(35, 4),  // "loop"
        QT_MOC_LITERAL(40, 7),  // "loop_3d"
        QT_MOC_LITERAL(48, 10),  // "loop_scene"
        QT_MOC_LITERAL(59, 10),  // "loop_model"
        QT_MOC_LITERAL(70, 10)   // "loop_light"
    },
    "RenderRoute",
    "frameOut",
    "",
    "uchar*",
    "image",
    "loop",
    "loop_3d",
    "loop_scene",
    "loop_model",
    "loop_light"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSRenderRouteENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   53,    2, 0x0a,    3 /* Public */,
       6,    0,   54,    2, 0x0a,    4 /* Public */,
       7,    0,   55,    2, 0x0a,    5 /* Public */,
       8,    0,   56,    2, 0x0a,    6 /* Public */,
       9,    0,   57,    2, 0x0a,    7 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject RenderRoute::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSRenderRouteENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSRenderRouteENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSRenderRouteENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<RenderRoute, std::true_type>,
        // method 'frameOut'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<unsigned char *, std::false_type>,
        // method 'loop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loop_3d'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loop_scene'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loop_model'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loop_light'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void RenderRoute::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RenderRoute *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->frameOut((*reinterpret_cast< std::add_pointer_t<uchar*>>(_a[1]))); break;
        case 1: _t->loop(); break;
        case 2: _t->loop_3d(); break;
        case 3: _t->loop_scene(); break;
        case 4: _t->loop_model(); break;
        case 5: _t->loop_light(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RenderRoute::*)(unsigned char * );
            if (_t _q_method = &RenderRoute::frameOut; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *RenderRoute::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RenderRoute::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSRenderRouteENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RenderRoute::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void RenderRoute::frameOut(unsigned char * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
