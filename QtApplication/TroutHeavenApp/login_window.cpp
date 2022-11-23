#include "login_window.h"
#include "ui_login_window.h"

#include "application_utilities.h"

#include <QDebug>
#include <QUrl>
#include <QDesktopServices>
#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QKeyEvent>

/* form */
#include "home_page_dialog.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    this->setWindowIcon(QIcon("resources/icons/iconApp.png"));
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

void LoginWindow::keyPressEvent(QKeyEvent *event) {
    /* check if the user pressed ENTER */
    if((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
        this->on_loginButton_clicked();
    }
}

void LoginWindow::loginFinished(QNetworkReply *rep) {
    /* check the error */
    if(!(rep->error() == QNetworkReply::NoError)) {
        QString strRep = (QString) rep->readAll();
        if(strRep == LoginErrors::Unauthorized) {
            QMessageBox::warning(0, "Warning", "Email or password wrong.");
            return;
        }
        if(strRep == LoginErrors::UnprocessableEntity) {
            QMessageBox::warning(0, "Warning", "Invalid email or password");
            return;
        }
        else {
            QMessageBox::critical(0, "Fatal Error", strRep);
            return;
        }
    }
    this->hide();

    /* open the homepage dialog */
    HomePageDialog homePageDialog;
    homePageDialog.show();
    homePageDialog.exec();
}

void LoginWindow::on_linkButton_clicked() {
    QDesktopServices::openUrl(QUrl(ApplicationUtilities::registrationPageUrl, QUrl::TolerantMode));
}

void LoginWindow::on_loginButton_clicked() {
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(loginFinished(QNetworkReply*)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),manager,SLOT(deleteLater()));

    QUrl url(ApplicationUtilities::loginAPiUrl);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["email"] = ui->emailBox->text();
    obj["password"] = ui->passwordBox->text();

    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    manager->post(request, data);
}
