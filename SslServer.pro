QT += network gui core widgets

CONFIG += c++11 console
CONFIG -= app_bundle openssl-linked

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
        qsslserver.h \
    mainwindow.h

SOURCES += \
        main.cpp \
        qsslserver.cpp \
    mainwindow.cpp

INCLUDEPATH += /opt/openssl/openssl-1.0.2h/include

LIBS += /opt/openssl/openssl-1.0.2h/libcrypto.a
LIBS += /opt/openssl/openssl-1.0.2h/libssl.a

RESOURCES += sslserver.qrc

copydata.commands = $(COPY_DIR) $$PWD/cert $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
