cmake_minimum_required(VERSION 3.19)
project(HMS LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()

qt_add_executable(HMS
    WIN32 MACOSX_BUNDLE
    main.cpp
    loginwindow.h loginwindow.cpp
    admindashboard.h admindashboard.cpp
    doctordashboard.h doctordashboard.cpp
    patientdashboard.h patientdashboard.cpp
    patientregisterdialog.h patientregisterdialog.cpp
    patientlistdialog.h patientlistdialog.cpp
    patientupdatedialog.h patientupdatedialog.cpp
    staffregisterdialog.h staffregisterdialog.cpp
    stafflistdialog.h stafflistdialog.cpp
    doctorregisterdialog.h doctorregisterdialog.cpp
    doctorlistdialog.h doctorlistdialog.cpp
    appointmentbookdialog.h appointmentbookdialog.cpp
    appointmentlistdialog.h appointmentlistdialog.cpp
    credentialsdialog.h credentialsdialog.cpp
    personalinfodialog.h personalinfodialog.cpp
    medicalrecordsviewdialog.h medicalrecordsviewdialog.cpp
    medicalrecordadddialog.h medicalrecordadddialog.cpp
    billingdialog.h billingdialog.cpp
    roomassigndialog.h roomassigndialog.cpp
    dischargedialog.h dischargedialog.cpp
    pharmacyinventorydialog.h pharmacyinventorydialog.cpp
    addmedicinedialog.h addmedicinedialog.cpp
    prescriptiondialog.h prescriptiondialog.cpp
    restockdialog.h restockdialog.cpp
    pharamacyrecordsdialog.h pharamacyrecordsdialog.cpp
    ambulanceregisterdialog.h ambulanceregisterdialog.cpp
    ambulancelistdialog.h ambulancelistdialog.cpp
    main.cpp

    loginwindow.cpp        loginwindow.h
    admindashboard.cpp     admindashboard.h
    doctordashboard.cpp    doctordashboard.h
    patientdashboard.cpp   patientdashboard.h

    PatientRegisterDialog.cpp     PatientRegisterDialog.h
    PatientListDialog.cpp         PatientListDialog.h
    PatientUpdateDialog.cpp       PatientUpdateDialog.h
    StaffRegisterDialog.cpp       StaffRegisterDialog.h
    StaffListDialog.cpp           StaffListDialog.h
    DoctorRegisterDialog.cpp      DoctorRegisterDialog.h
    DoctorListDialog.cpp          DoctorListDialog.h
    AppointmentBookDialog.cpp     AppointmentBookDialog.h
    AppointmentListDialog.cpp     AppointmentListDialog.h
    CredentialsDialog.cpp         CredentialsDialog.h
    PersonalInfoDialog.cpp        PersonalInfoDialog.h
    MedicalRecordsViewDialog.cpp  MedicalRecordsViewDialog.h
    MedicalRecordAddDialog.cpp    MedicalRecordAddDialog.h
    BillingDialog.cpp             BillingDialog.h
    RoomAssignDialog.cpp          RoomAssignDialog.h
    DischargeDialog.cpp           DischargeDialog.h
    PharmacyInventoryDialog.cpp   PharmacyInventoryDialog.h
    AddMedicineDialog.cpp         AddMedicineDialog.h
    PrescriptionDialog.cpp        PrescriptionDialog.h
    RestockDialog.cpp             RestockDialog.h
    PharmacyRecordsDialog.cpp     PharmacyRecordsDialog.h
    AmbulanceRegisterDialog.cpp   AmbulanceRegisterDialog.h
    AmbulanceListDialog.cpp       AmbulanceListDialog.h

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
    ../../SystemController.cpp ../../SystemController.h
)

target_link_libraries(HMS PRIVATE Qt::Core Qt::Widgets)

install(TARGETS HMS
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
