#include <QApplication>
#include "loginwindow.h"
#include "../../Patient.h"
#include "../../Doctor.h"
#include "../../Staff.h"
#include "../../Appointment.h"
#include "../../MedicalRecords.h"
#include "../../Billing.h"
#include "../../Ambulance.h"

#include <QDir>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Fix for Shadow Builds: Ensure working directory is the project root (where .txt files are)
    QDir dir(QCoreApplication::applicationDirPath());
    // Move up from build/debug/release folders until we find Patient.txt or reach root
    while (!dir.exists("Patient.txt") && dir.cdUp()) {
        // Just moving up
    }
    if (dir.exists("Patient.txt")) {
        QDir::setCurrent(dir.absolutePath());
        qDebug() << "Working directory set to:" << dir.absolutePath();
    }

    // Load counters
    Patient::loadCounterFromFile("Patient.txt");
    Doctor::loadCounterFromFile("Doctor.txt");
    Staff::loadCounterFromFile("Staff.txt");
    Appointment::loadCounterFromFile("Appointment.txt");
    MedicalRecords::loadCounterFromFile("MedicalRecords.txt");
    Billing::loadCounterFromFile("Billing.txt");
    Ambulance::loadCounterFromFile("Ambulance.txt");

    // Global Premium Stylesheet - Modern Medical Theme
    app.setStyleSheet(
        "QMainWindow {"
        "    background-color: #f8fafc;"
        "}"
        "QWidget {"
        "    color: #1e293b;"
        "    font-family: 'Segoe UI', Roboto, Helvetica, Arial, sans-serif;"
        "    font-size: 14px;"
        "}"
        
        /* SIDEBAR STYLING */
        "#Sidebar {"
        "    background-color: #0f172a;"
        "    border-right: 1px solid #1e293b;"
        "    min-width: 240px;"
        "    max-width: 240px;"
        "}"
        "#Sidebar QPushButton {"
        "    background-color: transparent;"
        "    color: #94a3b8;"
        "    text-align: left;"
        "    padding: 12px 20px;"
        "    border: none;"
        "    border-radius: 0px;"
        "    font-weight: 600;"
        "    font-size: 15px;"
        "}"
        "#Sidebar QPushButton:hover {"
        "    background-color: #1e293b;"
        "    color: #f8fafc;"
        "}"
        "#Sidebar QPushButton:checked {"
        "    background-color: #3b82f6;"
        "    color: #ffffff;"
        "    border-left: 4px solid #60a5fa;"
        "}"

        /* CONTENT AREA */
        "#ContentArea {"
        "    background-color: #f8fafc;"
        "    border-top-left-radius: 20px;"
        "}"
        
        /* DASHBOARD CARDS/BUTTONS */
        "QPushButton {"
        "    background-color: #ffffff;"
        "    color: #334155;"
        "    border: 1px solid #e2e8f0;"
        "    border-radius: 12px;"
        "    padding: 15px;"
        "    font-weight: 600;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    border: 1px solid #3b82f6;"
        "    background-color: #eff6ff;"
        "    color: #2563eb;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #dbeafe;"
        "}"
        
        /* ACTION BUTTONS (Logout, etc) */
        "#ActionBtn {"
        "    background-color: #ef4444;"
        "    color: white;"
        "    border: none;"
        "}"
        "#ActionBtn:hover {"
        "    background-color: #dc2626;"
        "}"

        /* HEADERS */
        "#PageHeader {"
        "    color: #0f172a;"
        "    font-size: 24px;"
        "    font-weight: 800;"
        "    margin-bottom: 20px;"
        "}"
        "#SectionHeader {"
        "    color: #64748b;"
        "    font-size: 14px;"
        "    font-weight: 600;"
        "    text-transform: uppercase;"
        "    letter-spacing: 1px;"
        "    margin-top: 10px;"
        "    margin-bottom: 10px;"
        "}"

        /* FORMS & INPUTS */
        "QLineEdit, QComboBox, QDateEdit, QSpinBox, QDoubleSpinBox, QTextEdit {"
        "    border: 1px solid #e2e8f0;"
        "    border-radius: 8px;"
        "    padding: 10px;"
        "    background-color: #ffffff;"
        "    color: #1e293b;"
        "}"
        
        /* SPINBOX ARROWS */
        "QSpinBox::up-button, QDoubleSpinBox::up-button {"
        "    width: 24px; height: 18px;"
        "    background-color: #f1f5f9;"
        "    border-left: 1px solid #e2e8f0;"
        "    border-top-right-radius: 8px;"
        "    margin: 1px;"
        "}"
        "QSpinBox::down-button, QDoubleSpinBox::down-button {"
        "    width: 24px; height: 18px;"
        "    background-color: #f1f5f9;"
        "    border-left: 1px solid #e2e8f0;"
        "    border-bottom-right-radius: 8px;"
        "    margin: 1px;"
        "}"
        "QSpinBox::up-arrow, QDoubleSpinBox::up-arrow {"
        "    width: 8px; height: 8px;"
        "    border-left: 4px solid transparent; border-right: 4px solid transparent;"
        "    border-bottom: 4px solid #64748b;"
        "}"
        "QSpinBox::down-arrow, QDoubleSpinBox::down-arrow {"
        "    width: 8px; height: 8px;"
        "    border-left: 4px solid transparent; border-right: 4px solid transparent;"
        "    border-top: 4px solid #64748b;"
        "}"
        
        /* COMBOBOX STYLING */
        "QComboBox::drop-down {"
        "    subcontrol-origin: padding;"
        "    subcontrol-position: top right;"
        "    width: 34px;"
        "    background-color: #f1f5f9;"
        "    border-left: 1px solid #e2e8f0;"
        "    border-top-right-radius: 8px;"
        "    border-bottom-right-radius: 8px;"
        "}"
        "QComboBox::down-arrow {"
        "    width: 0; height: 0;"
        "    border-left: 6px solid transparent;"
        "    border-right: 6px solid transparent;"
        "    border-top: 6px solid #64748b;"
        "}"

        /* TABLES */
        "QTableWidget {"
        "    background-color: #ffffff;"
        "    border: 1px solid #e2e8f0;"
        "    border-radius: 12px;"
        "    gridline-color: #f1f5f9;"
        "    outline: none;"
        "    selection-background-color: #eff6ff;"
        "    selection-color: #2563eb;"
        "}"
        "QHeaderView::section {"
        "    background-color: #ffffff;"
        "    padding: 12px;"
        "    border: none;"
        "    border-bottom: 2px solid #e2e8f0;"
        "    font-weight: 700;"
        "    color: #475569;"
        "}"
        "QHeaderView::section:vertical {"
        "    background-color: #ffffff;"
        "    color: #94a3b8;"
        "    padding: 5px 15px;"
        "    border-right: 1px solid #e2e8f0;"
        "    border-bottom: 1px solid #f1f5f9;"
        "    font-weight: 600;"
        "    font-size: 12px;"
        "}"
        "QTableWidget::item {"
        "    padding: 10px;"
        "    border-bottom: 1px solid #f1f5f9;"
        "    outline: none;"
        "}"
        "QTableWidget::item:selected {"
        "    background-color: #eff6ff;"
        "    color: #2563eb;"
        "    border: none;"
        "}"

        /* DIALOGS */
        "QDialog, QMessageBox, QInputDialog {"
        "    background-color: #ffffff;"
        "}"
        "QDialog QLabel, QMessageBox QLabel, QInputDialog QLabel {"
        "    color: #1e293b;"
        "}"
        "QDialog QLineEdit, QDialog QComboBox, QDialog QDateEdit, QDialog QTextEdit, QDialog QPlainTextEdit, QInputDialog QLineEdit {"
        "    background-color: #ffffff;"
        "    color: #0f172a;"
        "    border: 1px solid #cbd5e1;"
        "    border-radius: 8px;"
        "    padding: 10px;"
        "}"
        "QDialog QPushButton, QMessageBox QPushButton, QInputDialog QPushButton {"
        "    background-color: #f1f5f9;"
        "    color: #1e293b;"
        "    border: 1px solid #e2e8f0;"
        "    padding: 8px 16px;"
        "    border-radius: 6px;"
        "}"
        "QDialog QPushButton:hover, QMessageBox QPushButton:hover, QInputDialog QPushButton:hover {"
        "    background-color: #e2e8f0;"
        "}"
    );

    LoginWindow w;
    w.show();
    return app.exec();
}