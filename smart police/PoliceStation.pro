QT       += core gui
QT       += sql printsupport
QT       += network
QT       += multimedia
QT       +=serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


DEFINES += SMTP_BUILD
# You can also make yo:;,ç     cvxur code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    agent.cpp \
    ajoutercin.cpp \
    arduino.cpp \
    arme.cpp \
    budget.cpp \
    categories.cpp \
    cellule.cpp \
    certificat.cpp \
    citoyen.cpp \
    classe.cpp \
    connection.cpp \
    main.cpp \
    maintenance.cpp \
    mainwindow.cpp \
    mission.cpp \
    notification.cpp \
    passeport.cpp \
    reclamation.cpp \
    src/emailaddress.cpp \
    src/mimeattachment.cpp \
    src/mimecontentformatter.cpp \
    src/mimefile.cpp \
    src/mimehtml.cpp \
    src/mimeinlinefile.cpp \
    src/mimemessage.cpp \
    src/mimemultipart.cpp \
    src/mimepart.cpp \
    src/mimetext.cpp \
    src/quotedprintable.cpp \
    src/smtpclient.cpp \
    vehicule.cpp

HEADERS += \
    admin.h \
    agent.h \
    ajoutercin.h \
    arduino.h \
    arme.h \
    budget.h \
    categories.h \
    cellule.h \
    certificat.h \
    citoyen.h \
    classe.h \
    connection.h \
    maintenance.h \
    mainwindow.h \
    mission.h \
    notification.h \
    passeport.h \
    reclamation.h \
    src/SmtpMime \
    src/emailaddress.h \
    src/mimeattachment.h \
    src/mimecontentformatter.h \
    src/mimefile.h \
    src/mimehtml.h \
    src/mimeinlinefile.h \
    src/mimemessage.h \
    src/mimemultipart.h \
    src/mimepart.h \
    src/mimetext.h \
    src/quotedprintable.h \
    src/smtpclient.h \
    src/smtpexports.h \
    vehicule.h

FORMS += \
    mainwindow.ui


RESOURCES += \
    resource.qrc
