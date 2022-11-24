#include "home_page_dialog.h"
#include "ui_home_page_dialog.h"

bool HomePageDialog::isFishing = false;

QString HomePageDialog::email;

QString HomePageDialog::password;

#include "application_utilities.h"

#include <QUrl>
#include <QDesktopServices>
#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

/* forms */
#include "score_board_dialog.h"

HomePageDialog::HomePageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomePageDialog) {
    ui->setupUi(this);

    this->setWindowIcon(QIcon("resources/icons/iconApp.png"));
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    ui->titleLabel->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 30, 40));
    ui->statusLabel->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 24, 40));
    ui->startButton->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->stopButton->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->scoreBoardButton->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->optionsButton->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 15, 40));
    ui->myNickLabel->setFont(QFont("resources/fonts/Marhey-Bold.ttf", 18, 40));

    this->isFishing = false;
    ui->statusColor->setStyleSheet("background-color: rgb(186, 0, 0);");

    getNicknameFromServer();
}

HomePageDialog::~HomePageDialog() {
    delete ui;
}

void HomePageDialog::getNicknameReqFinished(QNetworkReply *rep) {
    /* check the error */
    if(!(rep->error() == QNetworkReply::NoError)) {
        QString strRep = (QString) rep->readAll();

        if(strRep == LoginErrors::UnprocessableEntity) {
            QMessageBox::critical(0, "Fatal Error", "The application failed to load the resources\n[ ERROR MESSAGE ]: " + strRep);
            return; this->close();
        }

        return; this->close();
    }
    QJsonDocument jDoc = QJsonDocument::fromJson(rep->readAll());
    QJsonObject jObj = jDoc.object();

    /* set the nickname */
    ui->myNickLabel->setText("You: " + jObj["nickname"].toString());
}

void HomePageDialog::getNicknameFromServer() {
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(getNicknameReqFinished(QNetworkReply*)));
    connect(manager,SIGNAL(finished(QNetworkReply*)),manager,SLOT(deleteLater()));

    QUrl url(ApplicationUtilities::getNicknameApiUrl);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject obj;
    obj["email"] = HomePageDialog::email;

    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();

    manager->post(request, data);
}

void HomePageDialog::on_startButton_clicked() {
    if(this->isFishing) { return; }

    ui->statusColor->setStyleSheet("background-color: rgb(0, 100, 0);");
    this->isFishing = true;
}

void HomePageDialog::on_stopButton_clicked() {
    if(!this->isFishing) { return; }

    ui->statusColor->setStyleSheet("background-color: rgb(186, 0, 0);");
    this->isFishing = false;
}

void HomePageDialog::on_scoreBoardButton_clicked() {
    ScoreBoardDialog scoreBoardDialog;

    scoreBoardDialog.setModal(true);
    scoreBoardDialog.show();
    scoreBoardDialog.exec();
}

