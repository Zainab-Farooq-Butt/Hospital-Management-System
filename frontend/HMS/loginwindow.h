#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

class LoginWindow : public QMainWindow {
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = nullptr);

private slots:
    void onLoginClicked();

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginBtn;
};

#endif