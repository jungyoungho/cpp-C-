TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    make_roundkey.h \
    shift_rows.h \
    mix_column.h \
    rounding.h \
    rijndael.h \
    char_to_hex.h
