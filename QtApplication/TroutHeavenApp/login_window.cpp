#include "login_window.h"
#include "ui_login_window.h"

#include <QDebug>
#include <QUrl>
#include <QDesktopServices>

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    ui->titleLabel->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 29, 40));
    ui->emailBox->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 19, 40));
    ui->passwordBox->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 19, 40));
    ui->loginButton->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 20, 40));
    ui->label_3->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 12, 40));
    ui->linkButton->setFont((QFont("resources/fonts/Marhey-Bold.ttf", 12, 40)));
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::on_linkButton_clicked() {
    QDesktopServices::openUrl(QUrl("http://localhost:3000/views/registration.html", QUrl::TolerantMode));
}

