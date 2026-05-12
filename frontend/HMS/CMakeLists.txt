cmake_minimum_required(VERSION 3.19)
project(HMS LANGUAGES CXX)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()
qt_add_executable(HMS
    WIN32 MACOSX_BUNDLE
    main.cpp
    loginwindow.cpp        loginwindow.h
    admindashboard.cpp     admindashboard.h
    doctordashboard.cpp    doctordashboard.h
    patientdashboard.cpp   patientdashboard.h
    patientregisterdialog.cpp     patientregisterdialog.h
    patientlistdialog.cpp         patientlistdialog.h
    patientupdatedialog.cpp       patientupdatedialog.h
    staffregisterdialog.cpp       staffregisterdialog.h
    stafflistdialog.cpp           stafflistdialog.h
    staffupdatedialog.cpp         staffupdatedialog.h
    doctorregisterdialog.cpp      doctorregisterdialog.h
    doctorlistdialog.cpp          doctorlistdialog.h
    doctorupdatedialog.cpp        doctorupdatedialog.h
    appointmentbookdialog.cpp     appointmentbookdialog.h
    appointmentlistdialog.cpp     appointmentlistdialog.h
    credentialsdialog.cpp         credentialsdialog.h
    personalinfodialog.cpp        personalinfodialog.h
    medicalrecordsviewdialog.cpp  medicalrecordsviewdialog.h
    medicalrecordadddialog.cpp    medicalrecordadddialog.h
    billingdialog.cpp             billingdialog.h
    roomassigndialog.cpp          roomassigndialog.h
    dischargedialog.cpp           dischargedialog.h
    pharmacyinventorydialog.cpp   pharmacyinventorydialog.h
    addmedicinedialog.cpp         addmedicinedialog.h
    prescriptiondialog.cpp        prescriptiondialog.h
    restockdialog.cpp             restockdialog.h
    pharmacyrecordsdialog.cpp     pharmacyrecordsdialog.h
    ambulanceregisterdialog.cpp   ambulanceregisterdialog.h
    ambulancelistdialog.cpp       ambulancelistdialog.h
    ambulanceupdatedialog.cpp     ambulanceupdatedialog.h
    adminregisterdialog.cpp       adminregisterdialog.h
    ../../Person.cpp           ../../Person.h
    ../../Patient.cpp          ../../Patient.h
    ../../Doctor.cpp           ../../Doctor.h
    ../../Staff.cpp            ../../Staff.h
    ../../Room.cpp             ../../Room.h
    ../../RBAC.cpp             ../../RBAC.h
    ../../Ambulance.cpp        ../../Ambulance.h
    ../../Appointment.cpp      ../../Appointment.h
    ../../Login.cpp            ../../Login.h
    ../../Medicine.cpp         ../../Medicine.h
    ../../Pharmacy.cpp         ../../Pharmacy.h
    ../../MedicalRecords.cpp   ../../MedicalRecords.h
    ../../Billing.cpp          ../../Billing.h
    ../../Prescription.cpp     ../../Prescription.h
    ../../SystemController.cpp ../../SystemController.h
)
target_link_libraries(HMS PRIVATE Qt::Core Qt::Widgets)
install(TARGETS HMS
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
# TXT files are now accessed directly from the project root in development
# This avoids confusion where updates persist to build folder copies but not source files