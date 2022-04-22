/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Desktop Application/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[59];
    char stringdata0[1083];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 21), // "on_HTTPButton_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 23), // "on_PascalButton_toggled"
QT_MOC_LITERAL(4, 58, 7), // "checked"
QT_MOC_LITERAL(5, 66, 20), // "on_KPHButton_toggled"
QT_MOC_LITERAL(6, 87, 26), // "on_FarenheitButton_toggled"
QT_MOC_LITERAL(7, 114, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(8, 136, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(9, 164, 5), // "index"
QT_MOC_LITERAL(10, 170, 14), // "updateHomepage"
QT_MOC_LITERAL(11, 185, 14), // "updateHumidity"
QT_MOC_LITERAL(12, 200, 17), // "updateTemperature"
QT_MOC_LITERAL(13, 218, 10), // "updateWind"
QT_MOC_LITERAL(14, 229, 14), // "updatePressure"
QT_MOC_LITERAL(15, 244, 8), // "updateAQ"
QT_MOC_LITERAL(16, 253, 9), // "updateGPS"
QT_MOC_LITERAL(17, 263, 9), // "setTempBG"
QT_MOC_LITERAL(18, 273, 13), // "setHumidityBG"
QT_MOC_LITERAL(19, 287, 9), // "setWindBG"
QT_MOC_LITERAL(20, 297, 13), // "setPressureBG"
QT_MOC_LITERAL(21, 311, 7), // "setAQBG"
QT_MOC_LITERAL(22, 319, 17), // "refreshCurrentTab"
QT_MOC_LITERAL(23, 337, 12), // "downloadFile"
QT_MOC_LITERAL(24, 350, 22), // "on_DownloadAll_clicked"
QT_MOC_LITERAL(25, 373, 16), // "downloadFinished"
QT_MOC_LITERAL(26, 390, 10), // "requestUrl"
QT_MOC_LITERAL(27, 401, 4), // "type"
QT_MOC_LITERAL(28, 406, 4), // "date"
QT_MOC_LITERAL(29, 411, 13), // "deleteAllData"
QT_MOC_LITERAL(30, 425, 20), // "on_DeleteAll_clicked"
QT_MOC_LITERAL(31, 446, 14), // "deleteFinished"
QT_MOC_LITERAL(32, 461, 14), // "getCurrentDate"
QT_MOC_LITERAL(33, 476, 7), // "getDate"
QT_MOC_LITERAL(34, 484, 12), // "getMinMaxAvg"
QT_MOC_LITERAL(35, 497, 6), // "sensor"
QT_MOC_LITERAL(36, 504, 30), // "on_FirstDate_2_userDateChanged"
QT_MOC_LITERAL(37, 535, 31), // "on_SecondDate_2_userDateChanged"
QT_MOC_LITERAL(38, 567, 13), // "getHttpSensor"
QT_MOC_LITERAL(39, 581, 8), // "multHttp"
QT_MOC_LITERAL(40, 590, 22), // "on_AboutButton_clicked"
QT_MOC_LITERAL(41, 613, 21), // "on_AboutClose_clicked"
QT_MOC_LITERAL(42, 635, 24), // "on_DeleteConfirm_clicked"
QT_MOC_LITERAL(43, 660, 21), // "on_DeleteDeny_clicked"
QT_MOC_LITERAL(44, 682, 28), // "on_FirstDate_userDateChanged"
QT_MOC_LITERAL(45, 711, 29), // "on_SecondDate_userDateChanged"
QT_MOC_LITERAL(46, 741, 30), // "on_FirstDate_3_userDateChanged"
QT_MOC_LITERAL(47, 772, 31), // "on_SecondDate_3_userDateChanged"
QT_MOC_LITERAL(48, 804, 30), // "on_FirstDate_4_userDateChanged"
QT_MOC_LITERAL(49, 835, 31), // "on_SecondDate_4_userDateChanged"
QT_MOC_LITERAL(50, 867, 30), // "on_FirstDate_5_userDateChanged"
QT_MOC_LITERAL(51, 898, 31), // "on_SecondDate_5_userDateChanged"
QT_MOC_LITERAL(52, 930, 14), // "getGPSLocation"
QT_MOC_LITERAL(53, 945, 20), // "on_TempDebug_clicked"
QT_MOC_LITERAL(54, 966, 24), // "on_HumidityDebug_clicked"
QT_MOC_LITERAL(55, 991, 20), // "on_WindDebug_clicked"
QT_MOC_LITERAL(56, 1012, 24), // "on_PressureDebug_clicked"
QT_MOC_LITERAL(57, 1037, 18), // "on_AQDebug_clicked"
QT_MOC_LITERAL(58, 1056, 26) // "on_MillibarsButton_toggled"

    },
    "MainWindow\0on_HTTPButton_clicked\0\0"
    "on_PascalButton_toggled\0checked\0"
    "on_KPHButton_toggled\0on_FarenheitButton_toggled\0"
    "on_pushButton_clicked\0on_tabWidget_currentChanged\0"
    "index\0updateHomepage\0updateHumidity\0"
    "updateTemperature\0updateWind\0"
    "updatePressure\0updateAQ\0updateGPS\0"
    "setTempBG\0setHumidityBG\0setWindBG\0"
    "setPressureBG\0setAQBG\0refreshCurrentTab\0"
    "downloadFile\0on_DownloadAll_clicked\0"
    "downloadFinished\0requestUrl\0type\0date\0"
    "deleteAllData\0on_DeleteAll_clicked\0"
    "deleteFinished\0getCurrentDate\0getDate\0"
    "getMinMaxAvg\0sensor\0on_FirstDate_2_userDateChanged\0"
    "on_SecondDate_2_userDateChanged\0"
    "getHttpSensor\0multHttp\0on_AboutButton_clicked\0"
    "on_AboutClose_clicked\0on_DeleteConfirm_clicked\0"
    "on_DeleteDeny_clicked\0"
    "on_FirstDate_userDateChanged\0"
    "on_SecondDate_userDateChanged\0"
    "on_FirstDate_3_userDateChanged\0"
    "on_SecondDate_3_userDateChanged\0"
    "on_FirstDate_4_userDateChanged\0"
    "on_SecondDate_4_userDateChanged\0"
    "on_FirstDate_5_userDateChanged\0"
    "on_SecondDate_5_userDateChanged\0"
    "getGPSLocation\0on_TempDebug_clicked\0"
    "on_HumidityDebug_clicked\0on_WindDebug_clicked\0"
    "on_PressureDebug_clicked\0on_AQDebug_clicked\0"
    "on_MillibarsButton_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      52,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  274,    2, 0x08 /* Private */,
       3,    1,  275,    2, 0x08 /* Private */,
       5,    1,  278,    2, 0x08 /* Private */,
       6,    1,  281,    2, 0x08 /* Private */,
       7,    0,  284,    2, 0x08 /* Private */,
       8,    1,  285,    2, 0x08 /* Private */,
      10,    0,  288,    2, 0x08 /* Private */,
      11,    0,  289,    2, 0x08 /* Private */,
      12,    0,  290,    2, 0x08 /* Private */,
      13,    0,  291,    2, 0x08 /* Private */,
      14,    0,  292,    2, 0x08 /* Private */,
      15,    0,  293,    2, 0x08 /* Private */,
      16,    0,  294,    2, 0x08 /* Private */,
      17,    0,  295,    2, 0x08 /* Private */,
      18,    0,  296,    2, 0x08 /* Private */,
      19,    0,  297,    2, 0x08 /* Private */,
      20,    0,  298,    2, 0x08 /* Private */,
      21,    0,  299,    2, 0x08 /* Private */,
      22,    0,  300,    2, 0x08 /* Private */,
      23,    0,  301,    2, 0x08 /* Private */,
      24,    0,  302,    2, 0x08 /* Private */,
      25,    0,  303,    2, 0x08 /* Private */,
      26,    2,  304,    2, 0x08 /* Private */,
      29,    0,  309,    2, 0x08 /* Private */,
      30,    0,  310,    2, 0x08 /* Private */,
      31,    0,  311,    2, 0x08 /* Private */,
      32,    0,  312,    2, 0x08 /* Private */,
      33,    1,  313,    2, 0x08 /* Private */,
      34,    2,  316,    2, 0x08 /* Private */,
      36,    1,  321,    2, 0x08 /* Private */,
      37,    1,  324,    2, 0x08 /* Private */,
      38,    2,  327,    2, 0x08 /* Private */,
      39,    1,  332,    2, 0x08 /* Private */,
      40,    0,  335,    2, 0x08 /* Private */,
      41,    0,  336,    2, 0x08 /* Private */,
      42,    0,  337,    2, 0x08 /* Private */,
      43,    0,  338,    2, 0x08 /* Private */,
      44,    1,  339,    2, 0x08 /* Private */,
      45,    1,  342,    2, 0x08 /* Private */,
      46,    1,  345,    2, 0x08 /* Private */,
      47,    1,  348,    2, 0x08 /* Private */,
      48,    1,  351,    2, 0x08 /* Private */,
      49,    1,  354,    2, 0x08 /* Private */,
      50,    1,  357,    2, 0x08 /* Private */,
      51,    1,  360,    2, 0x08 /* Private */,
      52,    0,  363,    2, 0x08 /* Private */,
      53,    0,  364,    2, 0x08 /* Private */,
      54,    0,  365,    2, 0x08 /* Private */,
      55,    0,  366,    2, 0x08 /* Private */,
      56,    0,  367,    2, 0x08 /* Private */,
      57,    0,  368,    2, 0x08 /* Private */,
      58,    1,  369,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString,   27,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString, QMetaType::QDate,   28,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   35,   28,
    QMetaType::Void, QMetaType::QDate,   28,
    QMetaType::Void, QMetaType::QDate,   28,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   35,   28,
    QMetaType::Void, QMetaType::QString,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,   28,
    QMetaType::Void, QMetaType::QDate,   28,
    QMetaType::Void, QMetaType::QDate,   28,
    QMetaType::Void, QMetaType::QDate,   28,
    QMetaType::Void, QMetaType::QDate,   28,
    QMetaType::Void, QMetaType::QDate,   28,
    QMetaType::Void, QMetaType::QDate,   28,
    QMetaType::Void, QMetaType::QDate,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_HTTPButton_clicked(); break;
        case 1: _t->on_PascalButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_KPHButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_FarenheitButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_pushButton_clicked(); break;
        case 5: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updateHomepage(); break;
        case 7: _t->updateHumidity(); break;
        case 8: _t->updateTemperature(); break;
        case 9: _t->updateWind(); break;
        case 10: _t->updatePressure(); break;
        case 11: _t->updateAQ(); break;
        case 12: _t->updateGPS(); break;
        case 13: _t->setTempBG(); break;
        case 14: _t->setHumidityBG(); break;
        case 15: _t->setWindBG(); break;
        case 16: _t->setPressureBG(); break;
        case 17: _t->setAQBG(); break;
        case 18: _t->refreshCurrentTab(); break;
        case 19: _t->downloadFile(); break;
        case 20: _t->on_DownloadAll_clicked(); break;
        case 21: _t->downloadFinished(); break;
        case 22: { QString _r = _t->requestUrl((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 23: _t->deleteAllData(); break;
        case 24: _t->on_DeleteAll_clicked(); break;
        case 25: _t->deleteFinished(); break;
        case 26: { QString _r = _t->getCurrentDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 27: { QString _r = _t->getDate((*reinterpret_cast< QDate(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 28: _t->getMinMaxAvg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 29: _t->on_FirstDate_2_userDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 30: _t->on_SecondDate_2_userDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 31: _t->getHttpSensor((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 32: _t->multHttp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 33: _t->on_AboutButton_clicked(); break;
        case 34: _t->on_AboutClose_clicked(); break;
        case 35: _t->on_DeleteConfirm_clicked(); break;
        case 36: _t->on_DeleteDeny_clicked(); break;
        case 37: _t->on_FirstDate_userDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 38: _t->on_SecondDate_userDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 39: _t->on_FirstDate_3_userDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 40: _t->on_SecondDate_3_userDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 41: _t->on_FirstDate_4_userDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 42: _t->on_SecondDate_4_userDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 43: _t->on_FirstDate_5_userDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 44: _t->on_SecondDate_5_userDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 45: _t->getGPSLocation(); break;
        case 46: _t->on_TempDebug_clicked(); break;
        case 47: _t->on_HumidityDebug_clicked(); break;
        case 48: _t->on_WindDebug_clicked(); break;
        case 49: _t->on_PressureDebug_clicked(); break;
        case 50: _t->on_AQDebug_clicked(); break;
        case 51: _t->on_MillibarsButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 52)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 52;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 52)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 52;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
