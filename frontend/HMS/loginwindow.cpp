#include "loginwindow.h"
#include "admindashboard.h"
#include "doctordashboard.h"
#include "patientdashboard.h"
#include "../../Login.h"
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QFrame>
#include <QPixmap>

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("HMS Login");
    resize(1000, 700); // Larger window for a more professional feel
    
    auto *central = new QWidget(this);
    central->setStyleSheet("background-color: #f8fafc;");
    
    auto *mainLayout = new QHBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // --- LEFT SIDE: BRANDING/ILLUSTRATION ---
    auto *brandPanel = new QWidget(central);
    brandPanel->setStyleSheet(
        "background-color: #0f172a;"
    );
    auto *brandLayout = new QVBoxLayout(brandPanel);
    brandLayout->addStretch();
    
    auto *brandIcon = new QLabel("🏥", brandPanel);
    brandIcon->setStyleSheet("font-size: 80px; margin-bottom: 20px;");
    brandIcon->setAlignment(Qt::AlignCenter);
    brandLayout->addWidget(brandIcon);

    auto *brandTitle = new QLabel("Hospital Management\nSystem", brandPanel);
    brandTitle->setStyleSheet("color: white; font-size: 32px; font-weight: 900;");
    brandTitle->setAlignment(Qt::AlignCenter);
    brandLayout->addWidget(brandTitle);

    auto *brandDesc = new QLabel("Advanced healthcare administration\nand patient care management.", brandPanel);
    brandDesc->setStyleSheet("color: #94a3b8; font-size: 16px; margin-top: 20px;");
    brandDesc->setAlignment(Qt::AlignCenter);
    brandLayout->addWidget(brandDesc);

    brandLayout->addStretch();
    mainLayout->addWidget(brandPanel, 1);

    // --- RIGHT SIDE: LOGIN FORM ---
    auto *formPanel = new QWidget(central);
    auto *formLayout = new QVBoxLayout(formPanel);
    formLayout->setContentsMargins(80, 40, 80, 40);
    
    formLayout->addStretch();

    auto *loginTitle = new QLabel("Welcome Back", formPanel);
    loginTitle->setStyleSheet("color: #0f172a; font-size: 28px; font-weight: 800;");
    formLayout->addWidget(loginTitle);

    auto *loginSubtitle = new QLabel("Please enter your credentials to login", formPanel);
    loginSubtitle->setStyleSheet("color: #64748b; font-size: 15px; margin-bottom: 30px;");
    formLayout->addWidget(loginSubtitle);

    auto *lblUser = new QLabel("Username", formPanel);
    lblUser->setStyleSheet("color: #475569; font-weight: 600; margin-bottom: 5px;");
    formLayout->addWidget(lblUser);

    usernameEdit = new QLineEdit(formPanel);
    usernameEdit->setPlaceholderText("Enter your username");
    usernameEdit->setMinimumHeight(45);
    formLayout->addWidget(usernameEdit);

    formLayout->addSpacing(20);

    auto *lblPwd = new QLabel("Password", formPanel);
    lblPwd->setStyleSheet("color: #475569; font-weight: 600; margin-bottom: 5px;");
    formLayout->addWidget(lblPwd);

    passwordEdit = new QLineEdit(formPanel);
    passwordEdit->setPlaceholderText("Enter your password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setMinimumHeight(45);
    formLayout->addWidget(passwordEdit);

    formLayout->addSpacing(30);

    loginBtn = new QPushButton("Sign In", formPanel);
    loginBtn->setMinimumHeight(50);
    loginBtn->setStyleSheet(
        "QPushButton {"
        "    background-color: #3b82f6;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 8px;"
        "    font-weight: 700;"
        "    font-size: 16px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2563eb;"
        "}"
    );
    formLayout->addWidget(loginBtn);

    formLayout->addStretch();
    mainLayout->addWidget(formPanel, 1);

    setCentralWidget(central);

    connect(loginBtn,    &QPushButton::clicked,        this, &LoginWindow::onLoginClicked);
    connect(passwordEdit, &QLineEdit::returnPressed,   this, &LoginWindow::onLoginClicked);
}

void LoginWindow::onLoginClicked() {
    QString uname = usernameEdit->text().trimmed();
    QString pwd   = passwordEdit->text();

    if (uname.isEmpty() || pwd.isEmpty()) {
        QMessageBox::warning(this, "Missing Info",
                             "Please enter both username and password.");
        return;
    }

    Login login;
    std::string role = login.authenticate(uname.toStdString(), pwd.toStdString());

    if (role == "ADMIN") {
        auto *dash = new AdminDashboard(uname);
        dash->setAttribute(Qt::WA_DeleteOnClose);
        dash->show();
        this->close();
    }
    else if (role == "DOCTOR") {
        auto *dash = new DoctorDashboard(uname);
        dash->setAttribute(Qt::WA_DeleteOnClose);
        dash->show();
        this->close();
    }
    else if (role == "PATIENT") {
        auto *dash = new PatientDashboard(uname);
        dash->setAttribute(Qt::WA_DeleteOnClose);
        dash->show();
        this->close();
    }
    else {
        QMessageBox::critical(this, "Login Failed",
                              "Invalid credentials. Try again.");
        passwordEdit->clear();
    }
}