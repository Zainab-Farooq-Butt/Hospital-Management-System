cmake_minimum_required(VERSION 3.19)
project(HMS LANGUAGES CXX)

<<<<<<< Updated upstream
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
=======
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

>>>>>>> Stashed changes
qt_standard_project_setup()

qt_add_executable(HMS
    WIN32 MACOSX_BUNDLE
    main.cpp
<<<<<<< Updated upstream
    loginwindow.cpp        loginwindow.h
    admindashboard.cpp     admindashboard.h
    doctordashboard.cpp    doctordashboard.h
    patientdashboard.cpp   patientdashboard.h

    patientregisterdialog.cpp     patientregisterdialog.h
    patientlistdialog.cpp         patientlistdialog.h
    patientupdatedialog.cpp       patientupdatedialog.h
    staffregisterdialog.cpp       staffregisterdialog.h
    stafflistdialog.cpp           stafflistdialog.h
    doctorregisterdialog.cpp      doctorregisterdialog.h
    doctorlistdialog.cpp          doctorlistdialog.h
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
=======
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    ../../Login.cpp
    ../../Login.h
)

qt_add_translations(
    TARGETS HMS
    TS_FILES HMS_en_GB.ts
)

target_link_libraries(HMS
    PRIVATE
        Qt::Core
        Qt::Widgets
)
>>>>>>> Stashed changes

install(TARGETS HMS
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

<<<<<<< Updated upstream
file(GLOB TXT_FILES "../../*.txt")
file(COPY ${TXT_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
=======
qt_generate_deploy_app_script(
    TARGET HMS
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
>>>>>>> Stashed changes
