# ===========================
# Hospital Management System
# ===========================

QT       += core gui qml quick
CONFIG   += c++17
CONFIG   += console
CONFIG   -= app_bundle  # optional, for Windows/Linux

# ===========================
# Project Sources and Headers
# ===========================
SOURCES += main.cpp \
           Doctor.cpp \
           Appointment.cpp

HEADERS += Doctor.h \
           Appointment.h

# ===========================
# QML Resources
# ===========================
RESOURCES += resource.qrc \   # contains Doc_App.qml
    resource.qrc

# ===========================
# Deployment
# ===========================
DISTFILES += Doc_App.qml

# ===========================
# Build settings
# ===========================
TARGET = HospitalManagement
TEMPLATE = app