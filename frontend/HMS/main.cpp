#include <QApplication>
#include "loginwindow.h"
#include "../../Patient.h"
#include "../../Doctor.h"
#include "../../Staff.h"
#include "../../Appointment.h"
#include "../../MedicalRecords.h"
#include "../../Billing.h"
#include "../../Ambulance.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Patient::loadCounterFromFile("Patient.txt");
    Doctor::loadCounterFromFile("Doctor.txt");
    Staff::loadCounterFromFile("Staff.txt");
    Appointment::loadCounterFromFile("Appointment.txt");
    MedicalRecords::loadCounterFromFile("MedicalRecords.txt");
    Billing::loadCounterFromFile("Billing.txt");
    Ambulance::loadCounterFromFile("Ambulance.txt");

    app.setStyleSheet(
        /* === BASE === */
        "QWidget { background-color: #f5f7fa; color: #1a2332; font-family: 'Segoe UI'; font-size: 13px; }"
        "QMainWindow { background-color: #f5f7fa; }"
        "QDialog { background-color: #ffffff; border: 1px solid #e2e8f0; border-radius: 12px; }"

        /* === LABELS === */
        "QLabel { color: #1a2332; background: transparent; }"

        /* === BUTTONS === */
        "QPushButton {"
        "    background-color: #0057b8;"
        "    color: #ffffff;"
        "    border: none;"
        "    border-radius: 8px;"
        "    padding: 9px 20px;"
        "    font-size: 13px;"
        "    font-weight: 600;"
        "    letter-spacing: 0.3px;"
        "}"
        "QPushButton:hover { background-color: #0069d9; }"
        "QPushButton:pressed { background-color: #004494; }"
        "QPushButton:disabled { background-color: #cbd5e1; color: #94a3b8; }"

        /* === INPUTS === */
        "QLineEdit {"
        "    background-color: #ffffff;"
        "    color: #1a2332;"
        "    border: 1.5px solid #e2e8f0;"
        "    border-radius: 8px;"
        "    padding: 9px 13px;"
        "    font-size: 13px;"
        "    selection-background-color: #0057b8;"
        "    selection-color: #ffffff;"
        "}"
        "QLineEdit:focus { border: 1.5px solid #0057b8; background-color: #ffffff; }"
        "QLineEdit:disabled { background-color: #f8fafc; color: #94a3b8; }"

        "QTextEdit, QPlainTextEdit {"
        "    background-color: #ffffff;"
        "    color: #1a2332;"
        "    border: 1.5px solid #e2e8f0;"
        "    border-radius: 8px;"
        "    padding: 8px;"
        "    selection-background-color: #0057b8;"
        "}"
        "QTextEdit:focus, QPlainTextEdit:focus { border-color: #0057b8; }"

        /* === COMBO BOX === */
        "QComboBox {"
        "    background-color: #ffffff;"
        "    color: #1a2332;"
        "    border: 1.5px solid #e2e8f0;"
        "    border-radius: 8px;"
        "    padding: 8px 13px;"
        "    font-size: 13px;"
        "}"
        "QComboBox:hover { border-color: #0057b8; }"
        "QComboBox:focus { border-color: #0057b8; }"
        "QComboBox::drop-down { border: none; width: 28px; }"
        "QComboBox::down-arrow { border-left: 5px solid transparent; border-right: 5px solid transparent; border-top: 6px solid #64748b; margin-right: 8px; }"
        "QComboBox QAbstractItemView { background-color: #ffffff; color: #1a2332; border: 1.5px solid #e2e8f0; border-radius: 8px; selection-background-color: #eff6ff; selection-color: #0057b8; outline: none; padding: 4px; }"

        /* === SPINBOX === */
        "QSpinBox, QDoubleSpinBox { background-color: #ffffff; color: #1a2332; border: 1.5px solid #e2e8f0; border-radius: 8px; padding: 8px 10px; }"
        "QSpinBox:focus, QDoubleSpinBox:focus { border-color: #0057b8; }"
        "QSpinBox::up-button, QDoubleSpinBox::up-button, QSpinBox::down-button, QDoubleSpinBox::down-button { background-color: #f1f5f9; border: none; width: 18px; border-radius: 4px; }"
        "QSpinBox::up-button:hover, QDoubleSpinBox::up-button:hover, QSpinBox::down-button:hover, QDoubleSpinBox::down-button:hover { background-color: #e2e8f0; }"

        /* === DATE/TIME === */
        "QDateEdit, QTimeEdit, QDateTimeEdit { background-color: #ffffff; color: #1a2332; border: 1.5px solid #e2e8f0; border-radius: 8px; padding: 8px 10px; }"
        "QDateEdit:focus, QTimeEdit:focus, QDateTimeEdit:focus { border-color: #0057b8; }"
        "QDateEdit::drop-down, QTimeEdit::drop-down, QDateTimeEdit::drop-down { border: none; width: 22px; }"
        "QCalendarWidget { background-color: #ffffff; color: #1a2332; border: 1px solid #e2e8f0; border-radius: 8px; }"
        "QCalendarWidget QToolButton { color: #0057b8; background: transparent; font-weight: 600; }"
        "QCalendarWidget QAbstractItemView { background-color: #ffffff; color: #1a2332; selection-background-color: #0057b8; selection-color: #ffffff; }"

        /* === CHECKBOX & RADIO === */
        "QCheckBox { color: #1a2332; spacing: 8px; }"
        "QCheckBox::indicator { width: 17px; height: 17px; border: 1.5px solid #cbd5e1; border-radius: 4px; background-color: #ffffff; }"
        "QCheckBox::indicator:checked { background-color: #0057b8; border-color: #0057b8; }"
        "QCheckBox::indicator:hover { border-color: #0057b8; }"
        "QRadioButton { color: #1a2332; spacing: 8px; }"
        "QRadioButton::indicator { width: 17px; height: 17px; border: 1.5px solid #cbd5e1; border-radius: 9px; background-color: #ffffff; }"
        "QRadioButton::indicator:checked { background-color: #0057b8; border-color: #0057b8; }"

        /* === TABLE === */
        "QTableWidget, QTableView {"
        "    background-color: #ffffff;"
        "    color: #1a2332;"
        "    border: 1px solid #e2e8f0;"
        "    border-radius: 10px;"
        "    gridline-color: #f1f5f9;"
        "    selection-background-color: #eff6ff;"
        "    selection-color: #0057b8;"
        "    alternate-background-color: #f8fafc;"
        "}"
        "QTableWidget::item, QTableView::item { padding: 9px 12px; border: none; }"
        "QTableWidget::item:selected, QTableView::item:selected { background-color: #eff6ff; color: #0057b8; }"
        "QTableWidget::item:hover, QTableView::item:hover { background-color: #f8fafc; }"
        "QHeaderView::section {"
        "    background-color: #f1f5f9;"
        "    color: #64748b;"
        "    font-weight: 600;"
        "    font-size: 12px;"
        "    letter-spacing: 0.4px;"
        "    padding: 10px 12px;"
        "    border: none;"
        "    border-bottom: 2px solid #e2e8f0;"
        "}"

        /* === LIST === */
        "QListWidget { background-color: #ffffff; color: #1a2332; border: 1.5px solid #e2e8f0; border-radius: 10px; padding: 4px; outline: none; }"
        "QListWidget::item { padding: 10px 14px; border-radius: 6px; margin: 2px 0; }"
        "QListWidget::item:selected { background-color: #eff6ff; color: #0057b8; }"
        "QListWidget::item:hover { background-color: #f8fafc; }"

        /* === TABS === */
        "QTabWidget::pane { background-color: #ffffff; border: 1px solid #e2e8f0; border-radius: 10px; padding: 12px; }"
        "QTabBar::tab { background-color: transparent; color: #64748b; padding: 10px 20px; margin-right: 4px; border: none; border-bottom: 2px solid transparent; font-weight: 500; }"
        "QTabBar::tab:selected { color: #0057b8; border-bottom: 2px solid #0057b8; font-weight: 600; }"
        "QTabBar::tab:hover { color: #1a2332; background-color: #f8fafc; border-radius: 6px 6px 0 0; }"

        /* === GROUP BOX === */
        "QGroupBox { background-color: #ffffff; border: 1.5px solid #e2e8f0; border-radius: 10px; margin-top: 14px; padding: 16px 12px 12px 12px; font-weight: 600; color: #64748b; font-size: 12px; }"
        "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; left: 14px; top: -8px; padding: 0 6px; background-color: #ffffff; color: #0057b8; }"

        /* === MENU === */
        "QMenuBar { background-color: #ffffff; color: #1a2332; border-bottom: 1px solid #e2e8f0; padding: 4px 8px; }"
        "QMenuBar::item { padding: 6px 14px; border-radius: 6px; background: transparent; }"
        "QMenuBar::item:selected { background-color: #f1f5f9; color: #0057b8; }"
        "QMenu { background-color: #ffffff; color: #1a2332; border: 1px solid #e2e8f0; border-radius: 8px; padding: 6px; }"
        "QMenu::item { padding: 8px 20px; border-radius: 6px; }"
        "QMenu::item:selected { background-color: #eff6ff; color: #0057b8; }"
        "QMenu::separator { height: 1px; background-color: #f1f5f9; margin: 4px 10px; }"

        /* === TOOLBAR === */
        "QToolBar { background-color: #ffffff; border-bottom: 1px solid #e2e8f0; padding: 4px 8px; spacing: 4px; }"
        "QToolButton { background-color: transparent; color: #64748b; border: none; border-radius: 6px; padding: 6px 12px; }"
        "QToolButton:hover { background-color: #f1f5f9; color: #1a2332; }"

        /* === STATUS BAR === */
        "QStatusBar { background-color: #ffffff; color: #64748b; border-top: 1px solid #e2e8f0; font-size: 12px; padding: 4px 10px; }"

        /* === SCROLLBAR === */
        "QScrollBar:vertical { background: #f1f5f9; width: 8px; border-radius: 4px; margin: 0; }"
        "QScrollBar::handle:vertical { background: #cbd5e1; border-radius: 4px; min-height: 30px; }"
        "QScrollBar::handle:vertical:hover { background: #0057b8; }"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0; }"
        "QScrollBar:horizontal { background: #f1f5f9; height: 8px; border-radius: 4px; }"
        "QScrollBar::handle:horizontal { background: #cbd5e1; border-radius: 4px; min-width: 30px; }"
        "QScrollBar::handle:horizontal:hover { background: #0057b8; }"
        "QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal { width: 0; }"

        /* === MISC === */
        "QProgressBar { background-color: #e2e8f0; border: none; border-radius: 6px; height: 8px; color: transparent; }"
        "QProgressBar::chunk { background: #0057b8; border-radius: 6px; }"
        "QToolTip { background-color: #1a2332; color: #ffffff; border: none; border-radius: 6px; padding: 6px 10px; font-size: 12px; }"
        "QMessageBox { background-color: #ffffff; color: #1a2332; }"
        "QMessageBox QPushButton { min-width: 90px; padding: 8px 18px; }"
        "QSplitter::handle { background-color: #e2e8f0; }"
        "QSplitter::handle:hover { background-color: #0057b8; }"
        "QFrame[frameShape='4'], QFrame[frameShape='5'] { color: #e2e8f0; }"
    );

    LoginWindow w;
    w.show();
    return app.exec();
}