TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    mix_column.h \
    make_roundkey.h \
    main_round.h \
    rounding.h \
    shift_rows.h \
    encode_base64.h
