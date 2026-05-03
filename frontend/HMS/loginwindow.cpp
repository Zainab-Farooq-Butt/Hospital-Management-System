#include "loginwindow.h"
#include "admindashboard.h"
#include "doctordashboard.h"
#include "patientdashboard.h"
#include "../../Login.h"
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Hospital Management System - Login");
    resize(420, 320);

    auto *central = new QWidget(this);
    auto *layout  = new QVBoxLayout(central);
    layout->setContentsMargins(40, 30, 40, 30);
    layout->setSpacing(15);

    auto *title = new QLabel("Hospital Management System", central);
    QFont tf = title->font();
    tf.setPointSize(16);
    tf.setBold(true);
    title->setFont(tf);
    title->setAlignment(Qt::AlignCenter);

    auto *lblUser = new QLabel("Username:", central);
    usernameEdit = new QLineEdit(central);

    auto *lblPwd = new QLabel("Password:", central);
    passwordEdit = new QLineEdit(central);
    passwordEdit->setEchoMode(QLineEdit::Password);

    loginBtn = new QPushButton("Login", central);
    loginBtn->setMinimumHeight(36);

    layout->addWidget(title);
    layout->addSpacing(10);
    layout->addWidget(lblUser);
    layout->addWidget(usernameEdit);
    layout->addWidget(lblPwd);
    layout->addWidget(passwordEdit);
    layout->addSpacing(10);
    layout->addWidget(loginBtn);
    layout->addStretch();

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