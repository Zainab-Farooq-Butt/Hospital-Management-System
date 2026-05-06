#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../login.h"
#include <QMessageBox>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir::setCurrent(QCoreApplication::applicationDirPath() + "/../../../../");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    string username=ui->usernameText->text().toStdString();
    string password=ui->passwordText->text().toStdString();
    string role=Login::authenticate(username,password);

    if(role=="NONE"){
        QMessageBox::warning(this,"Login Failed","Invalid Credentials");
    }
    else{
        QMessageBox::information(this,"Login Succcesfull","Welcome "+ QString::fromStdString(role));
    }
}

