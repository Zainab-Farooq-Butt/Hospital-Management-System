#include <QApplication>
#include "loginwindow.h"
#include "../../Patient.h"
#include "../../Doctor.h"
#include "../../Staff.h"
#include "../../Appointment.h"
#include "../../MedicalRecords.h"
#include "../../Billing.h"
#include "../../Ambulance.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Patient::loadCounterFromFile("Patient.txt");
    Doctor::loadCounterFromFile("Doctor.txt");
    Staff::loadCounterFromFile("Staff.txt");
    Appointment::loadCounterFromFile("Appointment.txt");
    MedicalRecords::loadCounterFromFile("MedicalRecords.txt");
    Billing::loadCounterFromFile("Billing.txt");
    Ambulance::loadCounterFromFile("Ambulance.txt");

    app.setStyleSheet(
        "QMainWindow, QDialog { background-color: #f0f4f8; }"
        "QWidget { background-color: transparent; color: #003366; font-family: 'Segoe UI', Arial, sans-serif; }"
        "QMainWindow > QWidget, QDialog > QWidget { background-color: #f0f4f8; }" // Central widgets
        "QTabWidget::pane { border: 1px solid #b0c4de; background-color: white; border-radius: 4px; }"
        "QTabBar::tab { background: #e0e8f0; color: #003366; padding: 10px 20px; border: 1px solid #b0c4de; border-bottom: none; border-top-left-radius: 4px; border-top-right-radius: 4px; margin-right: 2px; }"
        "QTabBar::tab:selected { background: white; font-weight: bold; border-top: 3px solid #00509e; }"
        "QTabBar::tab:hover { background: #d0e0e3; }"
        "QTabWidget > QWidget { background-color: white; }" // The actual tabs
        "QPushButton {"
        "    background-color: #00509e;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 4px;"
        "    padding: 8px 16px;"
        "}"
        "QPushButton:hover { background-color: #003f7d; }"
        "QPushButton:pressed { background-color: #002e5c; }"
        "QLineEdit, QDateEdit, QComboBox, QSpinBox, QDoubleSpinBox {"
        "    border: 1px solid #b0c4de;"
        "    border-radius: 4px;"
        "    padding: 4px;"
        "    background-color: white;"
        "    color: #003366;"
        "}"
        "QLineEdit:focus, QDateEdit:focus, QComboBox:focus {"
        "    border: 1px solid #00509e;"
        "}"
        "QLabel {"
        "    color: #003366;"
        "    background-color: transparent;"
        "}"
        "QTableWidget, QTableView {"
        "    background-color: white;"
        "    gridline-color: #d0e0e3;"
        "    selection-background-color: #00509e;"
        "    selection-color: white;"
        "    border: 1px solid #b0c4de;"
        "}"
        "QHeaderView::section {"
        "    background-color: #00509e;"
        "    color: white;"
        "    padding: 4px;"
        "    border: 1px solid #003f7d;"
        "}"
        "QScrollBar:vertical {"
        "    background: #e0e8f0;"
        "    width: 12px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #00509e;"
        "    min-height: 20px;"
        "    border-radius: 4px;"
        "}"
    );

    LoginWindow w;
    w.show();
    return app.exec();
}