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

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Hospital Management System - Login");
    resize(420, 320);

    auto *central = new QWidget(this);

    // Create a styled frame to act as a "card" for the login form
    auto *formFrame = new QFrame(central);
    formFrame->setObjectName("loginCard");
    formFrame->setMaximumWidth(420); // Slightly wider card
    formFrame->setStyleSheet(
        "#loginCard {"
        "   background-color: white;"
        "   border-radius: 10px;"
        "   border: 1px solid #d0e0e3;"
        "}"
    );
    
    auto *layout  = new QVBoxLayout(formFrame);
    layout->setContentsMargins(40, 40, 40, 40); // More padding for card look
    layout->setSpacing(20);

    // Title and Subtitle
    auto *title = new QLabel("Hospital Management", formFrame);
    QFont tf = title->font();
    tf.setPointSize(18);
    tf.setBold(true);
    title->setFont(tf);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: #00509e;");

    auto *subtitle = new QLabel("Sign in to your account", formFrame);
    QFont sf = subtitle->font();
    sf.setPointSize(10);
    subtitle->setFont(sf);
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("color: #666666; margin-bottom: 10px;");

    auto *lblUser = new QLabel("Username:", formFrame);
    QFont lblFont = lblUser->font();
    lblFont.setBold(true);
    lblUser->setFont(lblFont);
    usernameEdit = new QLineEdit(formFrame);
    usernameEdit->setMinimumHeight(35);

    auto *lblPwd = new QLabel("Password:", formFrame);
    lblPwd->setFont(lblFont);
    passwordEdit = new QLineEdit(formFrame);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setMinimumHeight(35);

    loginBtn = new QPushButton("Login", formFrame);
    loginBtn->setMinimumHeight(45); // Bigger login button
    QFont btnFont = loginBtn->font();
    btnFont.setBold(true);
    btnFont.setPointSize(11);
    loginBtn->setFont(btnFont);

    layout->addWidget(title);
    layout->addWidget(subtitle);
    layout->addWidget(lblUser);
    layout->addWidget(usernameEdit);
    layout->addWidget(lblPwd);
    layout->addWidget(passwordEdit);
    layout->addSpacing(15);
    layout->addWidget(loginBtn);

    // Main layouts to center the formFrame horizontally and vertically
    auto *mainVLayout = new QVBoxLayout(central);
    auto *mainHLayout = new QHBoxLayout();
    
    mainHLayout->addStretch();
    mainHLayout->addWidget(formFrame);
    mainHLayout->addStretch();
    
    mainVLayout->addStretch();
    mainVLayout->addLayout(mainHLayout);
    mainVLayout->addStretch();

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